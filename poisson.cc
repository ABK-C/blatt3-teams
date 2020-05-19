#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

double mu = 3.11538;
int N = 234;

double poisson(double mu, int k) {
    double mu_k = pow(mu, k);
    double exp_mu = exp(-mu);
    double k_Fak = tgamma(k+1);
    double Poisson = mu_k * exp_mu * (1/(k_Fak));
    return Poisson;
}

int main() {
    using namespace std;

    vector<int> zaehler(11);
    ifstream fin("datensumme.txt");
    ofstream fout1("hist.txt");
    ofstream fout2("histpoi.txt");

    int n_i;
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        zaehler[n_i] += 1;
        
    }
    for (int i = 0; i < 12; ++i) {
      double Warsch = poisson(mu, i)*N;
      fout1 << i << " " << zaehler[i] << "\n";
      fout2 << i << " " << zaehler[i] << " " << Warsch <<"\n";
      std::cout << i << " " << zaehler[i] << " " << Warsch << std::endl;
    }
    fin.close();
    fout1.close();
    fout2.close();
}