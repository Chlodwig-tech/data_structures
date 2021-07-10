#ifndef DTYPE_ELEMENT_H
#define DTYPE_ELEMENT_H

#include "dtype_super_element.h"

namespace data_structures {

template <typename T>
class dtype_element : public dtype_super_element{
public:
    T data;

    dtype_element(T data){
        this->data=data;
        next=nullptr;
        previous=nullptr;
        this->name=typeid(data).name();
        this->size=sizeof(data);
        this->ptr=&this->data;        
    }

    void print_(std::ostream &ostr){
        ostr<<data;
    }

};

}

#endif // DTYPE_ELEMENT_H
