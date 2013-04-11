/*
Name: Shamari Feaster
File: student.cpp
*/

#include "student.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>

using namespace std;

Student::Student()
{
	first = new char[40];
	last = new char[40];
	course = new char[40];
	final_avg = 0;
}

Student::Student(const char* fn, const char* ln)
{
	first = new char[40];
	last = new char[40];
	course = new char[40];
	strcpy(first, fn);
	strcpy(last, ln);
	final_avg = 0;
	
}

Student::~Student()
{
    delete [] first;    
    delete [] last;
    delete [] course;
    
}

void Student::PrintName()
{
    //override
;    
}
void Student::compute()
{
    //override
 ;   
}

void Student::PrintRow()
{
    //override
    ;
    
}
//returns the course a student is enrolled in
const char * Student::GetCourse()
{
    return course;    
    
}
//find the letter grade equivalent of a student's final grade
void Student::PrintGrade()
{
	if(final_avg > 0)
	{	
		if(final_avg >= 90)
			cout << "A";
		else if(final_avg >= 80)
			cout << "B";
		else if(final_avg >= 70)
			cout << "C";
		else if(final_avg >= 60)
			cout << "D";
		else 
			cout << "F";
	}
}

English::English()
{
	strcpy(first, "");
    strcpy(last, "");
    strcpy(course, "");
	
	attendance = 0;
	project = 0;
	midterm = 0;
	final =  0;
	
	//grade weighting
	a_weight = 10.0;
	p_weight = 30.0;
	m_weight = 30.0;
	f_weight = 30.0;
}

English::English(const char* fn, const char* ln, int att, int p, int m, int f): Student(fn, ln)
{
	strcpy(course, "English");
	attendance = att;
	project = p;
	midterm = m;
	final =  f;
	
	//grade weighting
	a_weight = 10.0;
	p_weight = 30.0;
	m_weight = 30.0;
	f_weight = 30.0;

}

void English::compute()
{
//calculates final grade based on subject weighting
double a_hd, p_hd, m_hd, f_hd;

a_hd = static_cast<double>(attendance)/100;
a_hd *= a_weight;
final_avg += a_hd;

p_hd = static_cast<double>(project)/100;
p_hd *= p_weight;
final_avg += p_hd;

m_hd = static_cast<double>(midterm)/100;
m_hd *= m_weight;
final_avg += m_hd;

f_hd = static_cast<double>(final)/100;
f_hd *= f_weight;
final_avg += f_hd;
}

void English::PrintRow()
{
    //formats and prints student's name and final grade
    string fname(first);
    string lname(last);
    string fullname = fname + " " + lname;
    cout << left << setw(42) << fullname << setw(8)
    <<  final << setw(7) << fixed << setprecision(2) << final_avg << " "; 
    PrintGrade();
    cout << endl;
}

History::History()
{
	strcpy(first, "");
    strcpy(last, "");
    strcpy(course, "");
	
	term_paper = 0;
	midterm = 0;
	final = 0;

	//grade weighting
	t_weight = 0.0;
	m_weight = 0.0;
	f_weight = 0.0;
}

History::History(const char* fn, const char* ln, int tp, int mt, int f): Student(fn, ln)
{
	strcpy(course, "History");
	term_paper = tp;
	midterm = mt;
	final = f;
	
	//grade weighting
	t_weight = 25.0;
	m_weight = 35.0;
	f_weight = 40.0;

}
void History::compute()
{
//calculates final grade based on subject weighting
double t_hd, m_hd, f_hd;//temporary holders for grades

t_hd = static_cast<double>(term_paper)/100;
t_hd *= t_weight;
final_avg += t_hd;

m_hd = static_cast<double>(midterm)/100;
m_hd *= m_weight;
final_avg += m_hd;

f_hd = static_cast<double>(final)/100;
f_hd *= f_weight;
final_avg += f_hd;


}

void History::PrintRow()
{
    //formats and prints student's name and final grade
    string fname(first);
    string lname(last);
    string fullname = fname + " " + lname;
    cout << left << setw(42) << fullname 
    << setw(8) << final << setw(7) << fixed << setprecision(2) 
	<<  final_avg << " "; 
    PrintGrade();
    cout << endl;
}

Math::Math()
{
	strcpy(first, "");
    strcpy(last, "");
    strcpy(course, "");
	
	
	q1 = 0;
	q2 = 0;
	q3 = 0;
	q4 = 0;
	q5 = 0;
	q_avg = 0;
	test1 = 0;
	test2 = 0;
	final = 0;
	q_weight = 0.0;
	t1_weight = 0.0;
	t2_weight = 0.0;
	f_weight = 0.0;
}
Math::Math(const char* fn, const char* ln, int qu1, int qu2, int qu3, int qu4, int qu5, int t1, int t2, int f)
			: Student(fn, ln)
{
	strcpy(course, "Math");
	
	q1 = qu1;
	q2 = qu2;
	q3 = qu3;
	q4 = qu4;
	q5 = qu5;
	
	q_avg = (q1+q2+q3+q4+q5)/5.0;
	
	test1 = t1;
	test2 = t2;
	final = f;
	
	//grade weighting
	q_weight = 15.0;
	t1_weight = 25.0;
	t2_weight = 25.0;
	f_weight = 35.0;
}
void Math::compute()
{
//calculates final grade based on subject weighting
double q_hd, t1_hd, t2_hd, f_hd;//temp holder of grades


q_hd = static_cast<double>(q_avg)/100;
q_hd *= q_weight;
final_avg += q_hd;

t1_hd = static_cast<double>(test1)/100;
t1_hd *= t1_weight;
final_avg += t1_hd;

t2_hd = static_cast<double>(test2)/100;
t2_hd *= t2_weight;
final_avg += t2_hd;

f_hd = static_cast<double>(final)/100;
f_hd *= f_weight;
final_avg += f_hd;
}

void Math::PrintRow()
{
    //formats and prints student's name and final grade
    string fname(first);
    string lname(last);
    string fullname = fname + " " + lname;
    cout << left << setw(42) << fullname 
    << setw(8) << final << setw(7) << fixed << setprecision(2) <<  final_avg  << " "; 
    PrintGrade();
    cout << endl;
}

