#ifndef TEST_POLY_H
#define TEST_POLY_H

#include "list.h"
using namespace std;

class TestPoly
{
public:
    /*Constructor stores string polynomial and calls createPoly() */
    TestPoly(string);
    /*Wrapper for evaluating polynomial value*/
    double evaluatePoly(double x) const;
    /*Wrapper for displaying polynomial*/
    void displayPoly(void) const;
    /*Destructor*/
    ~TestPoly();
private:
    /*Creates the singly linked list with terms of polynomial*/
    void createPoly(string);
    /*Pointer to List object*/
    List *li;
    /*Polynomial string*/
    string polyStr;
};
#endif
