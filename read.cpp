#include <iostream>
#include <fstream>  
#include <vector>
using namespace std;

int main()
{
    std::vector<int> numbers;
    ifstream inputFile("store.txt");
    if (inputFile.good()) {
        int current_number = 0;
        while (inputFile >> current_number){
            numbers.push_back(current_number);
        }
        inputFile.close();
        cout << "The numbers are: ";
        for (int count = 0; count < numbers.size(); count++){
            cout << numbers[count] << " ";
        }
        cout << endl;
    }else {
        cout << "Error!";
        exit(0);
    }
    return 0;
}