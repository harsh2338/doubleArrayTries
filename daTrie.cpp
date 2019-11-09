 
#include <iostream>
#include <bits/stdc++.h>
#include <string> 
#include<fstream>
#include<time.h>

using namespace std;

class DoubleArrayTrie
{
    public:
    long *base, *check;
    long size;    
    long pos;
    string tail;


    DoubleArrayTrie(long size_)
    {
        size = size_;
        base = new long[size];
        check = new long[size];
        for (long i = 0; i < size; i++)
        {
            base[i] = 0;
            check[i] = 0;
        }
        base[1] = 1;
        pos = 1;
        tail = "";
    }

    void a_insert(long r, string s)
    {
        //r-current node
        //s-remaing part of input string
        vector<long> a = string_to_vec(s);
        long i = 0;
        long t = base[r] + a[i];
        if (check[t] != 0)
        {
            long k = check[t];
            vector<long> r_list = set_list(r);
            vector<long> k_list = set_list(k);

            if (r_list.size() + 1 < k_list.size())
            {
                r=modify(r, r, a, r_list);
            }
            else
            {
                vector<long> null;
                r=modify(r, k, null, k_list);
            }
        }
        ins_str(r, a, pos);
    }

    void b_insert(long r, string a1, string b1)
    {
        vector<long> a = string_to_vec(a1);
        vector<long> b = string_to_vec(b1);
        long old_pos;
        old_pos = -base[r];
        long k;
        for (k = 0; a[k] == b[k]; k++);

        for (long i = 0; i < k; i++)
        {
            vector<long> temp = {a[i]};
            base[r] = x_check(temp);
            check[base[r] + a[i]] = r;
            r = base[r] + a[i];
        }
        vector<long> v = {a[k], b[0]};
        base[r] = x_check(v);
        ins_str(r, b, old_pos);
        a = vector<long>(a.begin() + k, a.end());
        ins_str(r, a, pos);
    }

    bool retrieval(string x)
    {
        long r = 1;
        long h = 0;
        long t;
        string s_temp, rem_input_string = "";
        while (base[r] > 0)
        {
            t = base[r] + code(x[h]);

            if (t > size || check[t] != r)
            {
                return false; //if the next state is not present
            }
            else
            {
                r = t;
            }
            h++;
        }
        if (h == strlen(x.c_str()))
        {
            return true;
        }
        else
        {
            s_temp = fetch_str(-base[r] - 1);
        }
        for (long i = h; i < strlen(x.c_str()); i++)
        {
            rem_input_string = rem_input_string + x[i];
        }
        if (str_cmp(rem_input_string, s_temp) == -1)
        {
            return true;
        }
        else
        {
            return false; //if the multinode is not same as the remaining part of the string
        }
    }

    //helper functions here

    long code(char c)
    { //returns 'a' -> 1,'b' -> 2 etc
        if(c == '#')return 27;
        return c - 96;
    }

    char val(long c)
    {
        if(c == 27)return '#';
        return c + 96;
    }

    vector<long> string_to_vec(string s)
    {
        vector<long> v;
        for (long i = 0; i < s.length(); i++)
        {
            v.push_back(code(s[i]));
        }
        return v;
    }

    string vec_to_str(vector<long> vec)
    {
        string str;
        for (long i = 0; i < vec.size(); i++)
        {
            str += val(vec[i]);
        }
        return str;
    }

    vector<long> set_list(long r)//returns a set of symbols a such that check[base[r] + i] == r
    {
        vector<long> a;
        long k = 1;
        for (long i = 1; i < 27; i++)
        {

            if (base[r] + i >= size)
                break;

            if (check[base[r] + i] == r)
            {
                a.push_back(i);
            }
        }
        return a;
    }

    long modify(long current_s, long h, vector<long> add, vector<long> org)
    {
        long old_base = base[h];
        vector<long> comb = combine(add, org);
        base[h] = x_check(comb);
        
        for (long c : org)
        {
            long t = old_base + c;
            long t_new = base[h] + c;
            base[t_new] = base[t];
            check[t_new] = h;

            if (base[t] > 0)
            {
                for (long b : set_list(t))
                {
                    check[base[t] + b] = t_new;
                }
                if (t == current_s)
                    current_s = t_new;
            }
            base[t] = 0;
            check[t] = 0;
        }
        return current_s;
    }

    long x_check(vector<long> a)
    {
        long q = 1, j = 0;
        while (1)
        {
            j= 0;
            for (long i : a)
            { 
                if (check[q + i] == 0)
                    j++;
                
            }
            if (j == a.size())
                return q;
            q++;
        }
    }

    vector<long> combine(vector<long> add, vector<long> org)
    {
        vector<long> a;
        for (long i : add)
            a.push_back(i);
        for (long i : org)
            a.push_back(i);
        return a;
    }

    void ins_str(long h, vector<long> a, long d_pos)
    {
        long t;
        vector<long> rem_string;

        t = base[h] + a[0];
        base[t] = -d_pos;
        check[t] = h;

        for (long i = 1; i < a.size(); i++)
            rem_string.push_back(a[i]);

        pos = str_tail(d_pos, rem_string);
    }

    /**r-node no
     * t-subsequent governing node no
     * a-current input symbol
     * K-set of keys(strings)
    */
    string fetch_str(long p)
    {
        string temp = "";
        while (tail[p] != '#')
        {
            temp = temp + tail[p];
            p++;
        }
        temp = temp + "#";
        return temp;
    }
    long str_cmp(string x, string y)
    {
        if (x == y)
        {
            return -1;
        }
        else
        {
            long n = x.length() < y.length() ? x.length() : y.length();
            for (long i = 0; i < n; i++)
            {
                if (x[i] != y[i])
                    return i;
            }
            return n;
        }
    }

    //undefined str_tail function
    long str_tail(long p, vector<long> rem_string)
    {
        //no clue what this does, please check
        for(long i = 0;i < rem_string.size();i++){
            if(tail.length() <= i+p-1)tail += '?';
            tail[i+p-1] = val(rem_string[i]);
        }
        if (p == pos)
            return (pos + rem_string.size());
        else
            return pos;
    }
    //x=a1a2a3...anan+1


    void insert(string x/*, long *base, long *check, string tail*/)
    {
        long r = 1;
        long h = 0;
        long t;
        string s_temp, rem_input_string = "";
        while (base[r] > 0)
        {
            t = base[r] + code(x[h]);

            if (t > size || check[t] != r)
            {
                string rem;
                for(long i=h;i<x.length();i++)
                    rem.push_back(x[i]);
                a_insert(r,rem); //if the next state is not present
                return;
            }
            else
            {
                r = t;
            }
            h++;
        }
        if (h == x.length())
        {
            return ;
        }
        else
        {
            s_temp = fetch_str(-base[r] - 1);
        }
        for (long i = h; i < x.length(); i++)
        {
            rem_input_string = rem_input_string + x[i];
        }
        if (str_cmp(rem_input_string, s_temp) == -1)
        {
            return ;
        }
        else
        {
            b_insert(r,rem_input_string,s_temp); //if the multinode is not same as the remaining part of the string
        }
    }
};
long main(){
    DoubleArrayTrie *dat=new DoubleArrayTrie(30000);
    ifstream file;
    string line;
    vector<string> words;
    file.open("google-10000-english.txt");
    clock_t start = clock(); 
    if(file.is_open()){
        while (getline(file, line) && words.size() < 4000) {
            line += "#";
            dat->insert(line);
            words.push_back(line);
            if(words.size() == 150)
                cout<<"Words inserted : "<<words.size()<<endl;
        }   
    }
    
    start = clock() - start;
    double time_taken = ((double)start/CLOCKS_PER_SEC);
    long n_correct = 0;
    clock_t end = clock();
    for(string s : words){
        if(!dat->retrieval(s)){
            dat->insert(s);
        }
        n_correct += dat->retrieval(s);
        
    }
    end = clock() - end;
    double time_ret = ((double)end/CLOCKS_PER_SEC);
    double acc = (double)n_correct/words.size()*100.0;
    cout<<"accuracy : "<<acc<<endl;
    cout<<"Time taken to insert : "<<time_taken<<endl;
    cout<<"Time taken to retrieval : "<<time_ret<<endl;
    cout<<"base  : ";
    for(long i = 1;i < 10;i++)cout<<dat->base[i]<<" ";
    cout<<endl;
    cout<<"check : ";
    for(long i = 1;i < 10;i++)cout<<dat->check[i]<<" ";
    cout<<endl;
    //cout<<"tail : "<<dat->tail<<endl;
}