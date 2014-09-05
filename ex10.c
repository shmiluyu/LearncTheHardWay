#include <stdio.h>

int main(int argc,char *argv[])
{
	int i = 0;
	printf(argv[i]);
	printf("\n");
	for(i=1;i<argc;i++)
	{
		printf("arg %d: %s\n",i,argv[i]);
	}
	
	return 0;
}
