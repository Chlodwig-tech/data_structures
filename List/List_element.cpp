#ifndef LIST_ELEMENT_CPP
#define LIST_ELEMENT_CPP

#include "List_element.h"

namespace data_structures {

template <typename T> List_element<T>::List_element(T data){
    this->data=data;
    this->next=nullptr;
    this->previous=nullptr;
}

template <typename T> void List_element<T>::__cout__(std::ostream &ostr){
    ostr<<data;
}

}

#endif // LIST_ELEMENT_CPP
