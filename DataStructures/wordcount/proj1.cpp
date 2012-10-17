/* The error in the example program is it is counting and outputing
* carriage returns
*
*/

#include <iostream>
#include <iomanip>
#include <cctype>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>


using namespace std;

// FUNCTIONS
bool sort_char (pair<char, int> i, pair<char, int> j) {
    if(i.second == j.second) {
        return (i.first < j.first);
    } else
        return (i.second > j.second);
    }

bool sort_string (pair<string, pair<int, int> > i, pair<string, pair<int, int> > j) {
    if((i.second).first == (j.second).first)
        return ((i.second).second < (j.second).second);
    else
        return (i.second > j.second);
    }

void print_heading(int size, string type) {
    cout << endl << "Total " << size << " different " << type << ", ";
    if(size > 10)
        cout << "10 most used " << type << ":" << endl;
    else
        cout << size << " most used " << type << " :" << endl;

}

void print_string_row(int row_num, string str, int count) {
    cout << right << "No." << setw(2) << row_num << " : " << left << setw(16) << str << setw(2) << count << endl;
    }

void print_char_row(int row_num, char str, int count) {
    if(str == '\n') {
        cout << right << "No." << setw(2) << row_num << " : " << left << setw(16) << "\\n" << setw(2) << count << endl;
    } else if(str == '\t') {
        cout << right << "No." << setw(2) << row_num << " : " << left << setw(16) << "\\t" << setw(2) << count << endl;
    } else
        cout << right << "No." << setw(2) << row_num << " : " << left << setw(16) << str << setw(2) << count << endl;
    }
// END FUNCTIONS

int main() {

bool debug = false;

string input;               //used as buffer
char character;
char c;
string alpha_str = "";
string digit_str = "";

map<char, int> char_count;
//map<key string, pair(occurances of the key, ordinal of key in input file)>
map<string, pair<int, int> > number_count;
map<string, pair<int, int> > word_count;

map<char, int>::iterator char_iter;
map<string, pair<int, int> >::iterator number_iter;
map<string, pair<int, int> >::iterator word_iter;

vector<pair<char, int> > vChar_count;
//vector<key string, pair(occurances of the key, ordinal of key in input file)>
vector<pair<string, pair<int, int> > > vNumber_count;
vector<pair<string, pair<int, int> > > vWord_count;

vector<pair<char, int> > ::iterator vChar_iter;
vector<pair<string, pair<int, int> > >::iterator vNumber_iter;
vector<pair<string, pair<int, int> > >::iterator vWord_iter;

//read file
while(cin.good()){
c = cin.get();
//throw away non-readable character except \n and \t
if(c < 32 && (c != 9 && c != 10))
    continue;
input += c;
}

//display file contents if debugging
if (debug)
    cout << "file contents: " << input << endl;

int ord = 0;                            //ordinal position
for(int x = 0; x < input.size(); x++) {
    character = input[x];
    //store and clear digit buffer
    if(isalpha(character)) {
        alpha_str += tolower(input[x]);
        //number boundary signaled so store and clear digit buffer
        if(digit_str != "" && number_count.count(digit_str) == 0) {
            number_count.insert\
            (pair<string, pair<int, int> >(digit_str, pair<int, int>(1, ord++)));
            digit_str = "";
        }
        else if(number_count.count(digit_str) != 0){
            number_count[digit_str].first++;
            digit_str = "";
        }
    }
    //store and clear alpha buffer
    else if(isdigit(character)){
        digit_str += character;
        //word boundary signaled so store and clear alpha buffer
        if(alpha_str != "" && word_count.count(alpha_str) == 0) {
            word_count.insert\
            (pair<string, pair<int, int> >(alpha_str, pair<int, int>(1, ord++)));
            alpha_str = "";
        }
        else if(word_count.count(alpha_str) != 0){
            word_count[alpha_str].first++;
            alpha_str = "";
        }

    //process non-alpha numeric (signals a word boundary)
    } else {

        //word boundary signaled so store and clear alpha buffer
        if(alpha_str != "" && word_count.count(alpha_str) == 0) {
            word_count.insert \
            (pair<string, pair<int, int> >(alpha_str, pair<int, int>(1, ord++)));
             alpha_str = "";
        }
        else if(word_count.count(alpha_str) != 0){
            word_count[alpha_str].first++;
            alpha_str = "";
        }

        //number boundary signaled so store and clear digit buffer
        if(digit_str != "" && number_count.count(digit_str) == 0) {
            number_count.insert\
            (pair<string, pair<int, int> >(digit_str, pair<int, int>(1, ord++)));
            digit_str = "";
        }
        else if(number_count.count(digit_str) != 0){
            number_count[digit_str].first++;
            digit_str = "";
        }
    }

    //tally all character occurances
    if(char_count.count(character) == 0) {
        char_count.insert(pair<char,int>(character, 1));
    } else {
        char_count[character]++;
    }

}

// Stroring uncleared buffers before termination of input processing

//alpha
if(alpha_str != "" && word_count.count(alpha_str) == 0) {
    word_count.insert\
    (pair<string, pair<int, int> >(alpha_str, pair<int, int>(1, ord++)));
    alpha_str = "";
}
else if(word_count.count(alpha_str) != 0){
    word_count[alpha_str].first++;
    alpha_str = "";
}

//digit
if(digit_str != "" && number_count.count(digit_str) == 0) {
    number_count.insert\
    (pair<string, pair<int, int> >(digit_str, pair<int, int>(1, ord++)));
    digit_str = "";
}
else if(number_count.count(digit_str) != 0){
    number_count[digit_str].first++;
    digit_str = "";
}

//place maps into vectors for sorting
for(char_iter = char_count.begin(); char_iter != char_count.end(); char_iter++) {
    vChar_count.push_back(pair<char, int>(char_iter->first, char_iter->second));
}

for(number_iter = number_count.begin(); number_iter != number_count.end(); number_iter++) {
    vNumber_count.push_back\
    (pair<string, pair<int, int> >(number_iter->first, number_iter->second));
}

for(word_iter = word_count.begin(); word_iter != word_count.end(); word_iter++) {
    vWord_count.push_back\
    (pair<string, pair<int, int> >(word_iter->first, word_iter->second));
}

sort(vChar_count.begin(), vChar_count.end(), sort_char);
sort(vNumber_count.begin(), vNumber_count.end(), sort_string);
sort(vWord_count.begin(), vWord_count.end(), sort_string);

//Display Results
int ctr;
const int MAX_RANK = 9;
print_heading(vChar_count.size(), "characters");
for (ctr = 0, vChar_iter=vChar_count.begin(); vChar_iter!=vChar_count.end(); vChar_iter++, ctr++ ) {
    print_char_row(ctr, (*vChar_iter).first, (*vChar_iter).second);
    if(ctr == MAX_RANK)
        break;
}

print_heading(vWord_count.size(), "words");
for (ctr = 0, vWord_iter=vWord_count.begin(); vWord_iter!=vWord_count.end(); vWord_iter++, ctr++) {
    print_string_row(ctr, (*vWord_iter).first, (*vWord_iter).second.first);
    if(ctr == MAX_RANK)
        break;
    }

    print_heading(vNumber_count.size(), "numbers");
for (ctr = 0, vNumber_iter=vNumber_count.begin(); vNumber_iter!=vNumber_count.end(); vNumber_iter++, ctr++){
    print_string_row(ctr, (*vNumber_iter).first, (*vNumber_iter).second.first);
    if(ctr == MAX_RANK)
        break;
    }

}
