#ifndef LIST_ELEMENT_H
#define LIST_ELEMENT_H

#include "../printable.h"

namespace data_structures{

template <typename T>
struct List_element : public Printable{
    T data;
    List_element *next;
    List_element *previous;

    List_element(T data);
    void __cout__(std::ostream &ostr); // virtual method of Printable
};

}

#endif // LIST_ELEMENT_H
