#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <cstdlib>    // for rand(), srand()
#include <ctime>      // for time()
#include <chrono>
#include <iomanip>
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

int main(){
    try {
        int N;
        CPURecord* all = loadData("data/machine.data", N);
        shuffleData(all, N);

        int n_train = int(0.8 * N), n_test = N - n_train;
        // build A,b for training
        Matrix A(n_train, 6);
        Vector b(n_train);
        for(int i=0;i<n_train;++i){
          auto&r = all[i];
          A(i+1,1)=r.MYCT; A(i+1,2)=r.MMIN;
          A(i+1,3)=r.MMAX; A(i+1,4)=r.CACH;
          A(i+1,5)=r.CHMIN;A(i+1,6)=r.CHMAX;
          b[i] = r.PRP;
        }

        LinearSystem sys(A,b);
        Vector x = sys.Solve();
        cout<<"Model x = "; 
        for(size_t i=0;i<x.size();++i) cout<<x[i]<<" ";
        cout<<"\n";

        // evaluate on test set
        Vector y_true(n_test), y_pred(n_test);
        for(int i=0;i<n_test;++i){
          auto&r = all[n_train + i];
          y_true[i] = r.PRP;
          double p=0;
          p += x[0]*r.MYCT + x[1]*r.MMIN + x[2]*r.MMAX
            + x[3]*r.CACH + x[4]*r.CHMIN + x[5]*r.CHMAX;
          y_pred[i] = p;
        }

        // compute and display RMSE
        double rmse = computeRMSE(y_true,y_pred);
        cout << "Test RMSE = " << rmse << "\n";
        // append RMSE to log file with timestamp
        std::ofstream logFile("rmse.log", std::ios::app);
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        logFile << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S")
                << " RMSE = " << rmse << "\n";

        delete[] all;
    }
    catch(const exception& e){
        cerr<<"ERROR: "<<e.what()<<"\n";
        return 1;
    }
    return 0;
}
