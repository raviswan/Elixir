#include <iostream>
#include <vector>
#include <array>
using namespace std;

unique_ptr<vector<int>> getMaxCount(const vector<int>& pointsAllowed, int totalPoints ){
	unique_ptr<vector<int>> maxValPtr = make_unique<vector<int>>();
	for(auto& i: pointsAllowed){
		maxValPtr->emplace_back((int)totalPoints/i);
	}
	return maxValPtr;
}


unique_ptr<vector<pair<int,int>>> formPair(const vector<int>& pointsAllowed,
	vector<int>* maxVector){
	int index = 0;
	unique_ptr<vector<pair<int,int>>> vPair = make_unique<vector<pair<int,int>>>();
	for(auto&i : pointsAllowed){
		vPair->emplace_back(make_pair(i,(*maxVector)[index]));
		++index;
	}
	return vPair;

}

void computePlayPoints(vector<pair<int,int>>* pPair,  vector<vector<int>>* pMap ) {
	int row = 0;
	vector<int> v;
	for(auto&i : *pPair){
		v.clear();
		for(int k= 0; k<=i.second; ++k){
			v.emplace_back(i.first*k);
		}
		pMap->emplace_back(v);
	}
}

// void computeComboHelper(int i, vector<vector<int>>* pVec, vector<int>* loopRes, 
// 					vector<vector<int>>* result, int* matchCount, int totalPoints ){
// 	if (loopRes->size() == (*pVec).size()){
// 		int sum = 0;
// 		for(auto& j: *loopRes){
// 			sum += j;
// 		}
// 		if (sum == totalPoints){
// 			(*result).emplace_back(*loopRes);
// 			++*matchCount;
// 		}
// 		return;
// 	}
// 	for(int k = 0; k <  (*pVec)[i].size() ; ++k){
// 		loopRes->emplace_back((*pVec)[i][k]);
// 		computeComboHelper(i+1, pVec, loopRes, result, matchCount, totalPoints);
// 		loopRes->erase(loopRes->end()-1);
// 	}

// }



void computeComboHelper(int i, const vector<int>& points, vector<int>* maxVec, 
						vector<int>* loopRes, vector<pair<int,int>>* comboRes,
						vector<vector<int>>* result, vector<vector<pair<int,int>>>* result2,
					  	int* matchCount, int totalPoints ){
	if (loopRes->size() == points.size()){
		int sum = 0;
		for(auto& j: *loopRes){
			//cout<<j<<" ";
			sum += j;
		}
		//cout<<endl;
		if (sum == totalPoints){
			(*result).emplace_back(*loopRes);
			(*result2).emplace_back(*comboRes);
			++*matchCount;
		}
		return;
	}
	for(int k = 0; k <=  (*maxVec)[i] ; ++k){
		loopRes->emplace_back(points[i]* k);
		comboRes->emplace_back(make_pair(points[i], k));
		computeComboHelper(i+1, points, maxVec, loopRes, comboRes, result, result2,  matchCount, totalPoints);
		loopRes->erase(loopRes->end()-1);
		comboRes->erase(comboRes->end() - 1);
	}

}

void printVector(vector<int>* p){
	for (auto i:*p){
		cout<<i<<" ";
	}
	cout<<endl;
}

void printVector(vector<int> p){
	for (auto i:p){
		cout<<i<<" ";
	}
	cout<<endl;
}

void printVector(vector<pair<int,int>> p){
	for (auto i:p){
		cout<<i.first<<" "<<i.second<<" ";
	}
	cout<<endl;
}


int main(){
	int totalPoints = 20	;
	int index;
	int matchCount = 0;
	vector<int> pointsAllowed = {2,3,7};
	cout<<"Total Points "<<totalPoints<<endl;
	for (int i: pointsAllowed){
		cout<<i<<" ";
	}
	cout<<endl;
	unique_ptr<vector<int>> maxVector = getMaxCount(pointsAllowed, totalPoints);
	unique_ptr<vector<pair<int,int>>> pointPair = formPair(pointsAllowed, maxVector.get());
	unique_ptr<vector<vector<int>>> pVec = make_unique< vector<vector<int>> >();
	unique_ptr< vector<vector<int>>> result = make_unique< vector<vector<int>> >();
	unique_ptr<vector<vector<pair<int,int>>>> result2 = make_unique<vector<vector<pair<int, int>>>>();
	vector<int> loopRes;
	vector<pair<int,int>> comboRes;
	cout<<"max vector"<<endl;
	printVector(*maxVector.get());
	cout<<"----------"<<endl;
	computePlayPoints(pointPair.get(), pVec.get());
	index = 0;
	// for(int i = 0; i <  (*pVec).size() ; ++i){
	// 	printVector((*pVec)[i]);
	// }
	//computeComboHelper(0, pVec.get(), &loopRes, result.get(), &matchCount, totalPoints);


	 computeComboHelper(0, pointsAllowed, maxVector.get(), &loopRes, &comboRes, result.get(), result2.get(),
	 					 &matchCount, totalPoints);

	cout<<"Total matches = "<<matchCount<<endl;
	 // for(int i = 0; i <  (*result).size() ; ++i){
	 // 	printVector((*result)[i]);
	 // }
	 for(int i = 0; i <  (*result2).size() ; ++i){
	 	printVector((*result2)[i]);
	 }
	return 1;
}