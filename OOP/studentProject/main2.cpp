#include "Student.h"
#include <iomanip>
#include <iostream>
#include <cstring>



using namespace std;

void PrintHeader()
{
cout << "Student                                   Final   Final   Letter" << endl;
cout << "Name                                      Exam    Avg     Grade" << endl;  
cout << "----------------------------------------------------------------" << endl; 
}


int main()
{
int num;
char fn[40];
char ln[40];
char subject[40];
int att,t,m,f,p,t1,t2,q1,q2,q3,q4,q5;
Student* s1;
/*
att = attendance, t = test, m = midterm, t1 = test1
t2 = test2, q1-q5 = quizs 1-5
*/


cin >> num;
cin.ignore(3, '\n');
Student ** list = new Student*[num];

for(int x = 0; x < num; x++)
{

	cin.getline(ln,40, ',');
    //cout << ln;	
	cin.ignore(1);
	cin.getline(fn,40,'\n');
    //cout << fn;	
	cin.getline(subject,40, ' ');
	//cout << subject << endl;
    if(!strcmp(subject, "English"))
    {
        
        cin >> att >> p >> m >> f;
        cin.ignore(256, '\n');
        list[x] = new English(fn, ln, att, p, m, f);
        //list[x]->PrintName();
        
          
    }else
    if(!strcmp(subject, "History"))
    {
        
        cin >> t >> m >> f;
        cin.ignore(256, '\n');
        
        list[x] = new History(fn, ln, t, m, f);
        //list[x]->PrintName();
    }else
    
    
    if(!strcmp(subject, "Math"))
    {
        
        cin >> q1 >> q2 >> q3 >> q4 >> q5 >> t1 >> t2 >> f;
        cin.ignore(256, '\n');
        list[x] = new Math(fn, ln, q1, q2, q3, q4,q5, t1, t2, f);
        //list[x]->PrintName();
    }
    
    
	

}
cout << "Student Grade Summary" << endl;
cout << "---------------------" << endl << endl;
cout << "ENGLISH CLASS" << endl << endl;
PrintHeader();
int x; 
for(x = 0; x < num; x++)
{
    if(!strcmp(list[x]->GetCourse(), "English"))
    {
        list[x]->compute();
        list[x]->PrintRow();
    }

}
cout <<endl << endl;
cout << "HISTORY CLASS" << endl << endl;
PrintHeader();
for(int x = 0; x < num; x++)
{
    if(!strcmp(list[x]->GetCourse(), "History"))
    {
        list[x]->compute();
        list[x]->PrintRow();
        
    }

}

cout <<endl << endl;
cout << "MATH CLASS" << endl << endl;
PrintHeader();
for(int x = 0; x < num; x++)
{
    if(!strcmp(list[x]->GetCourse(), "Math"))
    {
        list[x]->compute();
        list[x]->PrintRow();
        
    }

}

}
