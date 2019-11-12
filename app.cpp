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
/*
    ifstream file;
    string line;
    long tot_chars = 0;
    long stored_chars = 0;
    int n_correct = 0;
    vector<string> words,missed;
    file.open("google-10000-english.txt");

    clock_t start = clock(); 
    if(file.is_open()){
        while (getline(file, line) && words.size() < 10000) {
            int count = 0;
            line += "#";
            int m = dat->insert(line);
            
            words.push_back(line);
            if(words.size()%100 == 0)
                cout<<"Words inserted : "<<words.size()<<endl;
        }   
    }
    
    start = clock() - start;
    double time_taken = ((double)start/CLOCKS_PER_SEC);
    
    clock_t end = clock();

    for(string s : words){
        int r = dat->retrieval(s);
        if(r == 0)dat->insert(s);
    }

    for(string s : words){
        int r = dat->retrieval(s);
        if(r == 0)missed.push_back(s);
        tot_chars += s.length();
        n_correct += r;
    }
    
    end = clock() - end;
    double time_ret = ((double)end/CLOCKS_PER_SEC);
    double acc = n_correct/(double)words.size()*100;
    
    cout<<"\naccuracy : "<<acc<<endl;
    cout<<"Time taken to insert : "<<time_taken<<"s"<<endl;
    cout<<"Time taken to retrieval : "<<time_ret<<"s"<<endl;
    cout<<"max base  : "<<*max_element(dat->base,dat->base+size)<<endl;
    cout<<"min base  : "<<*min_element(dat->base,dat->base+size)<<endl;
    cout<<"max check  : "<<*max_element(dat->check,dat->check+size)<<endl;
    cout<<"min check  : "<<*min_element(dat->check+1,dat->check+size)<<endl;

    cout<<"base : ";
    for(int i = 1;i < 30;i++)cout<<dat->base[i]<<" ";
    cout<<endl;
    cout<<"check : ";
    for(int i = 1;i < 45;i++)cout<<dat->check[i]<<" ";
    cout<<endl;
    //cout<<"tail : "<<dat->tail<<endl;
    cout<<"Total chars : "<<tot_chars<<endl;
    stored_chars += 2*size + dat->tail.size();
    cout<<"Stored chars : "<<stored_chars<<endl;
    cout<<"TWAIL";

    //FOR STORING INTO ARRAY
    ofstream myfile0 ("base.txt");
    if (myfile0.is_open())
    {
        for(int count = 0; count < size; count ++){
            myfile0 << to_string(dat->base[count]) <<"\n" ;
        }
        cout<<"Base done";
        myfile0.close();
    }
    else cout << "Unable to open file";
    ofstream myfile1 ("check.txt");
    if (myfile1.is_open())
    {
        for(int count = 0; count < size; count ++){
            myfile1 << to_string(dat->check[count]) <<"\n" ;
        }
        cout<<"Done";
        myfile1.close();
    }
    else cout << "Unable to open file";
    ofstream myfile ("tail");
    if (myfile.is_open())
    {
        for(int i=0;i<dat->tail.size();i++)
        myfile<<dat->tail[i];
        cout<<"tail done";
        myfile.close();
    }
    else cout << "Unable to open file";
   
*/

    
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