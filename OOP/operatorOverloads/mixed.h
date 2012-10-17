/* File: mixed,h
   Author: Shamari Feaster
   Description: Objects of type Mixed will store and manage rational numbers 
   in a mixed number format (integer part and a fraction part).  
*/
#include <iostream>		
using namespace std;

class Mixed {
    friend istream& operator >> (istream& is, Mixed& f);
    friend ostream& operator << (ostream& os, const Mixed& f); 
    friend bool operator<(const Mixed& l, const Mixed& r);
    friend bool operator>(const Mixed& l, const Mixed& r);
    friend bool operator<=(const Mixed& l, const Mixed& r);
    friend bool operator>=(const Mixed& l, const Mixed& r);
    friend bool operator==(const Mixed& l, const Mixed& r);
    friend bool operator!=(const Mixed& l, const Mixed& r);
    friend Mixed operator+(const Mixed& l, const Mixed& r);
    friend Mixed operator-(const Mixed& l, const Mixed& r);
    friend Mixed operator*(const Mixed& l, const Mixed& r);
    friend Mixed operator/(const Mixed& l, const Mixed& r);
    friend int abs_value(const int i);
    /*finds the absolute value of an integer*/
    friend bool is_improper(const Mixed& f);
    /*tests to see if a fraction is improper*/
public:
    Mixed(int integer=0);
    Mixed(int integer, int numerator, int denominator);  
   void ToFraction();
    /* Converts the mixed number into fraction form. */
    void Simplify();
    /* Simplifies the mixed number representation to lowest terms.
       the fraction part should be reduced to lowest terms, and the 
       fraction part should not be an improper fraction*/
    double Evaluate();
    /*Converts a mixed number to decimal*/
    void ImproperToMixed();
    /*converts an improper fraction to a mixed number */
private:
    int integer;
    int numerator;
    int denominator;

};
