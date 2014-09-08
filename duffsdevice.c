#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

int duffs_device(char *from, char *to, int count);

int main(int argc,char *argv[])
{
	int i = atoi(argv[1]);
	char *from = "1234567890";
	char *to  = calloc(1,10);
	duffs_device(from,to,i);
	log_info("to is : %s",to);
	return 0;
}

int duffs_device(char *from, char *to, int count)
{
    {
        int n = (count + 7) / 8;

        switch(count % 8) {
            case 0: do { 
            			*to++ = *from++;
                        case 7: *to++ = *from++;
                        case 6: *to++ = *from++;
                        case 5: *to++ = *from++;
                        case 4: *to++ = *from++;
                        case 3: *to++ = *from++;
                        case 2: *to++ = *from++;
                        case 1: *to++ = *from++;
                    } while(--n > 0);
        }
    }

    return count;
}
