computeNextValue(vector<int> a){
	++a.back();
	for(int i=a.size() -1 ; i>0 && a[i]== 10 ; i--){
		a[i]=0;
		++a[i-1];
	}
	if a[0]==10{
		a[0] = 0;
		a.insert(a.begin(),1);
	}

	return a;
}

int main(){
	
}