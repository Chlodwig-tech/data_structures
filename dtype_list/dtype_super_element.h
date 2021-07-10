#ifndef DTYPE_SUPER_ELEMENT_H
#define DTYPE_SUPER_ELEMENT_H

#include "../printable.h"
#include<memory.h>

namespace data_structures {

class dtype_super_element : public Printable{
public:
    dtype_super_element* next;
    dtype_super_element* previous;
    std::string name;
    int size=0;
    void *ptr=nullptr;
    
    virtual void print_(std::ostream &ostr)=0;

    void __cout__(std::ostream &ostr){
        print_(ostr);
    }   

    bool is_equal(dtype_super_element *other){
        if(name!=other->name){
            return false;
        }
        if(size!=other->size){
            return false;
        }
        if(memcmp(ptr,other->ptr,size)==0){
            return true;
        }
        return false;
    }
};

}

#endif // DTYPE_SUPER_ELEMENT_H
