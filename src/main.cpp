#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <string>
#include <vector>
#include <cstdlib>    // for rand(), srand()
#include <ctime>      // for time()
#include <chrono>
#include <iomanip>
#include <filesystem>
#include <thread>
#include <limits>
#include "../include/Matrix.h"
#include "../include/Vector.h"
#include "../include/LinearSystem.h"

using namespace std;

struct CPURecord { int MYCT, MMIN, MMAX, CACH, CHMIN, CHMAX, PRP; };

static double my_sqrt(double x) {
    if (x <= 0) return 0;
    double r = x;
    for (int i = 0; i < 10; ++i)
        r = 0.5*(r + x/r);
    return r;
}

// load all records into a dynamic array, return count by reference
static CPURecord* loadData(const string& path, int& outN) {
    ifstream in(path);
    if (!in) throw runtime_error("Cannot open data file");
    // first count lines
    int N = 0;
    string line;
    while (getline(in,line))
      if (!line.empty()) ++N;
    in.clear(); in.seekg(0);

    CPURecord* A = new CPURecord[N];
    int idx = 0;
    while (getline(in,line)) {
        if (line.empty()) continue;
        istringstream ss(line);
        string tmp; CPURecord r;
        getline(ss,tmp,','); // skip vendor
        getline(ss,tmp,','); // skip model
        getline(ss,tmp,','); r.MYCT = stoi(tmp);
        getline(ss,tmp,','); r.MMIN = stoi(tmp);
        getline(ss,tmp,','); r.MMAX = stoi(tmp);
        getline(ss,tmp,','); r.CACH = stoi(tmp);
        getline(ss,tmp,','); r.CHMIN= stoi(tmp);
        getline(ss,tmp,','); r.CHMAX= stoi(tmp);
        // now column #9 is PRP, column #10 is ERP:
        getline(ss,tmp,','); r.PRP  = stoi(tmp);  // PRP
        getline(ss,tmp,',');         /* skip ERP */ 
        A[idx++] = r;
    }
    outN = idx;
    return A;
}

// shuffle with fixed seed for reproducibility and no rand() bias
static void shuffleData(CPURecord* A, int N) {
    // seed generator randomly for a new shuffle each run
    std::random_device rd;
    std::mt19937_64 gen(rd());
    for (int i = N-1; i > 0; --i) {
        std::uniform_int_distribution<> d(0,i);
        int j = d(gen);
        CPURecord tmp = A[i];
        A[i] = A[j];
        A[j] = tmp;
    }
}

// RMSE on our Vector class
static double computeRMSE(const Vector& T, const Vector& P) {
    if (T.size() != P.size())
        throw invalid_argument("RMSE size mismatch");
    double s=0;
    for (size_t i=0;i<T.size();++i) {
        double d = T[i] - P[i];
        s += d*d;
    }
    return my_sqrt(s / T.size());
}

/// Reads all lines of logPath, renumbers “[epoch N]” tags from 1…n, and writes back.
void renumberEpochsInLog(const std::string& logPath) {
    // 1) read
    std::ifstream fin(logPath);
    if (!fin) {
        std::cerr << "Cannot open " << logPath << " for reading\n";
        return;
    }
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(fin, line)) {
        lines.push_back(line);
    }
    fin.close();

    // 2) rewrite with new epoch numbers
    std::ofstream fout(logPath);
    if (!fout) {
        std::cerr << "Cannot open " << logPath << " for writing\n";
        return;
    }
    for (size_t i = 0; i < lines.size(); ++i) {
        auto& L = lines[i];
        auto pos = L.find("[epoch ");
        if (pos != std::string::npos) {
            auto end = L.find(']', pos);
            if (end != std::string::npos) {
                std::ostringstream oss;
                oss << "[epoch " << (i+1) << "]";
                L.replace(pos, end - pos + 1, oss.str());
            }
        }
        fout << L << "\n";
    }
    fout.close();
}

int main(int argc, char* argv[]){
    try {
        // prepare output directory in workspace root
        const std::string outDir = "Prediction";
        std::filesystem::create_directories(outDir);
        // prepare model file path and clear previous contents
        const std::string modelFile = outDir + "/model.txt";
        // ensure model file is writable
        std::ofstream initOut(modelFile, std::ios::out | std::ios::trunc);
        if (!initOut) {
            std::cerr << "ERROR: Cannot initialize model file at "
                      << std::filesystem::absolute(modelFile) << "\n";
            return 1;
        }
        initOut.close();
        // load data
        int N;
        CPURecord* all = loadData("data/machine.data", N);
        // determine epochs from command line (default 20)
        int epochs = 20;
        if (argc >= 2) epochs = std::max(1, std::atoi(argv[1]));
        // online model coefficients (initially zero)
        Vector x_old;
        // load previous model if present
        {
            std::ifstream inM(modelFile);
            if (inM) {
                std::vector<double> tmp;
                double v;
                while (inM >> v) tmp.push_back(v);
                if (!tmp.empty()) {
                    x_old = Vector(tmp.size());
                    for (size_t i = 0; i < tmp.size(); ++i)
                        x_old[i] = tmp[i];
                }
            }
        }
        
        // run multiple epochs
        for (int ep = 1; ep <= epochs; ++ep) {
            // shuffle and split
            shuffleData(all, N);
            int n_train = int(0.8 * N), n_test = N - n_train;
            // require at least one sample each
            if (n_train <= 0 || n_test <= 0) {
                std::cerr << "Not enough data (N=" << N << ") to split 80/20\n";
                break;
            }
            // build A,b
            Matrix A(n_train, 6);
            Vector b(n_train);
            for (int i = 0; i < n_train; ++i) {
                auto& r = all[i];
                A(i+1,1)=r.MYCT; A(i+1,2)=r.MMIN;
                A(i+1,3)=r.MMAX; A(i+1,4)=r.CACH;
                A(i+1,5)=r.CHMIN; A(i+1,6)=r.CHMAX;
                b[i] = r.PRP;
            }

            // train model
            LinearSystem sys(A,b);
            Vector x_new = sys.Solve();
            // ensure x_old initialized at first epoch
            if (ep == 1 && x_old.size() != x_new.size()) {
                x_old = Vector(x_new.size());
                for (size_t k = 0; k < x_old.size(); ++k) x_old[k] = 0.0;
            }
            // evaluate new and old models on test set
            Vector y_true(n_test), y_pred_new(n_test), y_pred_old(n_test);
            for (int i = 0; i < n_test; ++i) {
                auto& r = all[n_train + i];
                y_true[i] = r.PRP;
                // prediction by new
                double pnew = 0;
                for (size_t k = 0; k < x_new.size(); ++k) {
                    double feat = (k==0? r.MYCT : k==1? r.MMIN : k==2? r.MMAX :
                                   k==3? r.CACH : k==4? r.CHMIN : r.CHMAX);
                    pnew += x_new[k] * feat;
                }
                y_pred_new[i] = pnew;
                // prediction by old (only if sizes match)
                if (x_old.size() == x_new.size()) {
                    double pold = 0;
                    for (size_t k = 0; k < x_old.size(); ++k) {
                        double feat = (k==0? r.MYCT : k==1? r.MMIN : k==2? r.MMAX :
                                       k==3? r.CACH : k==4? r.CHMIN : r.CHMAX);
                        pold += x_old[k] * feat;
                    }
                    y_pred_old[i] = pold;
                }
            }
            double rmse_new = computeRMSE(y_true, y_pred_new);
            double rmse_old = (x_old.size() == x_new.size() ?
                               computeRMSE(y_true, y_pred_old) :
                               std::numeric_limits<double>::infinity());
            // choose better model
            Vector x_best = (rmse_new <= rmse_old ? x_new : x_old);
            double rmse_best = std::min(rmse_new, rmse_old);
            // save chosen model
            std::ofstream outM(modelFile, std::ios::out | std::ios::trunc);
            if (!outM) {
                std::cerr << "ERROR: Cannot open model file for writing at "
                          << std::filesystem::absolute(modelFile) << "\n";
            } else {
                for (size_t k = 0; k < x_best.size(); ++k) outM << x_best[k] << "\n";
                outM.close();
            }
            x_old = x_best;
            // log and report
            std::cout << "Epoch " << ep << ": RMSE(new)=" << rmse_new
                      << ", RMSE(old)=" << rmse_old
                      << ", chosen RMSE=" << rmse_best << "\n";
            // log best RMSE
            std::ofstream logFile(outDir + "/rmse.log", std::ios::app);
            auto now = std::chrono::system_clock::now();
            std::time_t t = std::chrono::system_clock::to_time_t(now);
            logFile << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S")
                    << " [epoch " << ep << "] RMSE = " << rmse_best << "\n";
            
            // renumber epochs in log after each epochs complete
            renumberEpochsInLog(outDir + "/rmse.log");

            // pause for 1 seconds before next epoch
            // std::this_thread::sleep_for(std::chrono::seconds(01));
        }


        delete[] all;
    }
    catch(const exception& e){
        cerr<<"ERROR: "<<e.what()<<"\n";
        return 1;
    }
    return 0;
}
