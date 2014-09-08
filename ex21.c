#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "debug.h"

typedef struct {
	int *value;
} Demo;
int main()
{
	printf("Max value of INT32 is %d \n",INT32_MAX);
	printf("Max value of UINT32 is %u \n",UINT32_MAX);
	
	Demo *d = NULL;
	d = calloc(1,sizeof(Demo));

	d.value = 10;
	
	log_info("d's value is %d",*(d->value));
	
	if(d){
		
		free(d);
	}
	return 0;
}
