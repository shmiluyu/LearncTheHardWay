#include <unistd.h>
#include <stdio.h>

int main()
{
	if(access("/home/shmiluyu/.abcdefg",W_OK | X_OK)==-1){
		printf("folder doesn't exist");
	}
	
	FILE *db = fopen("/home/shmiluyu/git/demo.txt","w");
	fclose(db);
	return 0;
}
