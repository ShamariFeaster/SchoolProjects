#include "MyString.h" /* MyString class declaration                            */
#include <string.h>   /* strcpy, strlen, etc.                                  */
#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;
/*1.5 notes: set all tokenization states to invalid*/
MyString::MyString(const char* s) 
{ //works
	
	/* internal string data */
    str_ptr = new char[strlen(s)];
    str_length = strlen(s);
    strcpy(str_ptr, s); 

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

    str_ptr = new char[rhs.str_length];
    strcpy(str_ptr, rhs.str_ptr);
    str_length = rhs.str_length;
    token_index = rhs.token_index;
    token_delim = rhs.token_delim;
    substring_size = rhs.substring_size;
    substring_pos = rhs.substring_pos;

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
        if(x < str_length)
        {
            buffer[x] = str_ptr[x];
            if(x == (len -1))
                buffer[x] = '\0';    
        }
    }
}

void MyString::ReversedStrCpy(char *buffer, int len) const 
{
    int x;
    //cout << "buffer: " << buffer << endl;
    for( x = 0; x < len; x++)
    {
        if(x < str_length)
        {
            //cout << "x: " << x << endl;
            //cout << "lette: " << str_ptr[(str_length) - (x + 1)] << endl;
            buffer[x] = str_ptr[(str_length + 1) - (x + 1)]; 
            //cout << "b[x]" << buffer[x] << endl;
            if(x == (len -1))
            {
                
                buffer[x] = '\0';   
            }
        }
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
    //set invalid tokenization state
    token_delim = 0;

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
        
        str_ptr = new char[new_length + 1];

        strcpy(str_ptr, new_str_ptr);
        str_length = strlen(str_ptr);

        delete [] new_str_ptr;
        new_str_ptr = NULL;

}

ostream& operator<<(ostream& os, const MyString& str) 
{
    os << str.str_ptr;
    return os; 
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
        str.Resize(str.str_length);
    }while(!is.eof() && c != '\n');
    str.str_ptr[str.str_length] = '\0'; // overwrite the \n
     
     //set invalid tokenization state
    str.token_delim = 0;
    
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
    //set invalid tokenization state
    str.token_delim = 0;
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
    //set invalid tokenization state
    str.token_delim = 0;
    MyString cpy(str);
    //set invalid tokenization state
    
    if(str.str_ptr != "")
    {
        char  z = str.str_ptr[str.str_length - 1];
        
        int x;
        for(x = str.str_length - 1; x > 0; x--)
        {
            str.str_ptr[x] = str.str_ptr[x-1];    
        }
        str.str_ptr[0] = z;
        /
        return cpy; /
    }else
        return cpy;  
}

MyString& operator--(MyString& str) 
{
    //set invalid tokenization state
    str.token_delim = 0;
    if(str.str_ptr != "")
    {
        char  z = str.str_ptr[0];
        
        int x;
        for(x = 0 ; x < (str.str_length - 1); x++)
        {
            str.str_ptr[x] = str.str_ptr[x+1];    
        }
        str.str_ptr[str.str_length - 1] = z;
        return str; /* change me */
    }else
        return str;
    
}

MyString operator--(MyString& str, int junk) 
{
    //set invalid tokenization state
    str.token_delim = 0;
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
    
    //set invalid tokenization state
    ret.token_delim = 0;
    
    delete []  new_str_ptr;
    new_str_ptr = NULL;     
    
    return ret; 
}

MyString& MyString::operator=(const MyString& rhs) 
{
    
    //works
    this->Resize(rhs.str_length);
    delete [] this->str_ptr;
    strcpy(this->str_ptr, rhs.str_ptr);
    this->str_length = rhs.str_length;
    this->token_index = rhs.token_index;
    this->token_delim = 0;
    this->substring_size = rhs.substring_size;
    this->substring_pos = rhs.substring_pos;
    cout << this->str_length;
    return *this; 
}

MyString& operator+=(MyString& lhs, const MyString& rhs) 
{
    //set invalid tokenization state
    lhs.token_delim = 0;
    //works
    int new_length = lhs.str_length + rhs.str_length;
    char * new_str_ptr = new char[new_length + 1];
    int x;
    for(x = 0; x < new_length + 1; x++)
        new_str_ptr[x] = '\0';
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
    if(token_delim == 0)
    {
        cerr << "Invalid Tokenization state" << endl;
        exit(2);
    }
    //accounts for delims at beginning
	while(str_ptr[token_index] == token_delim)
    {
        if(token_index < str_length)
            token_index++;   
    }

    const char * ret = &str_ptr[token_index];
	int length = 0;
	int x;
	int tkn = token_index;
	for(x = 0; x < str_length; x++)
	{
		if((str_ptr[tkn] != token_delim) && (tkn < str_length))
		{
			length++;
			tkn++;
			
		}
        else
		{
		   
		   break;
        }
	}

	for(x = 0; x < length; x++)
	{
		if(str_ptr[token_index] != token_delim)
		{
            if(token_index < str_length)
            {
    			token_index++;
            }
		}
		
	}

	//accounts for delims at the end
    while(str_ptr[token_index] == token_delim)
    {
        if(token_index < str_length)
            token_index++;   
    }
	len = length;

    if(length == 0)
        const char * ret = NULL;
        
	return ret;

}

void PrintToken(const char * c, int len)
    {
        int x;
        for(x = 0; x < len; x++)
        {
            cout << *(c + x);   
        }    
        
    }
int main()
{
    
    int len1 = 0;
    int len2 = 0;
 	MyString token1("hel,jo,big, small, have");
 	MyString token2(",,hel,jo,,small,,");
 	MyString token3("hel,jo,,,,");
 	MyString empty("");
 	MyString str1("one");
 	MyString str2("two");
	MyString str3("three");
	MyString str4("One");
    MyString str5("kjn23908/*0-0");
    MyString str6("lalalalala");
    MyString str7("one");
    MyString num("1234");
    
    
    
    /*
    Throughout this file I use a "variable : value" syntax
    as opposed to "variable = value" syntax. Values that are hardcoded
     i.e expected outcomes are placed in quotation marks, whereas
     values are produced programatically always follow a colon.
    
    */
    cout << "Insertion Overload" << endl;
    cout <<"Expected Output \"one\"" << endl;
    cout <<"Output: " << str1 << endl;
	cout <<"Expected Output: \"kjn23908/*0-0\"" << endl;
    cout <<"Output: " << str5 << endl;
    
    cout << endl << "Extraction Overload" << endl;
    cout << "Contents of str5 before Extraction: "  << str5 << endl;
    //Extraction should overwrite the contents of str1
    cout << "Please enter as many characters as you like then press enter" << endl;
    cin >> str5;
    cout << "The updated contents of str5 is: " << str5 << endl;
    
    cout << endl << "Arithmetic Operators" << endl;

    cout << "+ operator" << endl;
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    MyString temp;
    cout << "After the operation \"str1 + str2\" " << endl;
    cout << "The contents of temp should be: \"onetwotwo\"" << endl;
    temp = str1 + str2;
    cout << "temp: " << temp << endl;

    cout << endl;
    cout << "+= operator" << endl;
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    cout << "After the operation \"str1 += str2\" " << endl;
    cout << "The contents of str1 should be: \"onetwo\"" << endl;
    str1 += str2;
    cout << "str1: " << str1 << endl;

    cout << endl;
    cout << "postfix ++ operator" << endl;
    cout << "num: " << num << endl;
    cout << "The operation \"num++\"" << endl;
    cout << "Should print \"1234\"" << endl;
    cout << num++ << endl;
    cout << "After num++, num should be \"4123\"" << endl;
    cout << "num: " << num << endl;
    
    cout << endl;
    cout << "prefix ++ operator" << endl;
    cout << "num: " << num << endl;
    cout << "The operation \"++num \" " << endl;
    cout << "Should print \"3412\"" << endl;
    cout << ++num << endl;
    cout << "After ++num, num should still be \"3412\"" << endl;
    cout << "num: " << num << endl;
    
    cout << endl;
    cout << "postfix -- operator" << endl;
    cout << "num: " << num << endl;
    cout << "The operation \"num--\"" << endl;
    cout << "Should print \"3412\"" << endl;
    cout << num-- << endl;
    cout << "After num--, num should be \"4123\"" << endl;
    cout << "num: " << num << endl;
    
    cout << endl;
    cout << "prefix -- operator" << endl;
    cout << "num: " << num << endl;
    cout << "The operation \"--num \" " << endl;
    cout << "Should print \"1234\"" << endl;
    cout << --num << endl;
    cout << "After --num, num should still be \"1234\"" << endl;
    cout << "num: " << num << endl;
    /*
    MyString str7("one");
 	MyString str2("two");
	MyString str3("three");
	MyString str4("One");
	*/
    cout << "Comparison Operators" << endl;
    cout << "str7: " << str7 << endl;
    cout << "str2: " << str2 << endl;
    cout << "str3: " << str3 << endl;
    cout << "str4: " << str4 << endl;
    
    cout << "expected output of str7 < str3 \"1\" " << endl;
    cout << "str7 < str3: " << (str7 < str3) << endl;
    cout << "expected output of str7 > str2 \"0\"" << endl;
    cout << "str7 > str2: " << (str7 > str2) << endl;
    cout << "expected output of str3 <= str2 \"0\"" << endl;
    cout << "str3 <= str2: " << (str3 <= str2) << endl;
    cout << "expected output of str3 >= str2 \"1\"" << endl;
    cout << "str3 >= str2: " << (str3 >= str2) << endl;
    cout << "expected output of str7 == str4 \"1\"" << endl;
    cout << "str7 == str4: " << (str7 == str4) << endl;
    cout << "expected output of str7 != str4 \"0\"" << endl;
    cout << "str7 != str4: " << (str7 != str4) << endl;
    
    cout << endl << "Member Overloads" << endl;
    cout << "Assignmnet Operator" << endl;
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    cout << "After str1 = str2, str1 should be \"two\"" << endl;
    str1 = str2;
    cout << "str1: " << str1 << endl;
    
    cout << endl << "[] Operator" << endl;
    cout << "str1: " << str1 << endl;
    cout << "str1[2] should be \"o\"" << endl;
    cout << "it prints: "<<  str1[2] << endl;
    
    cout << endl << "Utility Functions" << endl;
    int b_size = 4;
    char * temp1 = new char [b_size];
    cout << "\nstr6: " << str6 << endl;
    cout << "Using StrCpy on str6 with a buffer of size 4 " << endl;
    cout << "should place the 1st 4 chars of str6 into my " << endl;
    cout << "buffer, without overflowing it \n" << endl;
    str6.StrCpy(temp1, b_size);
    cout << "My buffer: " << temp1 << endl;
    delete [] temp1;
    temp1 = NULL;
    
    b_size = 17;
    char * temp2 = new char [b_size];
    cout << "\nstr6: " << str6 << endl;
    cout << "Using StrCpy on str6 with a buffer of size 17 " << endl;
    cout << "should place the 1st 17 chars of str6 into my " << endl;
    cout << "buffer, without overflowing it and also not" << endl;
    cout << "indexing out of the bounds of str6.str_ptr array. \n" << endl;
    str6.StrCpy(temp2, b_size);
    cout << "My buffer: " << temp2 << endl;
    delete [] temp2;
    temp1 = NULL;
    
    b_size = 4;
    char * temp3 = new char [b_size];
    cout << "\n str6: " << str6 << endl;
    cout << "Using ReversedStrCpy on str6 with a buffer of size 4 " << endl;
    cout << "should place the last 4 chars of str6 into my " << endl;
    cout << "buffer, without overflowing it" << endl;
    str6.ReversedStrCpy(temp3, b_size);
    cout << "My buffer: " << temp3 << endl;
    delete [] temp3;
    temp1 = NULL;
    
    cout << endl << "Accessor Methods" << endl;
    cout << "\n str6: " << str6 << endl;
    cout << "cstring() should return a printable string that \n";     
    cout << "is identical to the c-string stored in the MyString \n";
    cout << "object (str6).";
    cout << "Output: " << str6.cstring() << endl;
     
    cout << "\n str6: " << str6 << endl;
    cout << "GetLength() should return an int that is the length \n";     
    cout << "of the c-string stored in the MyString object (str6)\n";

    cout << "Output: " << str6.GetLength() << endl;
    
    cout << endl << "Tokenize" << endl;
    cout << "Press 'y' then enter to see what happens when try NextToken() on \n";
    cout << "object that isn't initialize with Tokenize() \n";
    cout << "Pres 'n' then enter to use Tokenize() on an object \n";
    char ans = cin.get();
    switch(ans)
    {
        case 'y':
            token1.NextToken(len1);
            break;
        case 'n':   
            cout << "token1: " << token1 << endl;
            token1.Tokenize(',');
            cout << "call #1  to NextToken() \n"; 
            const char * a = token1.NextToken(len1);
            PrintToken(a, len1);
            cout << "\n call #2  to NextToken() \nToken:";
            const char * b = token1.NextToken(len1);
            PrintToken(b, len1);
            cout << "\ncall #3  to NextToken() \nToken:";
            const char * c = token1.NextToken(len1);
            PrintToken(c, len1);
            cout << "\ncall #4  to NextToken() \nToken:";
            const char * d = token1.NextToken(len1);
            PrintToken(d, len1);
            cout << "\ncall #5  to NextToken() \nToken:";
            const char * e = token1.NextToken(len1);
            PrintToken(e, len1);
            cout << "\ncall #6  to NextToken() \nToken:";
            const char * f = token1.NextToken(len1);
            PrintToken(f, len1);
            cout << "\ncall #7  to NextToken() \nToken:";
            const char * g = token1.NextToken(len1);
            PrintToken(g, len1);
            
            cout << "\n\nCalling Tokenize() on token1\n";
            token1.Tokenize(',');
            cout << "\ncall #8  to NextToken() \nToken:";
            const char * h = token1.NextToken(len1);
            PrintToken(h, len1);
            cout << "\ncall #9  to NextToken() \nToken:";
            const char * i = token1.NextToken(len1);
            PrintToken(i, len1);
            cout << "\ncall #10  to NextToken() \nToken:";
            const char * j = token1.NextToken(len1);
            PrintToken(j, len1);
            
            cout << "\n\nTesting how NextToken() handles leading, trailing,"; 
            cout << "and mulitple delimters. \n";
            
            cout << "\ntoken2: " << token2 << endl;
            token2.Tokenize(',');
            cout << "call #1  to NextToken() \n"; 
            const char * a1 = token2.NextToken(len1);
            PrintToken(a1, len1);
            cout << "\n call #2  to NextToken() \nToken:";
            const char * b1 = token2.NextToken(len1);
            PrintToken(b1, len1);
            cout << "\ncall #3  to NextToken() \nToken:";
            const char * c1 = token2.NextToken(len1);
            PrintToken(c1, len1);
            cout << "\ncall #4  to NextToken() \nToken:";
            const char * d1 = token2.NextToken(len1);
            PrintToken(d1, len1);

            
            cout << "token3: " << token3 << endl;
            token3.Tokenize(',');
            cout << "call #1  to NextToken() \n"; 
            const char * a2 = token3.NextToken(len1);
            PrintToken(a2, len1);
            cout << "\n call #2  to NextToken() \nToken:";
            const char * b2 = token3.NextToken(len1);
            PrintToken(b2, len1);
            cout << "\ncall #3  to NextToken() \nToken:";
            const char * c2 = token3.NextToken(len1);
            PrintToken(c2, len1);
            break;
        default:
            cout << "Your picked and ivalid selection. Token Testing\n";
            cout << "skipped. Exiting Program.";
            cerr << "Invalid Entry Error. Program Terminated.";
            exit(1);
            break;

            
            
    }   
    
    
    cin.get();
	return 0;

}
