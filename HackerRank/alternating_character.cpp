#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;


int main() {
    vector<string> v;
    string s;
    char c;
    size_t i,j,count,delCount;
    j=0;
    getline(cin,s);
    count = stoi(s);

    while(getline(cin,s) ){
         v.push_back(s);
         cout<<v[j]<<endl;
         j++;
         if(j==count)
            break;
    }

    j=0;
  
    while(j<count){
        s = v[j];
        c = s[0];
         delCount = 0;
         i = 1;
         while(i<s.length()){
            switch(c){
                case 'A':
                    c='B';
                    break;
                case 'B':
                    c='A';
                    break;
                default:
                     exit(1);
            }
            //cout<<"c="<<c<<endl;
            while(i<s.length() && s[i]!=c){
                ++delCount;
                i++;
            }
            if(i==s.length())
                 break;
             else{
                 c = s[i];
                 i++;
             }
            
         }
        cout<<delCount<<endl;
        j++;
    }
   
   
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}