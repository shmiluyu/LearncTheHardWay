#include <unistd.h>
#include <stdio.h>

int main()
{
	if(access("/home/shmiluyu/.abcdefg",W_OK | X_OK)==-1){
		printf("folder doesn't exist");
	}
	return 0;
}
