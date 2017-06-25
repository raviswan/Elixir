#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

void groupAnagrams(vector<string>& anag, unordered_map<string, vector<string>>& anagMap){
	for(auto s: anag){
		auto str = s;
		sort(str.begin(),str.end());
		anagMap[str].emplace_back(s);
	}

}
int main(){
	vector<string> anag = {"elvis", "levis", "silent", "lives", "badcredit","freedom","debitcard" };
	unordered_map<string, vector<string>> anagMap;
	groupAnagrams(anag, anagMap);
	for(auto &elem: anagMap){
		for(auto& i: anagMap[elem.first])
			cout<<i<<" ";
		cout<<endl;
	}
	cout<<endl;
}