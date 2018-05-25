// Michelle Ly
// mly8
// pa4

//This program will read an input file, insert its contents into an adjacency list,
//and print the distances and shortest paths

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"

#define MAX_LEN 250

int main(int argc, char * argv[]){
        int n = 0, count=0;
        FILE *in, *out;
        char line[MAX_LEN];
        
        // check command line for correct number of arguments
        if( argc != 3 ){
                printf("Usage: %s <input file> <output file>\n", argv[0]);
                exit(1);
        }
        
        // open files for reading and writing 
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
        
        fgets(line, MAX_LEN, in);
        sscanf(line, "%d", &n);
   
        Graph G = newGraph(n);
        
        //Adds edge from each line
        while( fgets(line, MAX_LEN, in) != NULL)  {
                int x = 0;
                int y = 0;
                sscanf(line, "%d %d", &x, &y);
                if(x == 0 && y == 0){
                        break;
                }
                addEdge(G, x, y);
        }
        
        //Prints the adjacency list
        printGraph(out, G);
        
        //Prints distance and shortest path
        while( fgets(line, MAX_LEN, in) != NULL)  {
                int x = 0;
                int y = 0;
                sscanf(line, "%d %d", &x, &y);
                if(x == 0 && y == 0){
                        break;
                }
                if(count++ != 0){
                        fprintf(out, "\n");
                }
                fprintf(out, "\n");
                BFS(G, x);
                int d = getDist(G, y);
                fprintf(out, "The distance from %d to %d is ", x, y);
                if(d != INF){
                        fprintf(out, "%d\n", d);
                        
                }
                else{
                        fprintf(out, "infinity\n");
                }
                List L = newList();
                getPath(L, G, y);
                if(front(L) != NIL){
                        fprintf(out, "A shortest %d-%d path is: ", x, y);
                        printList(out, L);
                }
                else {
                        fprintf(out, "No %d-%d path exists", x, y);     
                }
                freeList(&L);
        }
        fprintf(out, "\n");
        freeGraph(&G);
        /* close files */
        fclose(in);
        fclose(out);
        
        return(0);
}