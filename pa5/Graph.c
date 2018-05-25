// Michelle Ly
// mly8
// pa5

//This is a Graph ADT, representing a graph as an array of Lists.

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

#define WHITE 1
#define GRAY 2
#define BLACK 3

//Graph object
struct GraphObj{
        List *neighbor;
        int *color;
        int *parent;
        int order;
        int size;
        int *discover;
        int *finish;
};

/* Constructors-Destructors */
Graph newGraph(int n){
        Graph G = malloc(sizeof(struct GraphObj));
        G->neighbor = calloc(n + 1, sizeof(List));
        G->color = calloc(n + 1, sizeof(int));
        G->parent = calloc(n + 1, sizeof(int));
        G->discover = calloc(n + 1, sizeof(int));
        G->finish = calloc(n + 1, sizeof(int));
        G->order = n;
        G->size = 0;
        for(int i = 0; i < (n + 1); i++) {
                G->neighbor[i] = newList();
                G->color[i] = WHITE;
                G->parent[i] = NIL;
                G->discover[i] = UNDEF;
                G->finish[i] = UNDEF;
        }
        return G; 
}
void freeGraph(Graph* pG){
        Graph oldG = *pG;
        for(int i = 0; i < (oldG->order + 1); i++) {
                freeList(&(oldG->neighbor[i]));
        }
        free(oldG->neighbor);
        free(oldG->color);
        free(oldG->parent);
        free(oldG->discover);
        free(oldG->finish);
        free(*pG);
        *pG = NULL;
}
/* Access functions */
//Returns the order of graph
int getOrder(Graph G){
        return G->order;
}
//Returns the size of graph
int getSize(Graph G){
        return G->size;
}
//Returns the parent
/* Pre: 1<=u<=n=getOrder(G) */
int getParent(Graph G, int u){
        if(u < 1 || u > getOrder(G)) {
                printf("Graph Error: calling getParent() on vertex out of bounds\n");
                exit(1); 
        }
        return G->parent[u];
}
//Returns the discover time
/* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u){
        if(u < 1 || u > getOrder(G)) {
                printf("Graph Error: calling getDiscover() on vertex out of bounds\n");
                exit(1); 
        }
        return G->discover[u];
}
//Returns the finish time
/* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u){
        if(u < 1 || u > getOrder(G)) {
                printf("Graph Error: calling getFinish() on vertex out of bounds\n");
                exit(1); 
        }
        return G->finish[u];
}
/* Manipulation procedures */
//Adds an arc
/* Pre: 1<=u<=n, 1<=v<=n */
void addArc(Graph G, int u, int v){
        if((u < 1 || u > getOrder(G)) && (v < 1 || v > getOrder)){
                printf("Graph Error: calling addArc() on vertex out of bounds\n");
                exit(1);
        }
        List L = G->neighbor[u];
        moveFront(L);
        while(index(L) > -1 && v > get(L)) {
                moveNext(L);
        }
        if(index(L) == -1)
                append(L, v);
        else 
                insertBefore(L, v);
        G->size++;      
}
//Adds an edge; essentially adding arcs to and from two vertices
/* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v){
        if((u < 1 || u > getOrder(G)) && (v < 1 || v > getOrder)){
                printf("Graph Error: calling addEdge() on vertex out of bounds\n");
                exit(1);
        }
        addArc(G, u, v);
        addArc(G, v, u);
        G->size--;      
}
//Depth first search of graph
/* Pre: length(S)==getOrder(G) */
void DFS(Graph G, List S){
        if(length(S)!=getOrder(G)){
                printf("Graph Error: calling DFS() on mismatched length\n");
                exit(1);
        }
        for(int i = 0; i < (G->order+1); i++) {
                G->color[i] = WHITE;
                G->parent[i] = NIL;
                G->discover[i] = UNDEF;
                G->finish[i] = UNDEF;
        }
        int time = 0;
        moveFront(S);
        while(index(S) >= 0) {
                int i = get(S);
                if(G->color[i]==WHITE){
                        visit(G, S, i, &time);
                }
                moveNext(S);
        }
        int half = length(S)/2;
        for(int k = half; k > 0; k--){
                deleteBack(S);
        }
}
//Recursive helper function for DFS()
void visit(Graph G, List S, int x, int *time){
        G->color[x] = GRAY;
        G->discover[x] = (++*time);
        int adj = G->neighbor[x];
        moveFront(adj);
        while(index(adj) >= 0){
                int j = get(adj);
                if(G->color[j] == WHITE){
                        G->parent[j] = x;
                        visit(G, S, j, time);
                }
                moveNext(adj);  
        }
        G->color[x] = BLACK;
        G->finish[x] = (++*time);
        prepend(S, x);
}
/* Other Functions */
//Returns transposed copy of graph
Graph transpose(Graph G){
        Graph T = newGraph(getOrder(G));
        for(int i = 0; i < (G->order+1); i++){
                int adj = G->neighbor[i];
                moveFront(adj);
                while(index(adj) >= 0){
                        addArc(T, get(adj), i);
                        moveNext(adj);
                }
        }
        return T;
}
//Returns copy of graph
Graph copyGraph(Graph G){
        Graph C = newGraph(getOrder(G));
        for(int i = 0; i < (G->order+1); i++){
                int adj = G->neighbor[i];
                moveFront(adj);
                while(index(adj) >= 0){
                        addArc(C, i, get(adj));
                        moveNext(adj);
                }
        }
        return C;
}
//Prints graph's adj list
void printGraph(FILE* out , Graph G){
        for(int i = 1; i <= getOrder(G); i++) {
                fprintf(out, "%d: ", i);
                printList(out, G->neighbor[i]);
        }  
}