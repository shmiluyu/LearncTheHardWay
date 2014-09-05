#include <stdio.h>

int main(int argc,char *argv[])
{
	int ages[] = {23,44,12,32,2};
	char *names[] = {
		"Alan","Frank",
		"Mary","John","Lisa"
	};
	
	int count = sizeof(ages)/sizeof(int);
	int i = 0;
	
	for(i=0;i<count;i++)
	{
		printf("%s has %d years alive.\n",
			*(names+i),ages[i]);
	}
	printf("----\n");
	
	int *cur_ages = ages;
	char **cur_names = names;
	
	 // second way using pointers
    for(i = 0; i < count; i++) {
        printf("%s is %d years old.\n",
                *(cur_names+i), *(cur_ages+i));
    }
    
     // third way, pointers are just arrays
    for(i = 0; i < count; i++) {
        printf("%s is %d years old again.\n",
                cur_names[i], cur_ages[i]);
    }

    printf("---\n");
	return 0;
	
}
