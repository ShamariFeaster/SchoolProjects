#include "List.h"
#include <iostream>

using namespace std;
using namespace cop4530;

int main() {

    List<int> l1;
    List<int> l2;

    //cout << "before copy" << endl;

    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);

    l2.push_back(4);
    l2.push_back(5);
    l2.push_back(6);


    //List<int>::iterator::iterator start = l1.begin();
    /*
    List<int>::iterator::iterator end = l1.begin();
    ++start;
    ++end;
    ++end;
    ++end;
    * */
    //List<int>::iterator::iterator ans = l1.erase(end);
    cout << l1 << "helloe" << l2 << endl;
    //cout << *ans << endl;

    //List<int> l3(begin, end);
    //cout << l3 << endl;
    //l1 = l2;
    //cout << l1 << endl;
    //l1.reverse();
    //l2.reverse();

    //l1.print(cout);

    //cout << l1 << l2 << endl;
    //l1 = l2;

    //cout << l1 << l2;
    //cout << "(l1 == l2) = " << (l1 == l2) << endl;
    //cout << "-----------------------------" << endl;
    //l1.remove(30);
    //l1.print(cout);
    //l1.remove(2);
    //l1.print();
    //l1.print(cout);
    //cout << "after copy" << endl;
    //l2.print();

    //cout << "size: " << l2.size() << endl;
    //cout << "l2 front: " <<  l2.front() << endl;
    //l2.clear();

    //cout << "after clear" << endl;
    //l2.print();


    //cout << "size: " << l2.size() << endl;

    //cout << "l1 front: " << l1.front() << endl;
    //cout << "l2 front: " <<  l2.front() << endl;


    return 0;
}
