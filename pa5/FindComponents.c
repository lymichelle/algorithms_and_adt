// Michelle Ly
// mly8
// pa5

//This program will:
//      Read the input file.
//      Assemble a graph object G using newGraph() and addArc().
//      Print the adjacency list representation of G to the output file.
//      Run DFS on G and G transpose, processing the vertices in the second call by decreasing finish times fromthe first call.
//      Determine the strong components of G.
//      Print the strong components of G to the output file in topologically sorted order.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"

#define MAX_LEN 250

int main(int argc, char * argv[]){
        int n = 0, count=0, scc=0, temp=0;
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
        
        //Populate list
        List L = newList();
        for(int i = 1; i <= n; i++){
                append(L, i);
        }
        Graph G = newGraph(n);
        //Adds arc from each line
        while( fgets(line, MAX_LEN, in) != NULL)  {
                int x = 0;
                int y = 0;
                sscanf(line, "%d %d", &x, &y);
                if(x == 0 && y == 0){
                        break;
                }
                addArc(G, x, y);
        }
        //Find the strongly connected components
        DFS(G, L);
        Graph T = transpose(G);
        DFS(T, L);
        moveFront(L);
        while(index(L) >= 0){
                if(getParent(T, get(L)) == NIL){
                        scc++;
                }
                moveNext(L);
        }
        List S[scc];
        for(int j = 0; j < scc; j++){
                S[j] = newList();
        }
        moveFront(L);
        temp = scc;
        while(index(L) >= 0){
                if(getParent(T, get(L)) == NIL){
                        temp--;
                }
                if(temp == scc){
                        break;
                }
                append(S[temp], get(L));
                moveNext(L);
        }
        //Print the adj list and scc in topologically sorted order
        fprintf(out, "Adjacency list representation of G:\n");
        printGraph(out, G);
        fprintf(out, "\n");
        fprintf(out, "G contains %d strongly connected components:\n", scc);
        for(int k = 0; k < scc; k++){
                fprintf(out, "Component %d: ", k+1);
                printList(out, S[k]);
                freeList(&S[k]);
        }
        
        //Free the rest of the graphs and lists
        freeGraph(&G);
        freeList(&L);
        freeGraph(&T);
        /* close files */
        fclose(in);
        fclose(out);
        
        return(0);
}