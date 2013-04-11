#include <iostream>
#include <string>
#include <utility>
#include <map>
#include "hashtable.h"

using namespace std;
using namespace cop4530;

//prints option menu and takes user selection
void printMenu(char &input)
{
    cout << "\n\n";
    cout << "l - Load From File" << endl;
    cout << "a - Add User" << endl;
    cout << "r - Remove User" << endl;
    cout << "c - Change User Password" << endl;
    cout << "f - Find User" << endl;
    cout << "d - Dump HashTable" << endl;
    cout << "s - HashTable Size" << endl;
    cout << "w - Write to Password File" << endl;
    cout << "x - Exit program" << endl;
    cout << "\nEnter choice : ";
    cin >> input;
}
//allows us to get uname and ,optional, password
void getCredentials(string &uname, string &pw, bool justUname = false)
{
    const char * prompt = "";
    cout << "Enter username: ";
    cin >> uname;
    if(!justUname)
    {
        cout << "Enter password: ";
        pw = getpass(prompt);
    }
}
void Menu()
{
    map<char, int> ops;
    ops['l'] = 1; ops['d'] = 6;
    ops['a'] = 2; ops['s'] = 7;
    ops['r'] = 3; ops['w'] = 8;
    ops['c'] = 4;
    ops['f'] = 5;
    int capacity;
    string uname;
    string pw;
    string filename;

    cout << "Enter preferred hash table capacity: ";
    cin >> capacity;
    HashTable hash(capacity);

    char input;
    printMenu(input);
    while(input != 'x')
    {   //clean way of excluding invalid menu options
        if(ops.count(input) < 1)
        {
            cout << "*****Error: Invalid entry.  Try again." << endl;
            printMenu(input);
        }
        switch (input)
        {
            case 'l':
                cout << "Enter password file name to load from: ";
                cin >> filename;
                hash.loadFromFile(filename);
                printMenu(input);
                break;
            case 'a':
                getCredentials(uname, pw);
                if( hash.addUser(uname, pw) )
                    cout << endl << "User " <<  uname << " added." << endl;
                else
                    cout << endl << "*****Error: User already exists. Could not add user." << endl;

                printMenu(input);
                break;
            case 'r':
                getCredentials(uname, pw, true);
                hash.removeUser(uname, pw);
                printMenu(input);
                break;
            case 'c':
                getCredentials(uname, pw);
                hash.changePw(uname, pw);
                printMenu(input);
                break;
            case 'f':
                getCredentials(uname, pw);
                hash.findUser(uname, pw);
                printMenu(input);
                break;
            case 'd':
                hash.dumpTable();
                printMenu(input);
                break;
            case 's':
                cout << "Size of hashtable: " << hash.size() << endl;
                printMenu(input);
                break;
            case 'w':
                cout << "Enter password file name to write to: ";
                cin >> filename;
                hash.writeToFile(filename);
                printMenu(input);
                break;
        }
    }
}

int main()
{
    Menu();
    return 0;
}


