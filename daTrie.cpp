#include <iostream>
#include <bits/stdc++.h>
#include <string>

using namespace std;

class DoubleArrayTrie
{
    public:
    int *base, *check, size;
    int pos;
    string tail;


    DoubleArrayTrie(int size_)
    {
        size = size_;
        base = new int[size];
        check = new int[size];
        for (int i = 0; i < size; i++)
        {
            base[i] = 0;
            check[i] = 0;
        }
        base[1] = 1;
        pos = 1;
        tail = "";
    }

    void a_insert(int r, string s)
    {
        //r-current node
        //s-remaing part of input string
        cout<<"a_insert"<<endl;
        vector<int> a = string_to_vec(s);
        int i = 0;
        int t = base[r] + a[i];
        if (check[t] != 0)
        {
            int k = check[t];
            vector<int> r_list = set_list(r);
            vector<int> k_list = set_list(k);

            if (r_list.size() + 1 < k_list.size())
            {
                r=modify(r, r, a, r_list);
            }
            else
            {
                vector<int> null;
                r=modify(r, k, null, k_list);
            }
        }
        else
        {
            ins_str(r, a, pos);
        }
    }

    void b_insert(int r, string a1, string b1)
    {
        cout<<"b_insert"<<endl;
        cout<<r<<" "<<a1<<" "<<b1<<endl;
        vector<int> a = string_to_vec(a1);
        vector<int> b = string_to_vec(b1);
        int old_pos;
        old_pos = -base[r];
        int k;
        for (k = 0; a[k] == b[k]; k++);

        for (int i = 0; i < k; i++)
        {
            vector<int> temp = {a[i]};
            base[r] = x_check(temp);
            check[base[r] + a[i]] = r;
            r = base[r] + a[i];
        }
        vector<int> v = {a[k], b[0]};
        base[r] = x_check(v);
        cout<<base[r]<<endl;
        ins_str(r, b, old_pos);
        a = vector<int>(a.begin() + k, a.end());
        ins_str(r, a, pos);
    }

    bool retrieval(string x, int *base, int *check, string tail)
    {
        int r = 1;
        int h = 0;
        int t;
        string s_temp, rem_input_string = "";
        while (base[r] > 0)
        {
            t = base[r] + x[h];

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
            s_temp = fetch_str(base[r]);
        }
        for (int i = h + 1; i < strlen(x.c_str()); i++)
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

    int code(char c)
    { //returns 'a' -> 1,'b' -> 2 etc
        if(c == '#')return 27;
        return c - 96;
    }

    char val(int c)
    {
        if(c == 27)return '#';
        return c + 96;
    }

    vector<int> string_to_vec(string s)
    {
        vector<int> v;
        for (int i = 0; i < s.length(); i++)
        {
            v.push_back(code(s[i]));
        }
        return v;
    }

    string vec_to_str(vector<int> vec)
    {
        string str;
        for (int i = 0; i < vec.size(); i++)
        {
            str += val(vec[i]);
        }
        return str;
    }

    vector<int> set_list(int r)//returns a set of symbols a such that check[base[r] + i] == r
    {
        vector<int> a;
        int k = 1;
        for (int i = 1; i < 27; i++)
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

    int modify(int current_s, int h, vector<int> add, vector<int> org)
    {
        cout<<"modify"<<endl;
        int old_base = base[h];
        vector<int> comb = combine(add, org);
        base[h] = x_check(comb);
        
        for (int c : org)
        {
            int t = old_base + c;
            int t_new = base[h] + c;
            base[t_new] = base[t];
            check[t_new] = h;

            if (base[t] > 0)
            {
                for (int b : set_list(t))
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

    int x_check(vector<int> a)
    {
        cout<<"x_check"<<endl;
        cout<<vec_to_str(a)<<endl;
        int q = 1, j = 0;
        while (1)
        {
            j= 0;
            for (int i : a)
            { 
                if (check[q + i] == 0)
                    j++;
                
            }
            if (j == a.size())
                return q;
            q++;
        }
    }

    vector<int> combine(vector<int> add, vector<int> org)
    {
        vector<int> a;
        for (int i : add)
            a.push_back(i);
        for (int i : org)
            a.push_back(i);
        return a;
    }

    void ins_str(int h, vector<int> a, int d_pos)
    {
        cout<<"ins_str"<<endl;
        int t;
        vector<int> rem_string;

        t = base[h] + a[0];
        base[t] = -d_pos;
        check[t] = h;

        for (int i = 1; i < a.size(); i++)
            rem_string.push_back(a[i]);

        pos = str_tail(d_pos, rem_string);
        cout<<pos<<endl;
    }

    /**r-node no
     * t-subsequent governing node no
     * a-current input symbol
     * K-set of keys(strings)
    */
    string fetch_str(int p)
    {
        cout<<pos<<endl;
        string temp = "";
        while (tail[p] != '#')
        {
            temp = temp + tail[p];
            p++;
        }
        temp = temp + "#";
        return temp;
    }
    int str_cmp(string x, string y)
    {
        if (x == y)
        {
            return -1;
        }
        else
        {
            int n = x.length() < y.length() ? x.length() : y.length();
            for (int i = 0; i < n; i++)
            {
                if (x[i] != y[i])
                    return i;
            }
            return n;
        }
    }

    //undefined str_tail function
    int str_tail(int p, vector<int> rem_string)
    {
        //no clue what this does, please check
        cout<<"str_tail"<<endl;
        for(int i = 0;i < rem_string.size();i++){
            if(tail.length() <= i+p-1)tail += '?';
            tail[i+p-1] = val(rem_string[i]);
        }
        cout<<tail<<endl;
        if (p == pos)
            return (pos + rem_string.size());
        else
            return pos;
    }
    //x=a1a2a3...anan+1


    void insert(string x/*, int *base, int *check, string tail*/)
    {
        cout<<"insert"<<endl;
        int r = 1;
        int h = 0;
        int t;
        string s_temp, rem_input_string = "";
        while (base[r] > 0)
        {
            t = base[r] + code(x[h]);

            if (t > size || check[t] != r)
            {
                string rem;
                for(int i=h;i<x.length();i++)
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
        for (int i = h; i < x.length(); i++)
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
int main(){
    DoubleArrayTrie *dat=new DoubleArrayTrie(100);
    dat->insert("bachelor#");
    dat->insert("bcs#");
    dat->insert("badge#");
    dat->insert("baby#");
    cout<<"base  : ";
    for(int i = 1;i < 10;i++)cout<<dat->base[i]<<" ";
    cout<<endl;
    cout<<"check : ";
    for(int i = 1;i < 10;i++)cout<<dat->check[i]<<" ";
    cout<<endl;

}
