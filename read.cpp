#include<bits/stdc++.h> 

using namespace std;

int main()
{
    fstream inputFile,outputFile; 
    string word, t, q, filename; 
    filename = "store.txt"; 
    int len;
    inputFile.open(filename.c_str()); 
    outputFile.open("misspelt.txt");
    while (inputFile >> word) 
    { 
        transform(word.begin(), word.end(), word.begin(), ::tolower); 
        len=word.size();
        if (ispunct(word[len-1])) 
        { 
            word.erase(len-1, 1);
            len = word.size(); 
        } 
        remove(word.begin(), word.end(), ' ');
        outputFile<<word<<"\n"; 
    } 
  
    return 0; 
    /*
    std::vector<string> words;
    ifstream inputFile("store.txt");
    if (inputFile.good()) {
        string current_number = 0;
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
    return 0;*/
}