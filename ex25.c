#include "debug.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

void fun(int a,...)
{
	va_list argp;
	va_start(argp,a);
	int* key = NULL;
	for(key = va_arg(argp,int*);
		key!=NULL;
		key = va_arg(argp,int*))
	{
		log_info("%d",*key);
	}
	va_end(argp);
}
void fun2(int a ,...)
{
	va_list argp;
	va_start(argp,a);
	const char *key = NULL;
	const char *value = NULL;
	for(key = va_arg(argp,const char*);
		key!=NULL;
		key = va_arg(argp,const char*))
	{
		value = va_arg(argp,const char*);
		log_info("key : %s, value : %s",key,value);
	}
	va_end(argp);
}
int main()
{
	int a=1,b=2,c=3,d=4;
	fun(4,&a,&b,&c,&d,NULL);
	char *e="hello=world2",*f="world";
	fun2(4,e,f,NULL);
	return 0;
}