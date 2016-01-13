#include <sys/types.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char * argv[])
{
	if(argc!=3)
	{
		printf("bad argument\n");
		exit(1);
	}
	regex_t rg;
	regmatch_t rm[10];
	if(regcomp(&rg,argv[1],REG_EXTENDED)!=0)
		printf("error\n");
	if(regexec(&rg,argv[2],10,rm,0)!=0)
		printf("error\n");
	int i;
	printf("%d,%d\n",rm[0].rm_so,rm[0].rm_eo);
	for(i=rm[0].rm_so;i<rm[0].rm_eo;i++)
		printf("%c",argv[2][i]);
	printf("\n");
	printf("%d,%d\n",rm[1].rm_so,rm[1].rm_eo);
	for(i=rm[1].rm_so;i<rm[1].rm_eo;i++)
		printf("%c",argv[2][i]);
	printf("\n");

}
