#include "mystring.h"
#include <stdlib.h>
#include <string.h>
mystring::mystring()
{
    this->s=(char*)malloc(1);
    memset(s,0,1);
}
mystring::mystring(const char *s)
{
    int len =strlen(s);
    this->s=(char*)malloc(len+1);
    strcpy(this->s,s);
}
//mystring::mystring(const mystring &s)
//{
//    cout<<&s<<endl;
//    int len =strlen(s.s);
//    this->s=(char*)malloc(len+1);
//    strcpy(this->s,s.s);
//}
mystring::~mystring()
{
    delete[] s;
}

mystring& mystring::operator=(const  mystring & s)
{
    //cout<<&s<<endl;
    if(this==&s)
        return *this;
    delete[] this->s;
    int len =strlen(s.s);
    this->s=(char *)malloc(len+1);
    strcpy(this->s,s.s);
    return *this;
}


mystring& mystring::operator=(const char * c)
{
    delete[] this->s;
    int len =strlen(c);
    this->s=(char *)malloc(len+1);
    strcpy(this->s,c);
    return *this;
}

 mystring mystring::operator+(const mystring & s)
{
    int len1=strlen(this->s);
    int len2=strlen(s.s);
    char * c=(char*)malloc(len1+len2+1);
    strcpy(c,this->s);
    strcat(c,s.s);
    mystring temp(c);
   // cout<<&temp<<endl;
    return temp;
}


char& mystring::operator[](int i)
{
    return s[i];
}

bool mystring::operator>(const mystring &s)
{
    return strcmp(this->s,s.s)>0;
}

bool mystring::operator<(const mystring &s)
{
    return strcmp(this->s,s.s)<0;
}

bool mystring::operator==(const mystring &s)
{
    return !strcmp(this->s,s.s);
}

char * mystring::c_str()
{
    return s;
}

istream &  operator>>(istream & in, mystring & s)
{
    in>>s.s;
    return in;
}

ostream & operator<<(ostream& out,const mystring &s)
{
    out<<s.s;
    return out;
}
