// Michelle Ly
// mly8
// pa5

//-----------------------------------------------------------------------------
// GraphTest.c
// Test client for the Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char* argv[]){
        int i, n=8;
        List S = newList();
        Graph G = newGraph(n);
        Graph T=NULL, C=NULL;
        
        for(i=1; i<=n; i++) append(S, i);
        
        addArc(G, 1,2);
        addArc(G, 1,5);
        addArc(G, 2,5);
        addArc(G, 2,6);
        addArc(G, 3,2);
        addArc(G, 3,4);
        addArc(G, 3,6);
        addArc(G, 3,7);
        addArc(G, 3,8);
        addArc(G, 6,5);
        addArc(G, 6,7);
        addArc(G, 8,4);
        addArc(G, 8,7);
        printGraph(stdout, G);
        
        DFS(G, S);
        fprintf(stdout, "\n");
        fprintf(stdout, "x:  d  f  p\n");
        for(i=1; i<=n; i++){
                fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
        }
        fprintf(stdout, "\n");
        printList(stdout, S);
        fprintf(stdout, "\n");
        
        T = transpose(G);
        C = copyGraph(G);
        fprintf(stdout, "\n");
        printGraph(stdout, C);
        fprintf(stdout, "\n");
        printGraph(stdout, T);
        fprintf(stdout, "\n");
        
        DFS(T, S);
        fprintf(stdout, "\n");
        fprintf(stdout, "x:  d  f  p\n");
        for(i=1; i<=n; i++){
                fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
        }
        fprintf(stdout, "\n");
        printList(stdout, S);
        fprintf(stdout, "\n");
        
        List L = newList();
        for(int i = 1; i <= 10; i++){
                append(L, i);
        }
        
        Graph M = newGraph(10);
        addEdge(M, 1, 2);
        addEdge(M, 3, 4);
        
        DFS(M, L);
        fprintf(stdout, "\n");
        fprintf(stdout, "x:  d  f  p\n");
        for(i=1; i<=n; i++){
                fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(M, i), getFinish(M, i), getParent(M, i));
        }
        fprintf(stdout, "\n");  
        
        Graph J = transpose(M);
        DFS(J, L);
        for(i=1; i<=n; i++){
                fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(M, i), getFinish(M, i), getParent(M, i));
        }
        fprintf(stdout, "\n");          
        
        freeList(&L);
        freeList(&S);
        freeGraph(&G);
        freeGraph(&T);
        freeGraph(&C);
        freeGraph(&M);
        freeGraph(&J);
        return(0);
}