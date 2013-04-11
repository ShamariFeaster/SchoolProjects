using namespace std;

//Const Iterator
template <typename T>
List<T>::const_iterator::const_iterator() : current(NULL){}

template<typename T>
List<T>::const_iterator::const_iterator(Node *p) : current(p){}

template<typename T>
const T& List<T>::const_iterator::operator*() const {return retrieve(); }

template<typename T>
T& List<T>::const_iterator::retrieve() const {return current->data; }

template<typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator++()
{
    if(const_iterator::current->next != NULL)
        current = current->next;
    return *this;
}

template<typename T>
typename List<T>::const_iterator  List<T>::const_iterator::operator++(int)
{
    const_iterator old = *this;
    ++(*this);
    return old;
}

template<typename T>
typename List<T>::const_iterator &  List<T>::const_iterator::operator--()
{
    current = current->prev;
    return *this;
}

template<typename T>
typename List<T>::const_iterator  List<T>::const_iterator::operator--(int)
{
    const_iterator old = *this;
    --(*this);
    return old;
}

template<typename T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const
{
    return current == rhs.current;
}

template<typename T>
bool List<T>::const_iterator::operator!=(const const_iterator &rhs) const
{
    return !(*this == rhs);
}

//Iterator
template<typename T>
List<T>::iterator::iterator(Node *p) : const_iterator(p){}

template<typename T>
T & List<T>::iterator::operator*()
{
    return const_iterator::retrieve();
}

template<typename T>
const T & List<T>::iterator::operator*() const
{
    return const_iterator::retrieve();
}

// increment/decrement operators
template<typename T>
typename List<T>::iterator & List<T>::iterator::operator++()
{
    if(const_iterator::current->next != NULL)
        const_iterator::current = const_iterator::current->next;

    return *this;
}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
    iterator old = *this;
    ++(*this);
    return old;
}

template<typename T>
typename List<T>::iterator & List<T>::iterator::operator--()
{
    const_iterator::current = const_iterator::current->prev;
    return *this;
}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
    iterator old = *this;
    --(*this);
    return old;
}
//Start List<T> functions
template<typename T>
List<T>::List(){ init(); }

template<typename T>
void List<T>::init()
{
    head = new Node();
    tail = new Node();
    head->next = tail;
    tail->prev = head;
    theSize = 0;
}

template<typename T>
List<T>::List(const List &rhs)
{
    init();
    this->operator=(rhs);
}

template<typename T>
List<T>::~List()
{
    if(!this->empty())
    {
        for(Node * x = this->head; ; x = x->next)
        {
                delete x;
                if(x->next == NULL)
                    break;
        }
            theSize = 0;
    }
}

template<typename T>
List<T>::List(int num, const T& val)
{
    init();
    Node * curr = head;
    theSize = num;
    for(int x = 0; x < num; x++)
    {
        curr->next = new Node(val, curr);
        curr = curr->next;
    }
    curr->next = tail;
    tail->prev = curr;
}

template<typename T>
List<T>::List(const_iterator start, const_iterator end)
{
    init();
    Node * curr = head;

    while(start != end || start == this->end())
    {
        curr->next = new Node(*(start++), curr);
        curr = curr->next;
        ++theSize;
    }
    curr->next = tail;
    tail->prev =  curr;
}

template<typename T>
void List<T>::print(std::ostream& os, char ofc) const
{
    if(!this->empty())
    {
        typename List<T>::const_iterator::const_iterator begin;
        for(begin = this->begin(); begin != this->end() ; begin++)
        {
            os << *begin << ofc;
        }
    }
    else
    {
        os << "---";

    }
}

template<typename T>
const List<T> & List<T>::operator=(const List &rhs)
{
    if(rhs.empty())
    {
        this->~List();
        init();
        return *this;
    }
    else
    {
        typename List<T>::const_iterator::const_iterator begin = rhs.begin();
        Node * curr = head;

        while(begin != rhs.end())
        {
            curr->next = new Node(*(begin++), curr);
            curr = curr->next;
            ++theSize;
        }
        curr->next = tail;
        tail->prev =  curr;
    }
}

template<typename T>
int List<T>::size() const { return theSize; }

template<typename T>
bool List<T>::empty() const
{
    if(theSize == 0)
        return true;
    else
        return false;
}

template<typename T>
void List<T>::clear() { this->~List(); }

template<typename T>
void List<T>::reverse()
{
    if(!this->empty())
    {
        Node * temp;

        for(Node * curr_node = head;; curr_node = curr_node->prev)
        {
            temp = curr_node->prev;
            curr_node->prev = curr_node->next;
            curr_node->next = temp;

            if(curr_node->prev == NULL)
            {
                break;
            }
        }
        temp = head;
        head = tail;
        tail = temp;
    }
}

template<typename T>
T & List<T>::front() { return head->next->data;}

template<typename T>
const T& List<T>::front() const { return head->next->data;}

template<typename T>
T & List<T>::back() { return tail->prev->data;}

template<typename T>
const T & List<T>::back() const { return tail->prev->data;}

template<typename T>
void List<T>::push_front(const T & val)
{
    if(this->empty())
    {
        head->next = new Node(val, head, tail);
        tail->prev = head->next;
        ++theSize;
    }
    else
    {
        Node * temp = new Node(val, head, head->next);
        head->next->prev = temp;
        head->next = temp;
        ++theSize;
    }
}

template<typename T>
void List<T>::push_back(const T & val)
{
    if(this->empty())
    {
        head->next = new Node(val, head, tail);
        tail->prev =  head->next;
        ++theSize;
    }
    else
    {
        Node * new_node = new Node(val, tail->prev, tail);
        tail->prev->next = new_node;
        tail->prev = new_node;
        ++theSize;
    }
}

template<typename T>
void List<T>::pop_front()
{
    Node * temp = head->next;
    head->next = head->next->next;
    head->next->prev = head;
    head->prev = NULL;
    delete temp;
    --theSize;
}

template<typename T>
void List<T>::pop_back()
{
    Node * temp = tail->prev;
    tail->prev->prev->next = tail;
    tail->prev = tail->prev->prev;
    delete temp;
    --theSize;
}

template<typename T>
void List<T>::remove(const T &val)
{
    if(!this->empty())
    {
        typename List<T>::iterator::iterator current = this->begin();
        while(current != this->end())
        {
            if(val == *current)
                this->erase(current);
            else
                ++current;
        }
    }

}

//Iterator Retrieval
template<typename T>
typename List<T>::iterator List<T>::begin() { return iterator(head->next); }

template<typename T>
typename List<T>::const_iterator List<T>::begin() const { return const_iterator(head->next); }

template<typename T>
typename List<T>::iterator List<T>::end(){ return iterator(tail);}

template<typename T>
typename List<T>::const_iterator List<T>::end() const{ return const_iterator(tail);}

//Iterator Operations
template<typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val)
{

    //Bad Iterator
    if(itr == NULL)
        return iterator(head);

    Node * curr = itr.current;
    Node * new_node = new Node(val, curr->prev, curr);
    curr->prev->next = new_node;
    curr->prev = new_node;
    return iterator(curr);

}

template<typename T>
typename List<T>::iterator List<T>::erase(iterator itr)
{
        //Bad Iterator
    if(itr == NULL)
        return iterator(head);

    Node * curr = itr.current;
    Node * return_node = itr.current->next;
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    delete curr;
    return iterator(return_node);

}

template<typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end)
{
    typename List<T>::iterator::iterator current_itr = start;
    // bad iterator
    if(start == NULL)
        return iterator(head);
    // start and end are the same
    if(start == end)
        return iterator(this->erase(start));
    // cover case is start is after end, we just erase all from start to end
    while(current_itr != end && current_itr != this->end())
        this->erase(current_itr++);
}

//List comparrison operators
template <typename T>
bool operator==(const List<T> & lhs, const List<T> &rhs)
{

    if(lhs.size() != rhs.size())
        return false;

    bool same = true;

    typename List<T>::const_iterator::const_iterator l = lhs.begin();
    typename List<T>::const_iterator::const_iterator r = rhs.begin();

    while(l != lhs.end())
    {
        if(*l++ != *r++)
        {
            same = false;
            break;
        }

    }
    return same;
}

template <typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs){ return !(lhs == rhs); }

//Print List<T> Contents
template <typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l)
{
    l.print(os);
    return os;
}
