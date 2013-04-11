/* File: LinkedList.hpp
   Author: ???
   Description: This file contains the implementation of the templated classes
   from LinkedList.h                                                            */

template <typename T> 
std::ostream& operator<<(std::ostream& os, const ListElement<T>& LE){
  os<<"<"<<LE.data<<">";
  return os;
}

template <typename T> 
std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list){
  ListElement<T> *ptr;
  

  /* traverse linked list */
  for(ptr = list.head; ptr; ptr = ptr->next)
    os<<*ptr;
  
  return os;
}

/* Default Constructor (Complete) */
template<typename T>
LinkedList<T>::LinkedList() {

  /* initialize list to be empty (NULL pointer indicates this) */
  this->head = NULL;
}

/* Deallocates dynamic memory associated with calling object. */
template<typename T>
LinkedList<T>::~LinkedList() {
    ListElement<T> *ptr;
    for(ptr = this->head; ptr; ptr = ptr->next)
    {
        if(ptr)
            delete ptr->next;   
    }
        

}

template<typename T>
void LinkedList<T>::AddToEnd(T val) {
  ListElement<T> *ptr;

  /* list is empty */
  if(!this->head) {
    this->head = new ListElement<T>;
    this->head->data = val;
    this->head->next = NULL;
    return;
  }

  /* traverse list until we find end */
  for(ptr = this->head; ptr->next; ptr = ptr->next)
    ;

  ptr->next = new ListElement<T>;
  ptr->next->data = val;
  ptr->next->next = NULL;
}

template<typename T>
void LinkedList<T>::RemoveFromEnd() {
  ListElement<T> *ptr;

  /* list empty */
  if(!this->head)
    return;

  /* one element list */
  if(!this->head->next) {
    delete this->head;
    this->head = NULL;
    return;
  }

  /* traverse list until we reach one element before end */
  for(ptr = this->head; ptr->next->next; ptr = ptr->next)
    ;
  
  delete ptr->next;
  ptr->next = NULL;
}


/* Allocates a new ListElement and adds it to the calling object's linked list 
   at position 'pos' in the linked list (numbering begins at 0).  If 'pos' < 0 
   or greater than the size of the list, the element is added at the end of 
   the list.                                                                    */
template<typename T>
void LinkedList<T>::AddElementPos(T val, int pos) {
    
    //if list is empty
    if(!this->head) return;
    //put element at the beginning
    if(pos ==0)
    {
        ListElement<T> *temp;
        temp = this->head;
        this->head = new ListElement<T>;
        this->head->data = val;
        this->head->next = temp;
        return;
    }

    //find the size of the list
    ListElement<T> *ptr;
    int x;// x = size of the linked list
    for(x = 0, ptr = this->head; ptr; ptr = ptr->next, x++)
    ;
    
    //if position is within bounds
    if(pos > 0 && pos < x)
    {
        int i;
        ListElement<T> *before, *after;
        for(i = 0, ptr = this->head; ptr; i++, ptr = ptr->next)
        {
            if(i == (pos - 1))
            {
               before = ptr;
            } 
            
            if(i == pos)
            {
                after = ptr;
                break;
            } 
        }
       
        before->next = new ListElement<T>;
        before->next->data = val;
        before->next->next = after;
        return;
    }
    else
        this->AddToEnd(val);

}

/* Removes the element at the position 'pos'.  If 'pos' is not a valid position,
   nothing is done.                                                             */
template<typename T>
void LinkedList<T>::RemoveElementPos(int pos) {
     
    //if list is empty
    if(!this->head) return;
   
    //if we want to delete the first element
    if(pos ==0)
    {
        delete this->head;
        this->head = this->head->next;
        
        return;
    }
    
    //get the size of the list
    ListElement<T> *ptr;
     
    int x; //x = size of linked list
    for(x = 0, ptr = this->head; ptr; ptr = ptr->next, x++)
    ;
    
    //if its the last emement in the list
    if(pos == (x - 1))
        {
            this->RemoveFromEnd();
            return;
        }

    //if position is within bounds
    if(pos > 0 && pos < x)
    {
        int i;
        ListElement<T> *before, *after;
        for(i = 0, ptr = this->head; ptr; i++, ptr = ptr->next)
        {
            if(i == (pos - 1))
            {
               before = ptr;
            } 
            
            if(i == (pos + 1))
            {
                after = ptr;
                break;
            } 
        }
        delete before->next;
        before->next = after;
    }

}


