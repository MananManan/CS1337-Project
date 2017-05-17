//ABSTRACT CLASS
#ifndef BASENODE_H
#define BASENODE_H

#include<iostream>
#include<string>
#include<cstdlib>
#include<sstream>
#include<iomanip>

using namespace std;

//all the extra functions are here
bool isValidArabic (string);
bool isValidRoman (string);
bool isValidFileInput(string&);
string digit2letters(int , int);
string arabic2roman (string);
int romanChar2number (char);
int roman2arabic (string);

class BaseNode{

protected:
    int arabic;
    string roman;

public:

    //Constructors
    BaseNode() { arabic = 0; roman = "";} //default

    BaseNode(string); //overloaded

    BaseNode(const BaseNode& abc){ //copy
        arabic = abc.arabic;
        roman = abc.roman;
    }

    //accessors
    int getArabic() {return arabic;}
    string getRoman() { return roman;}

    //mutators;
    void setArabic (int x);
    void setRoman (string x);

    //overloaded <<
    friend ostream& operator<<(ostream& out, BaseNode& node);
    //overloaded >>
    friend istream& operator>>(istream& in, BaseNode& node);

    //destructor JUST TO MAKE THE CLASS ABSTRACT
    virtual void dummy() = 0;


};


#endif // BASENODE_H
