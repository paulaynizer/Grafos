#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

enum Cor {WHITE,GRAY,BLACK};
int color[1001], d[1001], p[1001], f[1001], t,vertex, edge;
char nota[1001];
int NIL = numeric_limits<int>::min();
int INF = numeric_limits<int>::max();
bool possivel;

//*************** FILA ****************
//Nó da fila que aponta para o prox nó
typedef struct fila_no{
	struct fila_no * prox;
	int dado;
}fila_no;

//Ponteiros para inicio e fim da fila
typedef struct fila_t{
	fila_no * frente;
	fila_no * final;
}fila_t;

fila_t * fila_cria(){
	/*Inicializafila  */
	fila_t * nova_fila = (fila_t*)malloc(sizeof(fila_t)); 
	
	nova_fila -> frente = NULL;
	nova_fila -> final = NULL;
    return nova_fila;
}

void fila_put(fila_t * fila, int val){
	
	//Cria nó
	fila_no * novo_no = (fila_no*)malloc(sizeof(fila_no));
	novo_no -> dado = val;
	novo_no -> prox = NULL;

	
	if (fila -> frente == NULL){
		fila -> frente = fila -> final = novo_no;
	}
	
	else{
		/*O que era o último elemento, vai
		apontar para o novo último elemento*/
		fila -> final -> prox = novo_no;
		
		/*O novo elemento vai ser o final da fila*/
		fila -> final = novo_no;
	}	

}

int fila_pop(fila_t * fila){
	
	if (fila -> frente){


		
		int val = fila -> frente -> dado;
	
		fila_no * temp = fila -> frente;
		
						
		fila -> frente = fila -> frente -> prox;
		free(temp);
		return val;
	}
	
	return -1;
}


//*******************************

//****** Grafo ********
typedef struct node {
  int vertice;
  struct node* next;
}_node;


typedef struct Graph {
  int numVertices;
   node** adj;
}_Graph;

// Create a node
node * createNode(int v) {
	node * newNode = (node*)malloc(sizeof(node));
  	newNode->vertice = v;
  	newNode->next = NULL;
  	return newNode;
}

// Create a graph
Graph * createAGraph(int vertices) {
  Graph * graph = (Graph*)malloc(sizeof(Graph));
  graph->numVertices = vertices;
  
  graph->adj = (node**)malloc(vertices * sizeof(struct node*));

  int i;
  for (i = 0; i < vertices; i++)
    graph->adj[i] = NULL;

  return graph;
}

// Add edge
void addEdge(struct Graph* graph, int s, int d) {
  // Add edge from s to d
  node * newNode = createNode(d);
  newNode->next = graph->adj[s];
  graph->adj[s] = newNode;

  // Add edge from d to s
  newNode = createNode(s);
  newNode->next = graph->adj[d];
  graph->adj[d] = newNode;
}



void varinhaMagica(Graph* graph,int v, int u)
{
	nota[v]='A';
	nota[u]='A';
	

}

bool BFS(Graph* graph, int s, int k){
    node * u = graph->adj[0];
	if (s== k){
                return true;
    }
    for(int u=0; u<=vertex; u++) {
        color[u] = WHITE;
        d[u] = INF;
        p[u] = NIL;
    }

    color[s] = GRAY;
    d[s] = 0;
    p[s] = NIL;
    
	fila_t * Q = fila_cria();
    fila_put(Q, s);

    while( Q) {
    	
    	int atual = fila_pop(Q);
    
    	node* temp = graph->adj[atual];
	

        while(temp) {
        	int adjVertex = temp->vertice;
            if (adjVertex== k){
                //cout<<"entraaq"<<endl;
                return true;
            }
            if(color[adjVertex] == WHITE) {
                if (adjVertex== k){
                    //cout<<"entraaq"<<endl;
                    return true;
                }
                color[adjVertex] = GRAY;
                //d[adjVertex] = d[atual]+v;
                p[adjVertex] = atual;
                p[atual] = adjVertex;
                fila_put(Q, adjVertex);
            }
        }
        color[temp->vertice] = BLACK;
    }
    return false;
}
int main()
{
	vector<int> adj[4001];
    int n;//numero de vertices
    int m;//numero de arestas
 
  
	while (cin>> n>>m)
    {   
    	
        bool existe=true;
        Graph* graph = createAGraph(n);
        vertex=n;

        char notas[1001];
        int u, v;
        int hasB=0;
        int cont=0;
        for(int i=1;i<=vertex;i++){
            cin>>nota[i];
        }
        for(int i =1;i<=m;i++){
            cin>>u>>v;
            addEdge(graph,u,v);
           
        }
      	//conta a quantidade de B
        for(int u=1;u<=vertex;u++){
        	if(nota[u]=='B'){
        	    cont++;
			}
		}
        //se for par 
        if(cont%2==0){
            for(int u=1;u<=vertex;u++){//para cada vertice do grafo
                
        	    if(nota[u]=='B'){//se a nota for B
        		    if(hasB){//segundo B encontrado
        		    	if(BFS(graph,hasB,u)){
        		    		varinhaMagica(graph,hasB,u);//faz troca
						}	    
						hasB=0; 
					}
    			    else{
    				    hasB=u;//primeiro B encontrado
			    	}
				}
		    }
			for(int u=1;u<=vertex;u++){//se todas as notas são A
				if(nota[u]=='B'){
					existe=false;
				}
			}
			if(existe==true){
				cout<<"Y"<<endl;
			}
			else{
				cout<<"N"<<endl;
			}
        }//se for impar
        else{
			cout<<"N"<<endl;
		}
    }
    return 0;
}
