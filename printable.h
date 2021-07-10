// an abstract class used to overload << operator 

#ifndef PRINTABLE
#define PRINTABLE
class Printable{
public:
    virtual void __cout__(std::ostream &ostr)=0;
  
    friend std::ostream& operator<<(std::ostream& ostr,Printable &printable){
	      printable.__cout__(ostr);
        return ostr;
    }
};
#endif // PRINTABLE
