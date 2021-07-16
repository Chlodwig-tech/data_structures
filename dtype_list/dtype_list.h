#ifndef DTYPE_LIST_H
#define DTYPE_LIST_H

#include<fstream>

#include "../printable.h"
#include "dtype_element.h"

namespace data_structures{

class dtype_list : public Printable{
    
    class Type{
        //Types : int, float, double, char, std::string, const char*
        dtype_super_element *dts_elem;
    public:
        auto get(dtype_super_element *dts_elem){
            this->dts_elem=dts_elem;
            struct result{
                operator int(){
                    if(dtype_element<int> *e=dynamic_cast<dtype_element<int>*>(type->dts_elem)){
                        return e->data;
                    }throw("Exception : invalid variable type");
                }
                operator float(){
                    if(dtype_element<float> *e=dynamic_cast<dtype_element<float>*>(type->dts_elem)){
                        return e->data;
                    }throw("Exception : invalid variable type");
                }
                operator double(){
                    if(dtype_element<double> *e=dynamic_cast<dtype_element<double>*>(type->dts_elem)){
                        return e->data;
                    }throw("Exception : invalid variable type");
                }
                operator char(){
                    if(dtype_element<char> *e=dynamic_cast<dtype_element<char>*>(type->dts_elem)){
                        return e->data;
                    }throw("Exception : invalid variable type");
                }
                operator std::string(){
                    if(dtype_element<std::string> *e=dynamic_cast<dtype_element<std::string>*>(type->dts_elem)){
                        return e->data;
                    }throw("Exception : invalid variable type");
                }
                operator const char*(){
                    if(dtype_element<const char*> *e=dynamic_cast<dtype_element<const char*>*>(type->dts_elem)){
                        return e->data;
                    }throw("Exception : invalid variable type");
                }
                Type *type;
            };
            return result{this};
        }
    };
    
    dtype_super_element *first;
    dtype_super_element *last;
    int size;
    Type type;
public: 

    // Constructors & Destructors
    dtype_list();
    template <typename T,typename ...Args> dtype_list(const T& data,Args...more);
    dtype_list(dtype_list &l);
    ~dtype_list();

    // Methods
    void __cout__(std::ostream &ostr); // virtual method of Printable
    auto get(int i);
    void add_element(dtype_super_element *helper);
    bool delete_element(dtype_super_element *helper);
    template<typename T> void push_front(T data);
    template<typename T> void push_back(T data);
    template<typename T> void insert(int index,T data);
    void pop_front();
    void pop_back();
    void remove(int index);
    template<typename T> bool remove_element(T data,int i=0);
    void insert_elements();
    template<typename T,typename ...Args> void insert_elements(const T& data,Args ...more);
    dtype_super_element* get_e(int index);
    void print();
    int clear();
    int get_size();
    bool is_empty();
    dtype_super_element* get_first();
    template<typename T> T get(int index);
    void save(std::string path=".dtype_list_file.xml");
    void read(std::string path=".dtype_list_file.xml");
    
    // Operators
    dtype_super_element* operator()(int i);
    auto operator[](int i);
    dtype_list& operator=(dtype_list l);
    bool operator==(dtype_list &l);
    bool operator!=(dtype_list &l);
    template<typename T> void operator+=(T data);
    void operator+=(dtype_list &l);
    template<typename T> void operator-=(T data);
    void operator-=(dtype_list &l);
    void operator*=(int k);
    template<typename T> dtype_list operator+(T data);
    template<typename T> dtype_list operator-(T data);
    dtype_list operator+(dtype_list &l);
    dtype_list operator-(dtype_list &l);
    dtype_list operator*(int k);

};

}

#endif // DTYPE_LIST_H
