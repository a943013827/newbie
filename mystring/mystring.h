#ifndef MYSTRING_H
#define MYSTRING_H
#include <iostream>
using namespace std;
class mystring
{
private:
    char *s;
public:
    mystring();
    mystring(const char *s );
//    mystring(const mystring &s);
    ~mystring();
    mystring& operator=(const mystring &s);
    mystring& operator=(const char * c);
    mystring operator+(const mystring & s);
    char& operator[](int i);
    bool operator>(const mystring &s);
    bool operator<(const mystring &s);
    bool operator==(const mystring &s);
    char * c_str();
    friend  istream &  operator>>(istream & in, mystring & s);
    friend  ostream & operator<<(ostream& out,const mystring &s);

};

#endif // MYSTRING_H
