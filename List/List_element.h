#ifndef LIST_H
#define LIST_H


#include <printable>
#include "list_element.cpp"

namespace data_structures {

template <typename T>
class List : public Printable{
    List_element<T> *first;
    List_element<T> *last;
    unsigned int size;
public:
    // Constructors & Destructors
    List();
    template<typename ...Args> List(const T& data,Args ...more);
    List(List<T> &l);

    // Methods
    void __cout__(std::ostream &ostr); // virtual method of Printable
    void push_front(T data);
    void push_back(T data);
    void insert(unsigned int index,T data);
    List_element<T>* pop_front();
    List_element<T>* pop_back();
    List_element<T>* remove(int index);
    List_element<T>* remove_element(T data,int i=0);
    void insert_elements();
    template<typename ...Args> void insert_elements(const T& data,Args ...more);
    List_element<T>* get(int index);
    void print();
    int clear();
    int get_size();
    bool is_empty();
    List_element<T>* get_first();

    //Operators
    List_element<T>* operator()(int i);
    T operator[](int i);
    List<T>& operator=(List<T> l);
    bool operator==(List<T> &l);
    bool operator!=(List<T> &l);
    void operator+=(T data);
    void operator+=(List<T> &l);
    void operator-=(T data);
    void operator-=(List<T> &l);
    void operator*=(int k);
    List<T> operator+(T data);
    List<T> operator-(T data);
    List<T> operator+(List<T> &l);
    List<T> operator-(List<T> &l);
    List<T> operator*(int k);
};

}

#endif // LIST_H
