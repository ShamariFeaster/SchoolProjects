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
        
        return cpy; 
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

const char * MyString::GenerateSubstring(int& len, bool reset)
{
    if(reset == true)
    {
        
        substring_size = str_length;
        //cout << substring_size << endl;
        substring_pos = 0;
        //cout << substring_pos << endl;
        return NULL;        
    }
    //cout << "sub_pos in: "<<  substring_pos << endl;
    if((substring_pos + substring_size) <= str_length)
    {
        len = substring_size;
        //cout << "generate: valid "  << endl;
        return &str_ptr[substring_pos++];
    }
    else
    {
        substring_size--;
        substring_pos = 0;
        len = 0;
        //cout << "generate: invalid "  << endl;
        //cout << "substring_size" << substring_size << endl;
        return NULL;
    }
   
}

const char * MyString::LargestCommonSubstring(MyString& str, int& length)
{
    char* caller;
    char* param;
    bool flag = true;
    int len1 = 0;
    int len2 = 0;
    int diff = str_length - str.str_length;
    this->GenerateSubstring(len1, true);
    str.GenerateSubstring(len2, true);
    if(diff > 0)
    {
        
        substring_size = str.str_length;
        substring_pos = 0;
        //cout << "resizing caller" << endl;
    }
    if(diff < 0)
    {
        diff *= -1; //get abs vallues of diff    
        //cout << "diff: " << diff << endl;
        for(int x = 0; x < diff; x++)
        {
             while(str.GenerateSubstring(len2, false) != '\0')
            {
                //cout << "resizing param" << endl;//geting sub_size of str down to the largest
                 //possible substring of calling object     
                
            }    
           
        }
    }

    while( str.substring_size > 0)
    {
        
          
        //cout << "outer loop" << endl;
        if(str.GenerateSubstring(len2, false) != '\0')
        {
            //cout << " here 3" << endl;
            substring_pos = 0;
            substring_size = len2;
            while(this->GenerateSubstring(len1, false) != '\0')
            { 
                flag = true;
                //cout << "here1" << endl;
                caller = str_ptr + (substring_pos - 1 );
                param = str.str_ptr + (str.substring_pos - 1);
                for(int i = 0; i < len1; i++)
                {
                    //cout << "len1: " << len1 << endl;
                    //cout << "len2: " << len2 << endl;
                    //cout << "caller: " << *(caller + i ) << endl;
                    //cout << "param: " << *(param + i) << endl;
                    //cout << "i: " << i << endl;
                    
                    if(*(caller + i) != *(param + i))
                    {    flag = false;
                        //cout << "false comparison" << endl;
                    }
                }
                
                if(flag == true)
                {
                    length = len1;
                    cout << "length " << length << endl;
                    return  &str_ptr[substring_pos-1];
                }
                //cout << "here2" << endl;
                //cout << "caller: " << *(caller) << endl;
                //cout << "sub_pos: " << substring_pos << endl;
                //cout << "sub_size: " << substring_size << endl;
            }
            
        }
    }
    
length = 0;
return NULL;
    
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
    
    int len1;
    int len2 = 0;

 	MyString str1("d");
 	MyString str2("d");
 
    cout << str1.LargestCommonSubstring(str2, len1) << len1 << endl;
     
            
            
      
    
    
    cin.get();
	return 0;

}
