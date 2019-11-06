#include <algorithm>
#include <iterator>
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int data[] = { 1, 2, 3 };

    ofstream out( "store.txt" );
    copy( data, data + 3, ostream_iterator<int>( out, " " ) );
}