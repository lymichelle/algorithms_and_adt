// Michelle Ly
// mly8
// pa2

// This program will read a file containing numbers and will be sorted
// in alphabetical order and stored into a doubly linked list.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){
        int n = 0, count=0;
        FILE *in, *out;
        char line[MAX_LEN];
        List A = newList();
        // Check command line for correct number of arguments.
        if( argc != 3 ){
                printf("Usage: %s <input file> <output file>\n", argv[0]);
                exit(1);
        }
        // Open files for reading and writing 
        in = fopen(argv[1], "r");
        out = fopen(argv[2], "w");
        if( in==NULL ){
                printf("Unable to open file %s for reading\n", argv[1]);
                exit(1);
        }
        if( out==NULL ){
                printf("Unable to open file %s for writing\n", argv[2]);
                exit(1);
        }
        // Read each line of input file and update count
        while( fgets(line, MAX_LEN, in) != NULL)  {
                count++;
        }
        fclose(in);
        in = fopen(argv[1], "r");
        char array[count][MAX_LEN];
        while( fgets(line, MAX_LEN, in) != NULL && n < count){
                strcpy(array[n], line);
                n++;
        }
        prepend(A, 0);
        // Compare the strings and sort them accordingly
        for(int j=1; j<count; j++){
                moveFront(A);
                while(index(A)>=0){
                        if(strcmp(array[j], array[get(A)]) <= 0){
                                insertBefore(A, j);
                                break;
                        }
                        moveNext(A);
                }
                if(index(A)==-1){
                        append(A, j);
                }
        }
        moveFront(A);
        while(index(A) != -1){
                fprintf(out, "%s", array[get(A)]);
                moveNext(A);
        }
        // Close files, free list
        fclose(in);
        fclose(out);
        freeList(&A);
        return(0);
}
