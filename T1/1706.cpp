#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>
#include <queue>



using namespace std;

enum Cor {WHITE,GRAY,BLACK};
int color[1001], d[1001], p[1001], f[1001], t,vertex, edge;
char nota[1001];
int NIL = numeric_limits<int>::min();
int INF = numeric_limits<int>::max();
bool possivel;


class Grafo
{
	int V; // numero de vertices
	vector<int> *adj; // ponteiro para um array contendo as listas de adjacencias

    public:
	Grafo(int V); // construtor
	void adicionarAresta(int v1, int v2); // adiciona uma aresta no grafo
    bool BFS(int s, int k);
    void varinhaMagica(int v, int u);
  
};

Grafo::Grafo(int V)
{
	this->V = V; // atribui o numero de vertices
	adj= new vector<int>[V+1]; // cria as listas
}

void Grafo::adicionarAresta(int v1, int v2)
{
	
	adj[v1].push_back(v2);
	

}
void Grafo::varinhaMagica(int v, int u)
{
	nota[v]='A';
	nota[u]='A';
	

}

bool Grafo :: BFS(int s, int k){
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

    queue<int> Q; Q.push(s);

    while( !Q.empty()) {
        
        int u = Q.front(); Q.pop();
        
        for(int v=0; v<adj[u].size(); v++) {
            if (v== k){
                //cout<<"entraaq"<<endl;
                return true;
            }
            if(color[adj[u][v]] == WHITE) {
                if (adj[u][v]== k){
                    //cout<<"entraaq"<<endl;
                    return true;
                }
                color[adj[u][v]] = GRAY;
                d[adj[u][v]] = d[u] + v;
                p[adj[u][v]] = u;
                p[u] = adj[u][v];
                Q.push(adj[u][v]);
            }
        }
        color[u] = BLACK;
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
        Grafo grafo(n);
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
            grafo.adicionarAresta(u,v);
            grafo.adicionarAresta(v,u);
        }
      	//conta a quantidade de b
        for(int u=1;u<=vertex;u++){
        	if(nota[u]=='B'){
        	    cont++;
			}
		}
        //se for par 
        if(cont%2==0){
            for(int u=1;u<=vertex;u++){//para cada vertice do grafo
                
        	    if(nota[u]=='B'){//se a nota for b
        		    if(hasB){//segundo b encontrado
        		    	if(grafo.BFS(hasB,u)){
        		    		grafo.varinhaMagica(hasB,u);
						}	    
						hasB=0; 
					}
    			    else{
    				    hasB=u;//primeiro b encontrado
			    	}
				}
		    }
			for(int u=1;u<=vertex;u++){
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
