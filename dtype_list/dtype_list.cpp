#ifndef DTYPE_LIST_CPP
#define DTYPE_LIST_CPP

#include "dtype_list.h"

namespace data_structures{

// Constructors & Destructors
dtype_list::dtype_list(){
    first=nullptr;
    last=nullptr;
    size=0;
}

template <typename T,typename ...Args> dtype_list::dtype_list(const T& data,Args...more){
    first=nullptr;
    last=nullptr;
    size=0;
    push_back(data);
    insert_elements(more...);
}

dtype_list::dtype_list(dtype_list &l){
    first=nullptr;
    last=nullptr;
    size=0;
    for(dtype_super_element *helper=l.get_first();helper!=nullptr;helper=helper->next){
        add_element(helper);
    }
}

dtype_list::~dtype_list(){
    clear();
}


// Methods
void dtype_list::__cout__(std::ostream &ostr){
    if(is_empty()){
        ostr<<"Empty list";
    }else{
        for(dtype_super_element *helper=first;helper!=nullptr;helper=helper->next){
            ostr<<*helper<<" ";
        }
    }
}

auto dtype_list::get(int i){
    return type.get(get_e(i));
}

void dtype_list::add_element(dtype_super_element *helper){
    try{
        int data=type.get(helper);
        push_back(data);
    }catch(...){}
    try{
        float data=type.get(helper);
        push_back(data);
    }catch(...){}
    try{
        double data=type.get(helper);
        push_back(data);
    }catch(...){}
    try{
        char data=type.get(helper);
        push_back(data);
    }catch(...){}
    try{
        std::string data=type.get(helper);
        push_back(data);
    }catch(...){}
    try{
        const char* data=type.get(helper);
        push_back(data);
    }catch(...){}
}

bool dtype_list::delete_element(dtype_super_element *helper){
    try{
        int data=type.get(helper);
        return remove_element(data);
    }catch(...){}
    try{
        float data=type.get(helper);
        return remove_element(data);
    }catch(...){}
    try{
        double data=type.get(helper);
        return remove_element(data);
    }catch(...){}
    try{
        char data=type.get(helper);
        return remove_element(data);
    }catch(...){}
    try{
        std::string data=type.get(helper);
        return remove_element(data);
    }catch(...){}
    try{
        const char* data=type.get(helper);
        return remove_element(data);
    }catch(...){}
}

template<typename T> void dtype_list::push_front(T data){
    if(first==nullptr){
        first=last=new dtype_element<T>(data);
    }else{
        dtype_element<T> *helper=new dtype_element(data);
        helper->next=first;
        helper->previous=nullptr;
        first->previous=helper;
        first=helper;
    }
    size++;
}

template<typename T> void dtype_list::push_back(T data){
    if(first==nullptr){
        first=last=new dtype_element<T>(data);
    }else{
        dtype_element<T> *helper=new dtype_element(data);
        helper->next=nullptr;
        helper->previous=last;
        last->next=helper;
        last=helper;
    }
    size++;
}

template<typename T> void dtype_list::insert(int index,T data){
    if(index==0){
        push_front(data);
    }else if(index==size){
        push_back(data);
    }else if(index<0 || index>size){
        return;
    }else{
        dtype_super_element *helper=get_e(index-1);
        dtype_element<T> *help=new dtype_element<T>(data);
        help->next=helper->next;
        help->previous=helper;
        helper->next->previous=help;
        helper->next=help;
        size++;
    }
}

void dtype_list::pop_front(){
    if(size>0){
        dtype_super_element *helper=first;
        if(first==last){
            first=last=nullptr;
        }else{
            first=first->next;
            first->previous=nullptr;
        }
        delete helper;
        size--;
    }
}

void dtype_list::pop_back(){
    if(size>0){
        dtype_super_element *helper=last;
        if(first==last){
            first=last=nullptr;
        }else{
            last=last->previous;
            last->next=nullptr;
        }
        delete helper;
        size--;
    }
}

void dtype_list::remove(int index){
    if(index==0){
        pop_front();
    }else if(index==size-1){
        pop_back();
    }else if(index<0 || index>=size){
        return;
    }else{
        dtype_super_element *helper=get_e(index);
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
        delete helper;
        size--;
    }
}

template<typename T> bool dtype_list::remove_element(T data,int i){
    int c=0,j=0;
    for(dtype_super_element *helper=first;helper!=nullptr;helper=helper->next,j++){
        dtype_element<T>* elem=dynamic_cast<dtype_element<T>*>(helper);
        if(elem!=nullptr){
            if(elem->data==data){
                if(c<i){
                    c++;
                }else{
                    remove(j);
                    return true;
                }
            }
        }
    }
    return false;
}

void dtype_list::insert_elements(){}

template<typename T,typename ...Args> void dtype_list::insert_elements(const T& data,Args... more){
    push_back(data);
    insert_elements(more...);
}

dtype_super_element* dtype_list::get_e(int index){
    dtype_super_element *helper=first;
    for(int i=0;i<index;i++){
        helper=helper->next;
    }
    return helper;
}

void dtype_list::print(){
    for(dtype_super_element *helper=first;helper!=nullptr;helper=helper->next){
        std::cout<<*helper<<" ";
    }
    std::cout<<std::endl;
}

int dtype_list::clear(){
    int s=size;
    while (size) {
        pop_back();
    }
    return s;
}

int dtype_list::get_size(){
    return size;
}

bool dtype_list::is_empty(){
    return size==0;
}

dtype_super_element* dtype_list::get_first(){
    return first;
}

template<typename T> T dtype_list::get(int index){
    dtype_element<T> *e=dynamic_cast<dtype_element<T>*>(get_e(index));
    return e->data;
}

void dtype_list::save(std::string path){
    std::ofstream file(path);
    file<<"<dtype_list>\n";
    for(dtype_super_element *helper=first;helper!=nullptr;helper=helper->next){
        try{
            int data=type.get(helper);
            file<<"<int>\n\t"<<data<<"\n</int>\n";
            continue;
        }catch(...){}
        try{
            float data=type.get(helper);
            file<<"<float>\n\t"<<data<<"\n</float>\n";
            continue;
        }catch(...){}
        try{
            double data=type.get(helper);
            file<<"<double>\n\t"<<data<<"\n</double>\n";            
            continue;
        }catch(...){}
        try{
            char data=type.get(helper);
            file<<"<char>\n\t"<<data<<"\n</char>\n";            
            continue;
        }catch(...){}
        try{
            std::string data=type.get(helper);
            file<<"<std::string>\n\t"<<data<<"\n</std::string>\n";
            continue;
        }catch(...){}
        try{
            const char* data=type.get(helper);
            file<<"<const char*>\n\t"<<data<<"\n</const char*>\n";
            continue;
        }catch(...){}
    }
    file<<"</dtype_list>\n";
    file.close();
}

void dtype_list::read(std::string path){
    std::ifstream file(path);
    std::string start;    
    std::string line;
    getline(file,start);
    if(start=="<dtype_list>"){
        while(getline(file,line)){
	    if(line=="</dtype_list>"){
	   	break;
 	    }
 	    std::string data;
            getline(file,data);
            data.erase(data.begin());
            if(line=="<int>"){
                push_back(stoi(data));
            }else if(line=="<float>"){
                push_back(stof(data));
            }else if(line=="<double>"){
                push_back(stod(data));
            }else if(line=="<char>"){
                push_back(char(data[0]));
            }else if(line=="<std::string>"){
                push_back(data);
            }else if(line=="<const char*>"){
                push_back(data);
            }
            getline(file,line);
        }
    }
    file.close();
}

// Operators
dtype_super_element* dtype_list::operator()(int i){
    if(i==0){
        return first;
    }
    if(i==size-1){
        return last;
    }
    return get_e(i);
}

auto dtype_list::operator[](int i){
    return get(i);
}

dtype_list& dtype_list::operator=(dtype_list l){
    clear();
    for(dtype_super_element *helper=l.get_first();helper!=nullptr;helper=helper->next){
        add_element(helper);
    }
    return *this;
}

bool dtype_list::operator==(dtype_list &l){
    if(size!=l.get_size()){
        return false;
    }
    for(dtype_super_element *helper=first,*helper2=l.get_first();helper!=nullptr;helper=helper->next,helper2=helper2->next){
        if(!helper->is_equal(helper2)){
            return false;
        }
    }
    return true;
}

bool dtype_list::operator!=(dtype_list &l){
    return !(*this==l);
}

template<typename T> void dtype_list::operator+=(T data){
    push_back(data);
}

void dtype_list::operator+=(dtype_list &l){
    for(dtype_super_element *helper=l.get_first();helper!=nullptr;helper=helper->next){
        add_element(helper);
    }
}

template<typename T> void dtype_list::operator-=(T data){
    remove_element(data);
}

void dtype_list::operator-=(dtype_list &l){
    for(dtype_super_element *helper=l.get_first();helper!=nullptr;helper=helper->next){
        bool b=true;
        do{
            b=delete_element(helper);
        }while(b);
    }
}

void dtype_list::operator*=(int k){
    dtype_super_element *helper=last;
    for(int i=1;i<k;i++){
        for(dtype_super_element* h=first;h!=helper;h=h->next){
            add_element(h);
        }
        add_element(helper);
    }
}

template<typename T> dtype_list dtype_list::operator+(T data){
    dtype_list l=*this;
    l.push_back(data);
    return l;
}

template<typename T> dtype_list dtype_list::operator-(T data){
    dtype_list l=*this;
    l.remove_element(data);
    return l;
}

dtype_list dtype_list::operator+(dtype_list &l){
    dtype_list l2=*this;
    l2+=l;
    return l2;
}

dtype_list dtype_list::operator-(dtype_list &l){
    dtype_list l2=*this;
    l2+=l;
    return l2;
}

dtype_list dtype_list::operator*(int k){
    dtype_list l=*this;
    l*=k;
    return l;
}


}

#endif // DTYPE_LIST_CPP
