/* File: mixed.cpp
   Author: Shamari Feaster
   Description: This class stores mied numbers and performs 
   various operations on those numbers
*/

#include <iostream>
#include "mixed.h"

using namespace std;


//-----------------------------------------------------------
Mixed::Mixed(int i)
{
    integer = i;
    numerator = 0;
    denominator = 1;
}
//-----------------------------------------------------------
Mixed::Mixed(int i, int n, int d)
{
    
    if(
       (i > 0 && n < 0) || 
       (d <= 0 )|| 
       (i < 0 && n < 0)
      )
    {
        integer = 0;
        numerator = 0;
        denominator = 1;
    }
    else
    {       
        integer = i;     
        numerator = n;
        denominator = d;
    }
    
}
//-----------------------------------------------------------
istream& operator >> (istream& is, Mixed& f)
{
    /*
    overloads >> operator to allow input of mied numbers.
    my if statement below sets the mixed # to 0
    if certain conditions are met.
    */
    
    char slash;
    is >> f.integer >> f.numerator >> slash >> f.denominator; 
    if(
      (f.denominator <= 0) ||        //denominator 0 or '-' in wrong place
      (f.integer >= 1 && f.numerator < 0) || // '-' in wrong place
      (f.integer < 0 && f.numerator < 0) //two '-' symbols
      )
    {
        f.integer = 0;
        f.numerator = 0;
        f.denominator = 1;
    }

    
    return is;

}
//-------------------------------------------
ostream& operator << (ostream& os, const Mixed& f)
{
    /*
    overloads << operator to allow output of mied numbers.
    if else ladder to allow for standardized output
    under certain conditions.
    */
    if(f.integer == 0 && f.numerator == 0 && f.denominator == 1)
    {
        os << 0 << endl;
    }
    else
    if(f.integer == 0)
    {
        os << f.numerator << "/" << f.denominator 
       << endl;
    }
    else
    if(f.numerator == 0)
    {
        os << f.integer << endl;
    }
    else
        os << f.integer << " " << f.numerator << "/" << f.denominator << endl;
    
    return os;
} 

//-------------------------------------------
bool operator<(const Mixed& l, const Mixed& r)
{
    int lcm;       //least common multiple
    int temp_num_L;//temportary numerator left (l)
    int temp_num_R;//temportary numerator right (r)
    Mixed tmL = l;
    Mixed tmR = r;
    tmL.ToFraction();
    tmR.ToFraction();
    
    lcm = tmL.denominator * tmR.denominator;
    temp_num_L = tmL.numerator * (lcm/tmL.denominator); 
    temp_num_R = tmR.numerator * (lcm/tmR.denominator); 
    if(temp_num_L < temp_num_R)
        return true;
    else
        return false;
}

//-------------------------------------------
bool operator>(const Mixed& l, const Mixed& r)
{
    int lcm;       //least common multiple
    int temp_num_L;//temportary numerator left (l)
    int temp_num_R;//temportary numerator right (r)
    Mixed tmL = l;
    Mixed tmR = r;
    tmL.ToFraction();
    tmR.ToFraction();
    
    lcm = tmL.denominator * tmR.denominator;
    temp_num_L = tmL.numerator * (lcm/tmL.denominator); 
    temp_num_R = tmR.numerator * (lcm/tmR.denominator); 
    if(temp_num_L > temp_num_R)
        return true;
    else
        return false;
}

//-------------------------------------------
bool operator<=(const Mixed& l, const Mixed& r)
{
    int lcm;       //least common multiple
    int temp_num_L;//temportary numerator left (l)
    int temp_num_R;//temportary numerator right (r)
    Mixed tmL = l;
    Mixed tmR = r;
    tmL.ToFraction();
    tmR.ToFraction();
    
    lcm = tmL.denominator * tmR.denominator;
    temp_num_L = tmL.numerator * (lcm/tmL.denominator); 
    temp_num_R = tmR.numerator * (lcm/tmR.denominator); 
    if(temp_num_L <= temp_num_R)
        return true;
    else
        return false; 
}
//-----------------------------------------------------------
bool operator>=(const Mixed& l, const Mixed& r)
{
    int lcm;       //least common multiple
    int temp_num_L;//temportary numerator left (l)
    int temp_num_R;//temportary numerator right (r)
    Mixed tmL = l;
    Mixed tmR = r;
    tmL.ToFraction();
    tmR.ToFraction();
    
    lcm = tmL.denominator * tmR.denominator;
    temp_num_L = tmL.numerator * (lcm/tmL.denominator); 
    temp_num_R = tmR.numerator * (lcm/tmR.denominator); 
    if(temp_num_L >= temp_num_R)
        return true;
    else
        return false;
}
//-----------------------------------------------------------
bool operator==(const Mixed& l, const Mixed& r)
{
    int lcm;       //least common multiple
    int temp_num_L;//temportary numerator left (l)
    int temp_num_R;//temportary numerator right (r)
    Mixed tmL = l;
    Mixed tmR = r;
    tmL.ToFraction();
    tmR.ToFraction();
    
    lcm = tmL.denominator * tmR.denominator;
    temp_num_L = tmL.numerator * (lcm/tmL.denominator); 
    temp_num_R = tmR.numerator * (lcm/tmR.denominator); 
    if(temp_num_L == temp_num_R)
        return true;
    else
        return false; 
}
//-----------------------------------------------------------
bool operator!=(const Mixed& l, const Mixed& r)
{
    int lcm;       //least common multiple
    int temp_num_L;//temportary numerator left (l)
    int temp_num_R;//temportary numerator right (r)
    Mixed tmL = l;
    Mixed tmR = r;
    tmL.ToFraction();
    tmR.ToFraction();
    
    lcm = tmL.denominator * tmR.denominator;
    temp_num_L = tmL.numerator * (lcm/tmL.denominator); 
    temp_num_R = tmR.numerator * (lcm/tmR.denominator); 
    if(temp_num_L != temp_num_R)
        return true;
    else
        return false; 
}
//-----------------------------------------------------------
/*
    Comments on arithmetic overloads:
    Since I dont want my arithmetic operators to modify the
    operands they are passed in by constant reference. But 
    the most efficient way to do artithmatic on mixed
    numbers is to convert them to improper fractions first.
    This is why I created local copies of the operands in
    my overloads. They are called tmL and tmR.

*/
Mixed operator+(const Mixed& l, const Mixed& r)
{
    Mixed tm1;     //returned object
    int lcm;       //least common multiple
    int temp_num_L;//temportary numerator left (l)
    int temp_num_R;//temportary numerator right (r)

    Mixed tmL = l;
    Mixed tmR = r;
    tmL.ToFraction();
    tmR.ToFraction();
    
    lcm = tmL.denominator * tmR.denominator;

    temp_num_L = tmL.numerator * (lcm/tmL.denominator); 
    temp_num_R = tmR.numerator * (lcm/tmR.denominator); 
    tm1.numerator = temp_num_L + temp_num_R;   
    tm1.denominator = lcm;
    
    if(is_improper(tm1))
        tm1.ImproperToMixed();
    tm1.Simplify();
    return tm1;
}
//-----------------------------------------------------------
Mixed operator-(const Mixed& l, const Mixed& r)
{
    Mixed tm1;     //returned object
    int lcm;       //least common multiple
    int temp_num_L;//temportary numerator left (l)
    int temp_num_R;//temportary numerator right (r)

    Mixed tmL = l;
    Mixed tmR = r;
    tmL.ToFraction();
    tmR.ToFraction();
    
    lcm = tmL.denominator * tmR.denominator;

    temp_num_L = tmL.numerator * (lcm/tmL.denominator); 
    temp_num_R = tmR.numerator * (lcm/tmR.denominator); 
    tm1.numerator = temp_num_L - temp_num_R;   
    tm1.denominator = lcm;
    
    if(is_improper(tm1))
        tm1.ImproperToMixed();
    tm1.Simplify();
    return tm1;
}
//-----------------------------------------------------------
Mixed operator*(const Mixed& l, const Mixed& r)
{
    Mixed tm1;          //returned object
    int product_numerator;
    int product_denominator;
    Mixed tmL = l;
    Mixed tmR = r;
    tmL.ToFraction();
    tmR.ToFraction();
    product_numerator = tmL.numerator * tmR.numerator;
    product_denominator = tmL.denominator * tmR.denominator;
    tm1.numerator = product_numerator;
    tm1.denominator = product_denominator;
     
    if(is_improper(tm1))
        tm1.ImproperToMixed();
    tm1.Simplify();
    return tm1;
}
//-----------------------------------------------------------
Mixed operator/(const Mixed& l, const Mixed& r)
{
    Mixed tm1;          //returned object

    int temp;//temporarily stores numerator to allow for swap
    int product_numerator;
    int product_denominator;
    
    Mixed tmL = l;
    Mixed tmR = r;
    tmL.ToFraction();
    tmR.ToFraction();
    
    temp = tmR.numerator;
    tmR.numerator = tmR.denominator;
    tmR.denominator = temp;
    product_numerator = tmL.numerator * tmR.numerator;
    product_denominator = tmL.denominator * tmR.denominator;
    tm1.numerator = product_numerator;
    tm1.denominator = product_denominator;
    
    if(is_improper(tm1))
        tm1.ImproperToMixed();
    tm1.Simplify();
    return tm1;
}

void Mixed::ToFraction()
{
    /*converts the mixed number into fraction form*/
    if (integer != 0 && integer > 0)
    {
        //if its a positive mixed #
        numerator = (denominator * integer) + numerator;
        integer = 0;
    }
    else if(integer != 0 && integer < 0)
    {
        //if it's a negative mixed #
        numerator = (denominator *  integer) + (-1 * numerator);
        integer = 0;   
    }
}
//-----------------------------------------------------------
void Mixed::Simplify()
{
    /*Uses Euclid's Algo to reduce fractions to lowest terms*/
    int n = numerator;//numerator
    int d = denominator;//denomitor
    int r = 1;//remainder
    int gcd;//greatest common divisor
    int old_n;//old numerator
    int old_d;//old denominator
    int ltn;//lowest terms numerator
    int ltd;//lowest terms denominator
    
    //stores user input before calculations
    old_n = n;
    old_d = d;
    //reverse n & d if fraction is improper
    if(n > d)
    {
        d = old_n;
        n = old_d;
     }    

    while (r != 0)
    {
        //Euclid's Algorithm
        r = d % n;
        //cout << d << " / " << n << " yields R" << r << endl;
        d = n;
        n = r;
        //----------------
        /*when the remaminder = 0 the denominator that produced
         that result is the gcd*/
        gcd = d;
    }
    //creating the simplified fraction
    ltn = old_n/gcd;
    ltd = old_d/gcd;
    
    numerator = ltn;
    denominator = ltd;
    if(denominator < 0)
        denominator *= -1;
    
    if(is_improper(*this))
        (*this).ImproperToMixed();
        
}
//-----------------------------------------------------------
double Mixed::Evaluate()
{   /*Converts a mixed number to decimal*/
    if(integer >= 0)
    {
        double fraction;             
        fraction = static_cast<double>(numerator)/denominator;
        fraction += integer;
        return fraction;
    }
    else
    {
        //if negative # the fraction part must be made negative
        //so the addition of the 2 parts function correctly
        double fraction;             
        fraction = static_cast<double>((numerator * -1))/denominator;
        fraction += integer;
        return fraction;    
   
    }
}
//-----------------------------------------------------------
int abs_value(int i)
{
    /*reurns the absolute value of an integer*/
    if(i < 1) 
        return (-1 * i);
    else 
        return i;    
 }
//-----------------------------------------------------------
bool is_improper(const Mixed& f)
{
    /*tests to see if fraction is improper*/
    if(
       (abs_value(f.numerator) > f.denominator)
      )  
        return true;
    else
        return false;
}
//-----------------------------------------------------------
void Mixed::ImproperToMixed()
{
    /*converts an improper fraction to a mixed number */
    int store_int;

    if(numerator > 0 && integer > 0)
    {
        store_int = integer; //prevents  numerator from turning negative
        integer = numerator/denominator;
        numerator -= (integer * denominator);
        integer += store_int;
    }
    else
    if(numerator > 0 && integer < 0)
    {
        store_int = integer; //prevents  numerator from turning negative
        integer = ((numerator/denominator) * -1);
        numerator += (integer * denominator);
        integer += store_int;
        
    }
    else
    if(numerator > 0 && integer <= 0)
    {
        store_int = integer; //prevents  numerator from turning negative
        integer = (numerator/denominator);
        numerator -= (integer * denominator);
        integer += store_int;

        
    }
    if(numerator < 0)
    {
        /* this is logic for turning neagtive improper fractions into
           mixed #'s. The '-' sign is removed from the numerator by 
           multiplying it by -1. 
            
        */
        integer += (numerator/denominator);
        numerator -= (integer * denominator);
        numerator *= -1;
        if(denominator < 0)
            denominator *= -1;
        

    }
}
//-----------------------------------------------------------
