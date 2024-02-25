#include<stdio.h>
CSA0488-OPERATING SYSTEM
#include<dirent.h>
main()
{
char dirname[10];
DIR*p;
struct dirent *d;
printf("Enter directory name\n");
scanf("%s",dirname);
p=opendir(dirname);
if(p==NULL)
 {
 perror("Cannot find directory");
 exit(-1);
 }
while(d=readdir(p))
 printf("%s\n",d->d_name);
}
28. Write a C program for simulation of GREP UNIX command 
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) {
 if (argc != 3) {
 printf("Usage: %s [Operating System] [SSE]\n", argv[0]);
 return 1;
 }
 char *search_string = argv[1];
 char *file_name = argv[2];
 FILE *file = fopen(file_name, "r");
 if (!file) {
 printf("Error opening file\n");
 return 1;
 }
 char line[256];
 while (fgets(line, sizeof(line), file)) {
 if (strstr(line, search_string)) {
 printf("%s", line);
 }
 }
 fclose(file);
 return 0;
