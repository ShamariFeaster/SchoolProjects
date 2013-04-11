#include "MyString.h" /* MyString class declaration                            */
#include <string.h>   /* strcpy, strlen, etc.                                  */
#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

MyString::MyString(const char* s) 
{ //works
	
	/* internal string data */
    str_ptr = new char[strlen(s)];
    str_length = strlen(s);
    strcpy(str_ptr, s); 

        
    //cout << strlen(str_ptr) << endl;
	
	//tokenization state 
    token_index = 0; 
	token_delim = 0;

	//substring generation state 
	substring_size = 0;
	substring_pos = 0;
}

MyString::MyString(const MyString& rhs)
{
    //works
    token_delim = 0;
    //(*this).Resize(rhs.str_length);
    delete [] str_ptr;
    str_ptr = new char[rhs.str_length];
    strcpy(str_ptr, rhs.str_ptr);
    str_length = rhs.str_length;
    token_index = rhs.token_index;
    token_delim = rhs.token_delim;
    substring_size = rhs.substring_size;
    substring_pos = rhs.substring_pos;
    //cout << str_length;
}

 MyString::~MyString()
{
    delete [] str_ptr;
    str_ptr = NULL;    
}

void MyString::StrCpy(char *buffer, int len) const 
{
    
    int x;
    for( x = 0; x < len; x++)
    {
        buffer[x] = str_ptr[x];    
    }
}

void MyString::ReversedStrCpy(char *buffer, int len) const 
{
    int x;
    for( x = 0; x < len; x++)
    {
        buffer[x] = str_ptr[(str_length + 1) - x];    
    }
}

const char* MyString::cstring() const 
{
    char * a = new char[str_length];
    strcpy(a, str_ptr);
    return a; 
}

int MyString::GetLength() const 
{
    return str_length;
}

void MyString::Resize(int new_length)
{ //works
    char * new_str_ptr = new char[new_length + 1];
    int lcv1 = strlen(str_ptr);
    int x;
    for(x = 0; x < (new_length + 1); x++)
    {
        if( x < lcv1)
            new_str_ptr[x] = str_ptr[x];
        if(x == new_length)
            new_str_ptr[x] = '\0';
    }
    delete [] str_ptr;
    str_ptr = new char[new_length + 1];
    //cout << strlen(new_str_ptr) << endl;
    //cout << strlen(str_ptr) << endl;
    strcpy(str_ptr, new_str_ptr);
    str_length = strlen(str_ptr);
    
    delete [] new_str_ptr;
    new_str_ptr = NULL;
}

ostream& operator<<(ostream& os, const MyString& str) 
{
    os << str.str_ptr;
    return os; /* change me */
}

istream& operator>>(istream& is, MyString& str) 
{
    char c;
    str.Resize(0);
    do
    {
        c = is.get();
        str.str_ptr[str.str_length] = c;
        if( c != '\n')
            str.str_length++;
    }while(!is.eof() && c != '\n');
    str.str_ptr[str.str_length] = '\0'; // overwrite the \n
     
    return is;
}
char& MyString::operator[](int pos) 
{ // works
    if(pos >= str_length)
    {
        cerr << "Index Out Of Bounds. Execution Terminated" << endl;
        exit(1);
    }
    else
      return this->str_ptr[pos]; 
}  

char MyString::operator[] (int pos) const 
{
    if(pos >= str_length)
    {
        cerr << "Index Out Of Bounds. Execution Terminated" << endl;
        exit(1);
    }
    else
      return this->str_ptr[pos];     

}  

MyString& operator++(MyString& str) 
{
    if(str.str_ptr != "")
    {
        char  z = str.str_ptr[str.str_length - 1];
        
        int x;
        for(x = str.str_length - 1; x > 0; x--)
        {
            str.str_ptr[x] = str.str_ptr[x-1];    
        }
        str.str_ptr[0] = z;
        //cout << str;
        return str; /* change me */
    }else
        return str;
}

MyString operator++(MyString& str, int junk)
{
    MyString cpy(str);
    if(str.str_ptr != "")
    {
        char  z = str.str_ptr[str.str_length - 1];
        
        int x;
        for(x = str.str_length - 1; x > 0; x--)
        {
            str.str_ptr[x] = str.str_ptr[x-1];    
        }
        str.str_ptr[0] = z;
        //cout << str;
        return cpy; /* change me */
    }else
        return cpy;  
}

MyString& operator--(MyString& str) 
{
    if(str.str_ptr != "")
    {
        char  z = str.str_ptr[0];
        
        int x;
        for(x = 0 ; x < (str.str_length - 1); x++)
        {
            str.str_ptr[x] = str.str_ptr[x+1];    
        }
        str.str_ptr[str.str_length - 1] = z;
        //cout << str;
        return str; /* change me */
    }else
        return str;
    
}

MyString operator--(MyString& str, int junk) 
{
     MyString cpy(str);
    if(str.str_ptr != "")
    {
        char  z = str.str_ptr[0];
        
        int x;
        for(x = 0 ; x < (str.str_length - 1); x++)
        {
            str.str_ptr[x] = str.str_ptr[x+1];    
        }
        str.str_ptr[str.str_length - 1] = z;
        //cout << str;
        return cpy; /* change me */
    }else
        return cpy;
}

MyString operator+(const MyString& lhs, const MyString& rhs) 
{
    //works
    int new_length = lhs.str_length + rhs.str_length;
    char * new_str_ptr = new char[new_length + 1];
    int x;
    for(x = 0; x < new_length; x++)
    {
        if(x < lhs.str_length)
        {
            new_str_ptr[x] = lhs.str_ptr[x];    
        }
        else
        {
            new_str_ptr[x] = rhs.str_ptr[x - lhs.str_length];
        }
    }
    MyString ret(new_str_ptr);
    delete []  new_str_ptr;
    new_str_ptr = NULL;     
    
    return ret; /* change me */
}

MyString& MyString::operator=(const MyString& rhs) 
{
    //works
    this->Resize(rhs.str_length);
    delete [] this->str_ptr;
    strcpy(this->str_ptr, rhs.str_ptr);
    this->str_length = rhs.str_length;
    this->token_index = rhs.token_index;
    this->token_delim = rhs.token_delim;
    this->substring_size = rhs.substring_size;
    this->substring_pos = rhs.substring_pos;
    cout << this->str_length;
    return *this; /* change me */
}

MyString& operator+=(MyString& lhs, const MyString& rhs) 
{
    //works
    int new_length = lhs.str_length + rhs.str_length;
    char * new_str_ptr = new char[new_length + 1];
    int x;
    for(x = 0; x < new_length + 1; x++)
        new_str_ptr[x] = '\0';
        //cout << new_str_ptr[x];
    for(x = 0; x < new_length; x++)
    {
        if(x < lhs.str_length)
        {
            new_str_ptr[x] = lhs.str_ptr[x];    
        }
        else
        {
            new_str_ptr[x] = rhs.str_ptr[x - lhs.str_length];
        }
    }
    
    strcpy(lhs.str_ptr, new_str_ptr);
    lhs.str_length = strlen(lhs.str_ptr);
    delete []  new_str_ptr;
    new_str_ptr = NULL;     
    
   //cout << lhs.str_ptr << endl;
   //cout << lhs.str_length << endl;
   //lhs.Resize(15);
   //cout << lhs.str_ptr;
    return lhs; /* change me */
}

bool operator<  (const MyString& lhs, const MyString& rhs) 
{
    if(lhs.str_length < rhs.str_length)
        return true;
    else 
        return false;
}

bool operator>  (const MyString& lhs, const MyString& rhs) 
{
    if(lhs.str_length > rhs.str_length)
        return true;
    else 
        return false;
}

bool operator<= (const MyString& lhs, const MyString& rhs) 
{
    if(lhs.str_length < rhs.str_length)
        return true;
    //65-122 uppercase
    int x;
    for(x = 0; x < lhs.str_length; x++)
    {
        if(x < rhs.str_length) //prevents OOB on rhs
        {
        //the following tests if alpha
        if(isalpha(lhs.str_ptr[x]) && isalpha(rhs.str_ptr[x]))
        {
            if(tolower(lhs.str_ptr[x]) != tolower(rhs.str_ptr[x]))
                return false;  //alpha comparison failed
        }else if(lhs.str_ptr[x] != rhs.str_ptr[x])
            return false; //non-alpha comparison failed
        }
        else                
            return false;//if here there was more to lhs side
    }
    return true;
}

bool operator>= (const MyString& lhs, const MyString& rhs) 
{
    if(lhs.str_length > rhs.str_length)
        return true;
    //65-122 uppercase
    int x;
    for(x = 0; x < lhs.str_length; x++)
    {
        if(x < rhs.str_length) //prevents OOB on rhs
        {
        //the following tests if alpha
        if(isalpha(lhs.str_ptr[x]) && isalpha(rhs.str_ptr[x]))
        {
            if(tolower(lhs.str_ptr[x]) != tolower(rhs.str_ptr[x]))
                return false;  //alpha comparison failed
        }else if(lhs.str_ptr[x] != rhs.str_ptr[x])
            return false; //non-alpha comparison failed
        }
        else                
            return false;//if here there was more to lhs side
    }
    return true;
}

bool operator== (const MyString& lhs, const MyString& rhs) 
{
    if(lhs.str_length != rhs.str_length)
        return false;
    //65-122 uppercase
    int x;
    for(x = 0; x < lhs.str_length; x++)
    {
        if(x < rhs.str_length) //prevents OOB on rhs
        {
        //the following tests if alpha
        if(isalpha(lhs.str_ptr[x]) && isalpha(rhs.str_ptr[x]))
        {
            if(tolower(lhs.str_ptr[x]) != tolower(rhs.str_ptr[x]))
                return false;  //alpha comparison failed
        }else if(lhs.str_ptr[x] != rhs.str_ptr[x])
            return false; //non-alpha comparison failed
        }
        else                
            return false;//if here there was more to lhs side
    }
    return true;
}

bool operator!= (const MyString& lhs, const MyString& rhs) 
{
    if(lhs.str_length != rhs.str_length)
        return true;
    //65-122 uppercase
    int x;
    for(x = 0; x < lhs.str_length; x++)
    {
        if(x < rhs.str_length) //prevents OOB on rhs
        {
        //the following tests if alpha
        if(isalpha(lhs.str_ptr[x]) && isalpha(rhs.str_ptr[x]))
        {
            if(tolower(lhs.str_ptr[x]) != tolower(rhs.str_ptr[x]))
                return true;  //alpha comparison failed
        }else if(lhs.str_ptr[x] != rhs.str_ptr[x])
            return true; //non-alpha comparison failed
        }
        else                
            return true;//if here there was more to lhs side
    }
    return false;
}

void MyString::Tokenize(char delim) 
{
    token_delim = delim;
    token_index = 0; 
}

const char * MyString::NextToken(int& len)
{
	
	
	int length;
	int x;
	for(x = 0; x < str_length; x++)
	{
		if(str_ptr[x] != token_delim)
		{
			length++;
			
		}else
			break;
	}
	char * buff = new char[length];
	for(x = 0; x < str_length; x++)
	{
		if(str_ptr[x] != token_delim)
		{
			buff[x] = str_ptr[x];
			token_index++;
			
		}
		else
		{
			token_index++;
			break;
		}
	}
	buff[length] = '\0';
	const char * ret = buff;
	return ret;

}

int main()
{
    int a = 0;
 	MyString str("hel,john,me");
 	MyString str2("b");
 	MyString str3("c");
	str.Tokenize('9');
	cout << str.NextToken(a);
	//cout << str.NextToken(a);
	cin >> str2;
	cout << str2;
    cin.get();
	return 0;

}
