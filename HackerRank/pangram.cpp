#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

int main() {
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    string s;
    size_t t[26]={0};
    getline(cin,s);
    size_t i= 0;
    char c;
    while(i<s.length()){
        if(s[i]==' '){
            i++;
            continue;
        }
        c = tolower(s[i]);
        t[c-'a'] = 1;
        i++;
    }
    for(int i=0;i<26;i++){
        if(!t[i]){
            cout<<"not pangram"<<endl;
            exit(1);
        }
            
    }
    cout<<"pangram"<<endl;
    return 0;
}