// Michelle Ly
// mly8
// pa4

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
        int *distance;
        int order;
        int size;
        int source;
};

/*** Constructors-Destructors ***/
//Returns graph pointing to newly created GraphObj
Graph newGraph(int n){
        Graph G = malloc(sizeof(struct GraphObj));
        G->neighbor = calloc(n + 1, sizeof(List));
        G->color = calloc(n + 1, sizeof(int));
        G->parent = calloc(n + 1, sizeof(int));
        G->distance = calloc(n + 1, sizeof(int));
        G->order = n;
        G->size = 0;
        G->source = NIL;
        for(int i = 0; i < (n + 1); i++) {
                G->neighbor[i] = newList();
                G->color[i] = WHITE;
                G->parent[i] = NIL;
                G->distance[i] = INF;
        }
        return G;       
}
//Frees all dynamic memory associated with the Graph *pG, then sets the handle *pG to NULL
void freeGraph(Graph* pG){
        Graph oldG = *pG;
        for(int i = 0; i < (oldG->order + 1); i++) {
                freeList(&(oldG->neighbor[i]));
        }
        free(oldG->neighbor);
        free(oldG->color);
        free(oldG->parent);
        free(oldG->distance);
        free(*pG);
        *pG = NULL;
}

/*** Access functions ***/
//Returns order
int getOrder(Graph G){
        return G->order;
}
//Returns size
int getSize(Graph G){
        return G->size;
}
//Returns the source vertex most recently used in BFS()
int getSource(Graph G){
        return G->source;
}
//Returns the parent
// Pre: u >= 1 && u <= getOrder(G)
int getParent(Graph G, int u){
        if(u < 1 || u > getOrder(G)) {
                printf("Graph Error: calling getParent() on vertex out of bounds\n");
                exit(1); 
        }
        return G->parent[u];
}
//Returns the distance from the most recent BFS source to vertex u
// Pre: u >= 1 && u <= getOrder(G)
int getDist(Graph G, int u){
        if(u < 1 || u > getOrder(G)) {
                printf("Graph Error: calling getDist() on vertex out of bounds\n");
                exit(1); 
        }
        if(getSource(G) == NIL) {
                return INF;
        }
        return G->distance[u];
        
}
//Appends to the List L the vertices of a shortest path in G from course to u, or appends to
//L the value NIL if no such path exists
// Pre: u >= 1 && u <= getOrder(G)
// Pre: getSource(G) != NIL
void getPath(List L, Graph G, int u){
        if(u < 1 || u > getOrder(G)) {
                printf("Graph Error: calling getPath() on vertex out of bounds\n");
                exit(1); 
        }
        if(getSource(G) == NIL){
                printf("Graph Error: BFS() has not yet been called\n");
                exit(1);
        }
        int gs = G->source;
        if(u == gs) {
                prepend(L, gs);
        }else if(G->parent[u] == NIL) {
                append(L, NIL);
        } else {
                prepend(L, u);
                getPath(L, G, G->parent[u]);
        }
}

/*** Manipulation procedures ***/
//Deletes all edges of G, resorting it to its original no edge state
void makeNull(Graph G){
        for(int i = 0; i < (G->order+1); i++){
                clear(G->neighbor[i]);
        }
}
//Inserts a new edge joining u to v
// Pre: 1 < u < getOrder(G) && 1 < v < getOrder(G)
void addEdge(Graph G, int u, int v){
        if((u < 1 || u > getOrder(G)) && (v < 1 || v > getOrder)){
                printf("Graph Error: calling addEdge() on vertex out of bounds\n");
                exit(1);
        }
        addArc(G, u, v);
        addArc(G, v, u);
        G->size--;
}
//Inserts a new directed edge from u to v
// Pre: 1 < u < getOrder(G) && 1 < v < getOrder(G)
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
//Runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent,
//and source fields accordingly
void BFS(Graph G, int s){
        for(int i = 0; i < (G->order+1); i++) {
                G->parent[i] = NIL;
                G->distance[i] = INF;
                G->color[i] = WHITE;
        }
        G->source = s;
        G->distance[s] = 0;
        G->color[s] = GRAY;
        List L = newList();
        prepend(L, s);
        while(length(L) > 0) {
                int e = back(L);
                deleteBack(L);
                List neighbor = G->neighbor[e];
                moveFront(neighbor);
                while(index(neighbor) > -1) {
                        int v = get(neighbor);
                        if(G->color[v] == WHITE) {
                                G->color[v] = GRAY;
                                G->parent[v] = e;
                                G->distance[v] = G->distance[e] + 1;
                                prepend(L, v);
                        }
                        moveNext(neighbor);
                }
        }
        freeList(&L);   
}
/*** Other operations ***/
//Prints the adjecency list representation of G to the file pointed by out
void printGraph(FILE* out, Graph G){
        for(int i = 1; i <= getOrder(G); i++) {
                fprintf(out, "%d: ", i);
                printList(out, G->neighbor[i]);
                fprintf(out, "\n");
        }       
}
