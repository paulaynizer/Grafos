#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

enum Cor {WHITE,GRAY,BLACK};
int color[1001], d[1001], p[1001], f[1001], t,vertex, edge;
char nota[1001];
int NIL = numeric_limits<int>::min();

class Grafo
{
	int V; // numero de vertices
	vector<int> *adj; // ponteiro para um array contendo as listas de adjacencias

    public:
	Grafo(int V); // construtor
	void adicionarAresta(int v1, int v2); // adiciona uma aresta no grafo
    void DFS();
    void DFSVisit(int u);
    void varinhaMagica(int u, int v);
};

Grafo::Grafo(int V)
{
	this->V = V; // atribui o numero de vertices
	adj= new vector<int>[V+1]; // cria as listas
}

void Grafo::adicionarAresta(int v1, int v2)
{
	// adiciona vertice v2 a  lista de vertices adjacentes de v1
	adj[v1].push_back(v2);
}

void Grafo :: varinhaMagica(int u, int v){
	if(nota[adj[u][v]]=='B'&&nota[u]=='A'){
    		nota[adj[u][v]]='A';
			nota[u]='B';	
	}else if(nota[u]=='B'&&nota[adj[u][v]]=='A'){
		nota[u]='A';
		nota[adj[u][v]]='B';
	}
	else if(nota[u]=='B'&&nota[adj[u][v]]=='B'){
		nota[u]='A';
		nota[adj[u][v]]='A';
	}
	
}


void Grafo::DFS() {
   
    for(int u=0; u<=vertex; u++) {
        
        color[u] = WHITE;
        p[u] = NIL;
    }
    t = 0;
    for(int u=1; u<=vertex; u++) {
       
        if(color[u] == WHITE) {
        
            DFSVisit(u);
            
        }
    }
    
}

void Grafo :: DFSVisit(int u) {
 
    t = t + 1;
    d[u] = t;
    color[u] = GRAY;
   
    
    for(int v=0; v<adj[u].size(); v++) {
        
     
        if(color[adj[u][v]] == WHITE) {
            
            p[adj[u][v]] = u;
            DFSVisit(adj[u][v]);
            //cout<<"nota[u]"<<nota[u]<<endl;
            //cout<<"(nota[adj[u][adj[u].size()-1]]:"<<nota[adj[u][adj[u].size()-1]]<<endl;
            if((nota[adj[u][v]]!='A')||(nota[u]!='A')){
    			//cout<<"u: "<<u<<" faz troca"<<endl;
    			varinhaMagica(u, v);
			}
			else{
				//cout<<"u: "<<u<<"ta ok"<<endl;
			}
        }
        
    }
    color[u] = BLACK;
    t = t + 1;
    f[u] = t;
   	
    
   
}
int main()
{
	vector<int> adj[4001];
    int n;//numero de vertices
    int m;//numero de arestas
 
    freopen("entrada.txt", "r", stdin);
	while (cin>> n>>m)
    {
        bool possivel=true;
        Grafo grafo(n);
       vertex=n;
        char notas[1001];
        int u, v;
        
        for(int i=1;i<=vertex;i++){
            cin>>nota[i];
        }
        for(int i =1;i<=m;i++){
            cin>>u>>v;
            grafo.adicionarAresta(u,v);
        }
        grafo.DFS();
        for(int i=1; i<=vertex; i++) {
            //printf("v%d (%d/%d)\n", i, d[i], f[i]);
            //cout<<"nota:"<<nota[i]<<endl;
            if(nota[i]=='B'){
            	possivel=false;
			}
        }
        if(possivel==true){
        	cout<<"Y"<<endl;
		}
		else{
			cout<<"N"<<endl;
		}
	    
    }
}
