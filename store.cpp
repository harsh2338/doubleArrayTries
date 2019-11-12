#include <iostream>
#include <fstream>
using namespace std;

int main () {
  const int size = 5;
  double x[] = {1,2,3,4,5}; 

  ofstream myfile ("example.txt");
  if (myfile.is_open())
  {
    for(int count = 0; count < size; count ++){
        myfile << x[count] <<"\n" ;
    }
    myfile.close();
  }
  else cout << "Unable to open file";
  return 0;
}