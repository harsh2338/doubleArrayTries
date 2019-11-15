#include "daTrie.h"
#include<bits/stdc++.h>
using namespace std;
class Application{
    public :
        fstream inputFile,outputFile; 
        string filename;
        string processWord(string word);

};
string Application::processWord(string word){
    transform(word.begin(), word.end(), word.begin(), ::tolower); 
    int len=word.size();
    if (ispunct(word[len-1])) 
    { 
        word.erase(len-1, 1);
        len = word.size(); 
    } 
    remove(word.begin(), word.end(), ' ');
    return word;
}

int main(){
    int size = 30000;
    DoubleArrayTrie *dat=new DoubleArrayTrie(size);

    
    //FOR RETRIEVING FROM ARRAY
    ifstream inputFile("base.txt"),inputFile1("check.txt"),inputFile2("tail.txt");
    
    if (inputFile2.good()) {
        int i=0;
        char ch;
        for(int i=0;i<28317;i++){
            inputFile2>>ch;
            dat->tail.push_back(ch);
        }
        inputFile2.close();
    }
    else {
        cout << "Error!";
        exit(0);
    }  
    if (inputFile.good()) {
        int current_number;
        int i=0;
        while (inputFile >> current_number){
            dat->base[i]=current_number;
            i++;
        }
        inputFile.close();
    }
    else {
        cout << "Error!";
        exit(0);
    }

    if (inputFile1.good()) {
        int current_number;
        int j=0;
        while (inputFile1 >> current_number){
            dat->check[j]=current_number;
            j++;
        }
        inputFile1.close();

    }else {
        cout << "Error!";
        exit(0);
    }
    
    Application *app=new Application();
    string word;
    cout<<"Enter name of input file\n";
    cin>>app->filename;
    app->inputFile.open(app->filename.c_str()); 
    app->outputFile.open("misspelt.txt",std::fstream::in | std::fstream::out | std::fstream::app);
    while (app->inputFile >> word) 
    { 
       word=app->processWord(word);
        word=word+"#";
        if(!dat->retrieval(word)){
            app->outputFile<<word<<"\n"; 
        }
        word="";
    } 
    app->outputFile.close();
    app->inputFile.close();
    
}