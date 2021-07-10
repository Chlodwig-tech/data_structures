#ifndef LIST_CPP
#define LIST_CPP

#include "List.h"

namespace data_structures {

// Constructors & Destructors
template <typename T> List<T>::List(){
    first=last=nullptr;
    size=0;
}

template <typename T> template <typename ...Args> List<T>::List(const T& data,Args ...more){
    first=last=nullptr;
    size=0;
    push_back(data);
    insert_elements(more...);
}

template <typename T> List<T>::List(List<T> &l){
    first=last=nullptr;
    size=0;
    for(int i=0;i<l.get_size();i++){
        push_back(l[i]);
    }
}

// Methods

template <typename T> void List<T>::__cout__(std::ostream &ostr){
    if(is_empty()){
        ostr<<"Empty list";
    }
    for(List_element<T> *helper=first;helper!=nullptr;helper=helper->next){
        ostr<<*helper<<" ";
    }
}

template <typename T> void List<T>::push_front(T data){
    if(first==nullptr){
        first=last=new List_element<T>(data);
    }else{
        List_element<T> *helper=new List_element(data);
        helper->next=first;
        helper->previous=nullptr;
        first->previous=helper;
        first=helper;
    }
    size++;
}

template <typename T> void List<T>::push_back(T data){
    if(first==nullptr){
        first=last=new List_element<T>(data);
    }else{
        List_element<T> *helper=new List_element(data);
        helper->next=nullptr;
        helper->previous=last;
        last->next=helper;
        last=helper;
    }
    size++;
}

template <typename T> void List<T>::insert(unsigned int index,T data){
    if(index==0){
        push_front(data);
    }else if(index==size){
        push_back(data);
    }else{
        if(index<0 || index>size){
            return;
        }
        List_element<T> *helper=get(index-1);
        List_element<T> *help=new List_element<T>(data);
        help->next=helper->next;
        help->previous=helper;
        helper->next->previous=help;
        helper->next=help;
        size++;
    }
}

template <typename T> List_element<T>* List<T>::pop_front(){
    if(size>0){
        List_element<T> *helper=first;
        if(first==last){
            first=last=nullptr;
        }else{
            first=first->next;
            first->previous=nullptr;
        }
        List_element<T> *v=helper;
        delete helper;
        size--;
        return v;
    }
    return nullptr;
}

template <typename T> List_element<T>* List<T>::pop_back(){
    if(size>0){
        List_element<T> *helper=last;
        if(first==last){
            first=last=nullptr;
        }else{
            last=last->previous;
            last->next=nullptr;
        }
        List_element<T> *v=helper;
        delete helper;
        size--;
        return v;
    }
    return nullptr;
}

template <typename T> List_element<T>* List<T>::remove(int index){
    if(index==0){
        return pop_front();
    }
    if(index==size-1){
        return pop_back();
    }
    if(index<0 || index>=size){
        return nullptr;
    }
    List_element<T> *helper=get(index);
    if(helper->previous!=nullptr){
        helper->previous->next=helper->next;
    }else{
        first=helper->next;
    }
    if(helper->next!=nullptr){
        helper->next->previous=helper->previous;
    }else{
        last=helper->previous;
    }
    List_element<T> *v=helper;
    delete helper;
    size--;
    return v;
}

template <typename T> List_element<T>* List<T>::remove_element(T data,int i){
    int c=0,j=0;
    for(List_element<T> *helper=first;helper!=nullptr;helper=helper->next,j++){
        if(helper->data==data){
            if(c<i){
                c++;
            }else{
                return remove(j);
            }
        }
    }
    return nullptr;
}

template <typename T> void List<T>::insert_elements(){}

template<typename T> template<typename ...Args> void List<T>::insert_elements(const T& data,Args ...more){
    push_back(data);
    insert_elements(more...);
}

template<typename T> List_element<T>* List<T>::get(int index){
    if(index<0 || index>=size){
        return nullptr;
    }
    List_element<T> *helper=first;
    for(int i=0;i<index;i++){
        helper=helper->next;
    }
    return helper;
}

template <typename T> void List<T>::print(){
    for(List_element<T> *helper=first;helper!=nullptr;helper=helper->next){
        std::cout<<*helper<<" ";
    }
    std::cout<<std::endl;
}

template <typename T> int List<T>::clear(){
    int s=size;
    while(size){
        pop_back();
    }
    return s;
}

template <typename T> int List<T>::get_size(){
    return size;
}

template <typename T> bool List<T>::is_empty(){
    return size==0;
}

template <typename T> List_element<T>* List<T>::get_first(){
    return first;
}

// Operators
template <typename T> List_element<T>* List<T>::operator()(int i){
    if(i==0){
        return first;
    }
    if(i==size-1){
        return last;
    }
    return get(i);
}

template <typename T> T List<T>::operator[](int i){
    if(i==0){
        return first->data;
    }
    if(i==size-1){
        return last->data;
    }
    return get(i)->data;
}

template <typename T> List<T>& List<T>::operator=(List<T> l){
    clear();
    for(List_element<T> *helper=l.get_first();helper!=nullptr;helper=helper->next){
        push_back(helper->data);
    }
    return *this;
}

template <typename T> bool List<T>::operator==(List<T> &l){
    if(size!=l.get_size()){
        return false;
    }
    for(List_element<T> *helper=first,*helper2=l.get_first();helper!=nullptr;helper=helper->next,helper2=helper2->next){
        if(helper->data!=helper2->data){
            return false;
        }
    }
    return true;
}

template <typename T> bool List<T>::operator!=(List<T> &l){
    return !(*this==l);
}

template<typename T> void List<T>::operator+=(T data){
    push_back(data);
}

template<typename T> void List<T>::operator+=(List<T> &l){
    for(List_element<T> *helper=l.get_first();helper!=nullptr;helper=helper->next){
        push_back(helper->data);
    }
}

template<typename T> void List<T>::operator-=(T data){
    remove_element(data);
}

template<typename T> void List<T>::operator-=(List<T> &l){
    for(List_element<T> *helper=l.get_first();helper!=nullptr;helper=helper->next){
        List_element<T> *h=nullptr;
        do{
            h=remove_element(helper->data);
        }while(h!=nullptr);
    }
}

template<typename T> void List<T>::operator*=(int k){
    List_element<T> *l=last;
    for(int i=1;i<k;i++){
        for(List_element<T>* helper=first;helper!=l;helper=helper->next){
            push_back(helper->data);
        }
        push_back(l->data);
    }
}

template<typename T> List<T> List<T>::operator+(T data){
    List<T> l=*this;
    l.push_back(data);
    return l;
}

template<typename T> List<T> List<T>::operator-(T data){
    List<T> l=*this;
    l.remove_element(data);
    return l;
}

template<typename T> List<T> List<T>::operator+(List<T> &l){
    List<T> l2=*this;
    l2+=l;
    return l2;
}

template<typename T> List<T> List<T>::operator-(List<T> &l){
    List<T> l2=*this;
    l2-=l;
    return l2;
}

template<typename T> List<T> List<T>::operator*(int k){
    List<T> l=*this;
    l*=k;
    return l;
}

}

#endif // LIST_CPP
