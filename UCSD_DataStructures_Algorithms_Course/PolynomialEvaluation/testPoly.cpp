#include "testPoly.h"
#include <cstring>

TestPoly::TestPoly(string p) : polyStr(p){
	createPoly(this->polyStr);
}

TestPoly:: ~TestPoly(){
	cout<<"~TestPoly() invoked"<<"\n";
	if(li){
		li->destroyList();
		delete li;
	}
}

void TestPoly::createPoly(string p){
	//cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	size_t strPos;
	double term;
	li = new List();
	while(!p.empty()){
		/*extract next occuring double & return position after that double*/
		term = stod(p,&strPos);
		li->appendTerm(term);
		/*form a new substring leaving out already extracted double*/
		p = p.substr(strPos);
	}
}

double TestPoly::evaluatePoly(double x) const{
	return (li->evaluate(x));
}

void TestPoly::displayPoly(void) const{
	li->display();
}
