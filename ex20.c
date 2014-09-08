#include "debug.h"
#include <stdio.h>
#include <stdlib.h>

void test_debug()
{
	debug("I have Brown Hair.");
	
	debug("I am %d years old.",37);
}
void test_log_warn()
{
	log_warn("you can safely ignore this.");
	log_warn("maybe consider looking at : %s.","/ect/passwd");
}
void test_log_err()
{
    log_err("I believe everything is broken.");
    log_err("There are %d problems in %s.", 0, "space");
}
void test_log_info()
{
    log_info("Well I did something mundane.");
    log_info("It happened %f times today.", 1.3f);
}
int test_check(char *file_name)
{
    FILE *input = NULL;
    char *block = NULL;

    block = malloc(100);
    check_mem(block); // should work

    input = fopen(file_name,"r");
    check(input, "Failed to open %s.", file_name);

    free(block);
    fclose(input);
    return 0;

error:
    if(block) free(block);
    if(input) fclose(input);
    return -1;
}

int main(int argc,char *argv[]){
	check(argc==2,"Need an argument.");
	test_debug();
	test_log_err();
    test_log_warn();
    test_log_info();
    
    check(test_check("ex20.c")==0,"no ex20.cc file exists");
    check(test_check(argv[1]) == -1, "failed with argv");
	return 0;
error:
	return 1;
}
