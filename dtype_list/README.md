Doubly-linked list written in C++. The list allows you to store different types.
In the beginning there are this: int, float, double, char, std::string, const char*.
If you want to have more types you have to make following changes:
  - in file dtype_list.h add the appropriate operator type in line 47 in struct result.
  - in file dtype_list.cpp add try and catch with the appropriate type in functions add_element and delete_element.
  - if your type does not have operator<< overloaded, do it. (You can inherit from class Printable (data_structures/printable.h) and override function __cout__).
