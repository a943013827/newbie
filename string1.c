#include <stdio.h>
char* mystrchr(char* str,int c);
char* mystrcpy(char*str1,const char*str2);
char * mystrncpy(char* str1,const char* str2,int n );
int mystrncmp(const char* str1,const char *str2,int n);
int mystrcmp(const char* str1,const char* str2);
void mystrncat(char*str1,const char*str2,int n);
void mystrcat(char* str1,const char*str2);
int mystrlen(const char *s);
int main()
{
	char c1[20]="123458";
	char c2[20]="1233588";
	char c3[20];
	printf("%s\n",mystrchr(c2,'2'));
	return 0;
}

int mystrlen(const char *s)
{
	int i=0;
	while(*s)
	{
		i++;
		s++;
	}
	return i;
}
void mystrcat(char* str1,const char*str2)
{
	int i=mystrlen(str1);
	while(*str2)
	{
		str1[i]=*str2;
		str2++;
		i++;
	}
	str1[i]=(char)0;
}
void mystrncat(char*str1,const char*str2,int n)
{
	int i=mystrlen(str1),j;
	for(j=0;j<n;j++)
	{
		str1[i]=str2[j];
		i++;
	}
	str1[i]=(char)0;	
}

int mystrcmp(const char* str1,const char* str2)
{
	int i=0;
	while(1)
	{
		if(str1[i]<str2[i])
			return -1;
		if(str1[i]>str2[i])
			return 1;
		if(str1[i]==0)
			return 0;
		i++;
	}
}


int mystrncmp(const char* str1,const char *str2,int n)
{
	int i=0;
	for(i=0;i<n;i++)
	{
		if(str1[i]<str2[i])
                        return -1;
                if(str1[i]>str2[i])
                        return 1;
		 if(str1[i]==0)
                        return 0;
	}
	return 0;
}


char * mystrncpy(char* str1,const char* str2,int n )
{
	int i;
	for(i=0;i<n;i++)
	{
		*(str1+i)=*(str2+i);
	}
	*(str1+n)=0;
	return str1;
}

char* mystrcpy(char*str1,const char*str2)
{
	int n =mystrlen(str2);
	return mystrncpy(str1,str2,n);
}



char* mystrchr(char* str,int c)
{
	while(*str!=c&&*str!=0)
		str++;
	if(*str==0)
		return NULL;
	else
		return str;
}


