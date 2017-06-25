/*
Given a string of lowercase letters, determine the index of the character whose removal will make the string a palindrome. If the string is already a palindrome, then print −1−1. There will always be a valid solution.

Input Format

The first line contains TT (the number of test cases). 
The TT subsequent lines of test cases each contain a single string to be checked.

Constraints 
1≤T≤201≤T≤20 
1≤1≤ length of string ≤100005≤100005 
All characters are Latin lower case indexed.

Output Format

Print the zero-indexed position (integer) of a character whose deletion will result in a palindrome; if there is no such character (i.e.: the string is already a palindrome), print -1. Any correct answer will be accepted; e.g.: for a string such as bcbc, we can either remove b at index 00 or c at index 33—both answers are acceptable.

Sample Input

3
aaab
baa
aaa

Sample Output

3
0
-1
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    vector<string> v;
    string str;
    long i,j;
    cin>>n;
    bool flag;
    for(int k=0;k<n;k++){
        cin>>str;
        v.emplace_back(str);
    }
    for(string& str: v){
        flag = true;
        i=0;
        j=str.size()-1;
        while(i<=j){
            if(str[i]!=str[j]){
                 if(str[i+1]==str[j] && str[i+2]==str[j+1] ){
                    flag=false;
                    cout<<i<<endl;
                    break;
                 }
                 
                 if(str[i]==str[j-1] && str[i+1]==str[j-2]){
                    flag=false;
                    cout<<j<<endl;
                    break;
                 }
                 
            }
            i++;
            j--;
        }
        if(flag)
            cout<<-1<<endl;
        
        
    }
    return 0;
}