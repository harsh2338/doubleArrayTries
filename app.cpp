#include "daTrie"
#include<bits/stdc++.h>
using namespace std;
class Application{
    public :
        fstream inputFile,outputFile; 
        string filename;
        void processWord(string word);

};
void Application::processWord(string word){
    transform(word.begin(), word.end(), word.begin(), ::tolower); 
    int len=word.size();
    if (ispunct(word[len-1])) 
    { 
        word.erase(len-1, 1);
        len = word.size(); 
    } 
    remove(word.begin(), word.end(), ' ');
}

int main(){
    daTrie *dat=new daTrie();
    Application *app=new Application();
    string word;
    cout<<"Enter name of input file";
    cin>>app->filename;
    app->inputFile.open(app->filename.c_str()); 
    app->outputFile.open("misspelt.txt");
    while (app->inputFile >> word) 
    { 
        app->processWord(word);
        if(!dat->retrieval(word))
            outputFile<<word<<"\n"; 
    } 
}