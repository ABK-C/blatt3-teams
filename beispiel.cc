#include<iostream>
#include<fstream>
#include<vector>
#include<map>


using namespace std;

int main (){
  vector<string> v;
  std::string s;
  getline(std::cin,s);
  while (s.length()) {
    v.push_back(s);
    getline(std::cin,s);
  }
  //spuckt Eingabewert an [x] ter Stelle aus
  //std::cout << v[0] << "\n";
  std::map<char, int> m;
  for (std::string s : v) {
    for(int j = 0; j< s.length(); ++j) {
      char c = tolower(s[j]);
      m[c]++;
    }
  }
  for(auto kv : m) {
    std::cout << kv.first << ": " << kv.second << "\n";
  }
}