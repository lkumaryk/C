//to search a string in file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CS 1500
#define RS 1000

int main(int argc, char const *argv[])
{
    char line[RS][CS];
   // char fname[20];
    FILE *fptr = NULL; 
    int i = 1;
    int find_result = 0;
    char t[512];
    if((fptr = fopen(argv[1], "r")) == NULL) {
	return(-1);
    }
    while(fgets(t, 512, fptr) != NULL) {
	if((strstr(t, argv[2])) != NULL) {
		printf("String found on line: %d\n", i);
		printf("\n%s\n", t);
		find_result++;
	}
	i++;
    }
    printf("\n");
    return 0;
}

