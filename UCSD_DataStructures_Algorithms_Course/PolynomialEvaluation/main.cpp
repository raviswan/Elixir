//
//  main.cpp
//  UCSD_HW2
//
//  Created by Ram Viswanathan on 10/16/15.
//  Copyright © 2015 Ram Viswanathan. All rights reserved.
//

#include "list.h"
#include "testPoly.h"

int main(int argc, const char * argv[]) {
	double result,x;
    TestPoly p("6.0 0.0 -5.3 3.1");
    x=7.0;
    result = p.evaluatePoly(x);
    cout<<endl;
    p.displayPoly();
    cout<<" = "<<std::setprecision(15)<<result<<" with "<<"x="<<x<<endl;

    TestPoly p1("1.0 1.0");
    x=1.0;
    result = p1.evaluatePoly(x);
    p1.displayPoly();
    cout<<" = "<<std::defaultfloat<<std::setprecision(15)<<result<<" with "<<"x="<<x<<endl;

    TestPoly p2("1.0 0.0 -1.0");
    x=2.03;
    result = p2.evaluatePoly(x);
    p2.displayPoly();
    cout<<" = "<<std::defaultfloat<<std::setprecision(15)<<result<<" with "<<"x="<<x<<endl;

    TestPoly p3("-3.0 0.5 -2.0 0");
    x=05.0;
    result = p3.evaluatePoly(x);
    p3.displayPoly();
    cout<<" = "<<std::defaultfloat<<std::setprecision(15)<<result<<" with "<<"x="<<x<<endl;

	TestPoly p4("-0.3125 0.0 -9.915 -7.75 -40.0");
	x=123.45;
    result = p4.evaluatePoly(x);
    p4.displayPoly();
    cout<<" = "<<std::defaultfloat<<std::setprecision(15)<<result<<" with "<<"x="<<x<<endl;
    cout<<endl;
    return EXIT_SUCCESS;
}