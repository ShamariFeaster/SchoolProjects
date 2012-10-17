#include <iostream>
#include "LinkedList.h"

using namespace std;

 int main()
 {
   // create and work with a list of ints
    LinkedList<int> list1;		
    list1.AddToEnd(1);
    list1.AddToEnd(2);
    list1.AddToEnd(3);
    list1.AddToEnd(4);
    ListElement<int> *ptr;
    int a;
    
    cout << list1 << endl;
    
    list1.AddElementPos(15,78);

    cout << list1 << endl;
    
    list1.RemoveElementPos(101);

    cout << list1 << endl;

   return 0;
}
