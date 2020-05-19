#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

double mu = 3.11538;
int ndof = 233;
double Schritte = 0.01;

double prob(std::vector<int> daten, double mu) {
  double Likelihood = 1;
  for (int k : daten){
    double mu_k = pow(mu, k);
    double exp_mu = exp(-mu);
    double k_Fak = tgamma(k+1);
    double Poisson = mu_k * exp_mu * (1/(k_Fak));
    Likelihood = Likelihood * Poisson;
 }
  return Likelihood;
}

double Likelihood_k(std::vector<int> daten, double mu) {
  double Likelihood_k = 1;
  for (int k : daten){
    mu = k;
    double k_k = pow(k, k);
    double exp_k = exp(-k);
    double k_Fak = tgamma(k+1);
    double Poisson_k = k_k * exp_k * (1/(k_Fak));
    Likelihood_k = Likelihood_k * Poisson_k;
 }
 return Likelihood_k;
}



int main() {
    using namespace std;
    
    ofstream fout1("likelihood.txt");
    ofstream fout2("nll.txt");
    ofstream fout3("deltanll.txt");
    ifstream fin("datensumme.txt");
    int n_i;
    std::vector<int> daten;
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        daten.push_back(n_i);  
    }
    double likelihood = prob(daten, mu);
    std::cout << likelihood << std::endl;
    for (double mue = 0 ; mue < 6 ; mue = mue + Schritte) {
      double likelihood = prob(daten, mue);
      fout1 << mue << " " << likelihood << "\n";
      double likelihood_2 = -2* log (likelihood);
      fout2 << mue << " " << likelihood_2 << "\n";
      double likelihood_3 = -2* log (likelihood) - -2* log(prob(daten,mu));
      fout3 << mue << " " << likelihood_3 << "\n";
    }
    double quotient = prob(daten,mu)/Likelihood_k(daten,mu);
    std::cout << -2*log(quotient) << std::endl;
    double z = (-2*log(quotient)-ndof)/(sqrt(2*ndof));
    std::cout << z << std::endl;
    fin.close();
    fout1.close();
    fout2.close();
    fout3.close();
    // Die Suche in der Ausgabe-Datei "likelihood.txt" ergibt ein Maximum bei mue=3.12, in "nll.txt" ein Minimum bei mue=3.12 und bei "deltanll.txt" ein Minimum bei mue=3.12
    //Fehlergrenze = +- 0.12
}