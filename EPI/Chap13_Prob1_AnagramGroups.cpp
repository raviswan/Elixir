#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;
void groupAnagrams(vector<string>& anag, unordered_map<string, vector<string>>& anagMap){
	for(auto s: anag){
		auto c = s;
		c.sort(c.begin(),c.end());
		if(anagMap.find(c) != anagMap.end()){
			anagMap[c].emplace_back(s);
		}
		else{
			anagMap.insert(make_pair<string,string>(c,s));
		}

	}
int main(){
	vector<string> anag = {"elvis", "levis", "silent", lives", "badcredit"freedom","debitcard" }
	unordered_map<string, vector<string>> anagMap;
	groupAnagrams(anag, anagMap);
	for(auto &c: anagMap){
		for(auto& i: anagMap[c])
			cout<<i<<" ";
	}
	cout<<endl;
}