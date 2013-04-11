/* File: LinkedList.cpp
   Author: Matthew Small
   Description: Header file for a linked list that is templated to allow for 
   storage of various data types.                                              */

#include <iostream>


/* forward declarations, needed to allow template classes to work with friend 
   functions                                                                   */
template <typename T> class ListElement;
template <typename T> class LinkedList; 
template <typename T> std::ostream& operator<<(std::ostream&, 
					       const ListElement<T>&);
template <typename T> std::ostream& operator<<(std::ostream&, 
					       const LinkedList<T>&);

//------------------------------------------------------------------------------
/* A linked list element that holds a variable 'data' whose type is templated 
   as T.                                                                       */
template <typename DATA_TYPE>
class ListElement {
  friend std::ostream& operator<< <DATA_TYPE>(std::ostream&, 
					      const ListElement<DATA_TYPE>&);

public:
  DATA_TYPE               data; /* data stored by this element (int, double, 
                                   Mixed, etc.)                                */
  ListElement<DATA_TYPE> *next; /* pointer to next element in list             */
};



//-------------------------------------------------------------------------------


/* The linked list itself, this must also be templated.                        */
template<typename DATA_TYPE>
class LinkedList {
  friend std::ostream& operator<< <DATA_TYPE>(std::ostream&, 
					      const LinkedList<DATA_TYPE>&);

public:
  LinkedList();
  ~LinkedList();
  void AddToEnd(DATA_TYPE);
  void RemoveFromEnd();
  void AddElementPos(DATA_TYPE, int);
  void RemoveElementPos(int);
  
  
  
  ListElement<DATA_TYPE> *head; /* head of linked list                         */
};


/****    The comment below should be well understood for the Final Exam.    ****/

/* We include the implementation of the above templated classes below their 
   declaration within this header file so that any file that includes this 
   header also has access to the definitions.  As we recall from lecture, 
   different versions of templated functions and classes are compiled for
   each type used for 'typename T' and this happens during the compilation
   phase and not the linking phase (the linking phase is when non-template
   functions and class definitions are matched up with their uses).  Because
   of these differences, the convention is to use the file type '.hpp' for
   files containing template implementations.                                  */
   
#include "LinkedList.hpp"
