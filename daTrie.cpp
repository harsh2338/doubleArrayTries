#include<iostream>
#include<bits/stdc++.h>
#include<string>

using namespace std;

class DoubleArrayTrie
{
    int *base,*check,size;
    string tail;
    public:
    DoubleArrayTrie(int size_){
        size = size_;
        base = new int[size];
        check = new int[size];
        for(int i = 0;i < size;i++){
            base[i] = 1;
            check[i] = 0;
        }
    }

    void a_insert(int r,string s){
        int i = 0;
        int t = base[r] + code(s[i]);

        if(check[t] == 0){

        }
        else{
            int k = check[t];
            vector<int> r_list = set_list(r);
            vector<int> k_list = set_list(k);

            if(r_list.size() + 1 < k_list.size()){

            }
        }
        
    }

    //helper functions here

    int code(char c){   //returns 'a' -> 1,'b' -> 2 etc
        return c - 96;  
    }

    vector<int> set_list(int r){
        vector<int> a;
        int k = 1;
        for(int i = 1;i < 27;i++){

            if(base[r] + i >= size)break;

            if(check[base[r] + i] == r){
                a.push_back(i);
            }
        }
        return a;
    }

    int modify(int current_s,int h,vector<int> add,vector<int> org){
        int old_base = base[h];
        vector<int> comb = combine(add,org);
        base[h] = x_check(comb);

        for(int c : org){
            int t = old_base + c;
            int t_new = base[h] + c;

        }
    }

    int x_check(vector<int> a){
        int q = 1,j = 0;
        while(1){
            for(int i : a){
                j++;
                if(check[q+i] != 0)break;
            }
            if(j == a.size())return q;
            q++;
        }
    }

    vector<int> combine(vector<int> add ,vector<int> org){
        vector<int> a;
        for(int i : add)
            a.push_back(i);
        for(int i : org)
            a.push_back(i);
        return a;
    }
    
};