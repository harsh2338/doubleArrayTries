#include <iostream>
#include <bits/stdc++.h>
#include <string>

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
        vector<int> a = string_to_vec(s);
        int i = 0;
        int t = base[r] + a[i];

        if(check[t] != 0){
            int k = check[t];
            vector<int> r_list = set_list(r);
            vector<int> k_list = set_list(k);

            if(r_list.size() + 1 < k_list.size()){
                modify(r,r,a,r_list);
            }
            else{
                vector<int> null;
                modify(r,k,null,k_list);
            }
        }
    }

    void b_insert(int r,string a1, string b1){
        vector<int> a = string_to_vec(a1);
        vector<int> b = string_to_vec(b1);
        int old_pos;
        old_pos = -base[r];

        


    }

    bool retrieval(string x,int *base,int *check,string tail){
        int r=1;
        int h=0;
        int t;
        string s_temp,rem_input_string="";
        while(base[r]<0){
            t=base[r]+x[h];
            if(t>size||check[t]!=r){
                return false;
            }
            else{
                r=t;
            }
            h++;
        }
        if(h==strlen(x.c_str)){
            return true;
        }
        else{
            s_temp=fetch_str(base[r]);
        }
        for(int i=h+1;i<strlen(x.c_str);i++){
            rem_input_string=rem_input_string+x[i];
        }
        if(str_cmp(rem_input_string,s_temp)==-1){
            return true;
        }
        else{
            return false;
        }

    }

    //helper functions here

    int code(char c){   //returns 'a' -> 1,'b' -> 2 etc
        return c - 96;  
    }

    char val(int c){
        return c + 96;
    }

    vector<int> string_to_vec(string s){
        vector<int> v;
        for(int i = 0;i < s.length();i++){
            v.push_back(code(s[i]));
        }
        return v;
    }

    string vec_to_str(vector<int> vec){
        string str;
        for(int i=0;i<vec.size();i++){
            str[i] = val(vec[i]);
        }
        return str;
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
            base[t_new] = base[t];
            check[t_new] = h;

            if(base[t] > 0){
                for(int b : set_list(t)){
                    check[base[t] + b] = t_new;
                }
                if(t == current_s)current_s = t_new;
            }
            base[t] = 0;
            check[t] = 0;
        }
        return current_s;
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
    

    void ins_str(int h,vector<int> a,int d_pos){
        int t, pos;
        vector<int> rem_string;

        t = base[h] + a[0];
        base[t] = -d_pos;
        check[t] = h;

        for(int i=1;i<a.size()-1;i++)
            rem_string.push_back(a[i]);

        pos = str_tail(d_pos, rem_string);
        
    }

    /**r-node no
     * t-subsequent governing node no
     * a-current input symbol
     * K-set of keys(strings)
    */
    string fetch_str(int p){
        string temp="";
        while(tail[p]!='#'){
            temp=temp+tail[p];
            p++;
        }
        temp=temp+"#";
        return temp;
    }
    int str_cmp(string x,string y){
        if(x==y){
            return -1;
        }
        else{
            //return the length of the longest prefix of x and y
        }
        
    }

    //undefined str_tail function
    int str_tail(int p, vector<int> rem_string){
        //no clue what this does, please check
        int pos;
        tail.insert(p, vec_to_str(rem_string));
        if( p = pos)
            return (pos+rem_string.size());
        else
            return pos;
    }
    //x=a1a2a3...anan+1

};
