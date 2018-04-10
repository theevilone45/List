#include <iostream>
#include <exception>
using namespace std;

struct EmptyException : public exception
{
    const char* what() const throw()
    {
        return "List is empty";
    }
};

template <class T>
class List
{
private:
    struct Node
    {
        T value;
        Node* prev;
        Node* next;

        Node(T val, Node* n = nullptr, Node* p = nullptr)
        :value(val),next(n),prev(p)
        {}
    };

    size_t _size;
    Node* _head;

public:
    List()
    {
        _head = nullptr;
        _size = 0;
    }

    size_t GetSize()
    {
        return _size;
    }

    bool IsEmpty()
    {
        return _size==0;
    }

    void PushBack(T value)
    {
        Node* temp = _head;
        Node* new_node = new Node(value);

        if(IsEmpty())
            _head = new_node;
        else
        {
            while(temp->next != nullptr)
                temp = temp->next;
            temp->next = new_node;
            new_node->prev = temp;
        }
        _size++;
    }

    void PushFront(T value) {
        Node *new_node = new Node(value);

        if (IsEmpty())
            _head = new_node;
        else {
            _head->prev = new_node;
            new_node->next = _head;
            _head = new_node;
        }

        _size++;
    }

    T PopBack()
    {
        if(IsEmpty())
            throw EmptyException();

        Node* temp = _head;
        T result;

        if(_size==1)
        {
            result = _head->value;
            delete _head;
            _head = nullptr;
            _size=0;
            return result;
        }

        while(temp->next->next != nullptr)
            temp = temp->next;

        result = temp->next->value;

        delete temp->next;
        temp->next = nullptr;

        _size--;
        return result;
    }

    void PushAtIndex(T value, size_t index)
    {
        cout << "NOT IMPLEMENTED" << endl;
    }

    void Display()
    {
        Node* temp = _head;
        size_t i=0;
        while(temp!= nullptr) {
            cout << i++ << ")" << temp->value << endl;
            temp = temp->next;
        }
        cout << "Size: " << _size << endl;
    }

    T GetAtIndex(size_t index)
    {
        if(IsEmpty())
            throw EmptyException();

        if(index >= GetSize())
            index = _size-1;

        Node* temp = _head;
        for(size_t i =0; i< index; i++)
            temp= temp->next;

        return temp->value;
    }

    T PopFront()
    {
        if(IsEmpty())
            throw EmptyException();

        Node* temp = _head;
        T result = temp->value;

        if(_size==1)
        {
            delete _head;
            _head= nullptr;
        }
        else
        {
            _head = temp->next;
            delete temp;
            temp = nullptr;
        }
        _size--;
        return result;
    }

    void PushAtIndex(size_t index, T value)
    {
        if(index>=_size)
            index=_size-1;

        Node* temp = _head;
        Node* new_node = new Node(value);

        if(IsEmpty() || index == _size-1)
            PushBack(value);
        else if(index==0)
            PushFront(value);
        else {
            for (size_t i = 0; i < index - 1; i++)
                temp = temp->next;

            new_node->prev = temp;
            new_node->next = temp->next;
            temp->prev = new_node;
            temp->next = new_node;
        }
        _size++;
    }

    T DeleteAtIndex(size_t index)
    {
        if(IsEmpty())
            throw EmptyException();
        if(index>=_size)
            index=_size-1;

        Node* temp = _head;
        T result;

        if(index==0)
            result = PopFront();
        else if(index==_size-1)
            result = PopBack();
        else
        {
            for(size_t i = 0; i<index; i++)
                temp = temp->next;

            result = temp->value;

            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            temp = nullptr;
            _size--;
        }
        return result;
    }

};

int main() {
    List<int> _list;

    _list.PushBack(4);
    _list.PushBack(5);
    _list.PushBack(2);
    _list.PushBack(7);
    _list.PushBack(8);
    _list.PushBack(0);

    try {
        for(int i =0; i<12; i++)
        {
            _list.PopBack();
        }
    }
    catch(EmptyException& e)
    {
        cout << e.what() << endl;
    }




    _list.Display();

    return 0;
}