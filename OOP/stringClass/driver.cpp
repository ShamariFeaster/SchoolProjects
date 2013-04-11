#include "MyString.h"

using namespace std;

void PrintToken(const char * c, int len)
    {
        //cout << len << endl;
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
    
    MyString s1("suhduhudhuhduhuhhd");
    MyString s2("fifoijooinfoinuhh");

      
 	cout << endl << "Testing Substring Subroutines..." << endl;
    cout << "String we are testing with.\n";
    cout << "str1: " << str1 << endl;   
    cout << "str2: " << str2 << endl; 
    cout << "str3: " << str3 << endl; 
    cout << "str4: " << str4 << endl; 
    cout << "str5: " << str5 << endl; 
    cout << "str6: " << str6 << endl;    
    
    cout << endl << "\nTesting Largest substring between str1 and str2\n";
    const char* hld = s1.LargestCommonSubstring(s2, len1);
    cout << "Largest Common Substrin Is: ";
    PrintToken(hld, len1);
    
    cout << endl << "\nTesting Largest substring between str3 and str4\n";
    const char* hld2 = str3.LargestCommonSubstring(str4, len1);
    cout << "Largest Common Substrin Is: ";
    PrintToken(hld2, len1);
    
    cout << endl << "\nTesting Largest substring between str5 and str6\n";
    const char* hld3 = str5.LargestCommonSubstring(str6, len1);
    cout << "Largest Common Substrin Is: ";
    PrintToken(hld3, len1);

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
        }

    cin.get();
	return 0;

}
