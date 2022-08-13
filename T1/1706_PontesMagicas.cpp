#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

enum Cor {WHITE,GRAY,BLACK};
int color[1001], d[1001], p[1001], f[1001],vertex;
char nota[1001];
int NIL = 0;
int INF = -1;


//bfs para verificar se existe caminho entre s e k
bool BFS(vector<int> adj[], int s, int k){
    if (s== k){
        return true;
    }
    //inicializa os vetores color[], p[] e d[]
    for(int u=0; u<=vertex; u++) {
        color[u] = WHITE;
        d[u] = INF;
        p[u] = NIL;
    }

    color[s] = GRAY;
    d[s] = INF;
    p[s] = NIL;

    //inicia fila de nós a serem processados com s
    queue<int> Q; Q.push(s);

    //enquanto a fila não estiver vazia
    while( !Q.empty()) {
        //u recebe o primeiro elemento da fila
        int u = Q.front(); Q.pop();
        //para cada vértice da lista de adjascencia de u
        for(int v=0; v<adj[u].size(); v++) {
            //se ainda não foi descoberto
            if(color[adj[u][v]] == WHITE) {
                //se encontrou o vertice k existe um caminho
                if (adj[u][v]== k){
                    return true;
                }
                color[adj[u][v]] = GRAY;
                d[adj[u][v]] = d[u] + v;
                p[adj[u][v]] = u;
                p[u] = adj[u][v];
                Q.push(adj[u][v]);//adiciona o vertice v da lista de adjacencia de u na fila Q
            }
        }
        //finaliza vertice
        color[u] = BLACK;
    }
    return false;
}
//faz as trocas da varinha mágica e 
//retorna se existe caminho entre todos os Bs encontrados
bool existeCaminho(vector<int> adj[], char nota[]){
    int hasB=0;
    for(int u=1;u<=vertex;u++){
        //para cada vertice do grafo
                
        if(nota[u]=='B'){
            //se a nota for b
        	if(hasB){
        	    //segundo b encontrado
                //chama BFS()para verificar se existe um caminho
                //entre os dois Bs encontrados
        		if(BFS(adj,hasB,u)){
        		   nota[hasB]='A';//varinha mágica
	               nota[u]='A';//varinha mágica
				}
			    hasB=0; 
		    }
    	    else{
    	        hasB=u;//primeiro b encontrado
	        
    	    }
        }
    }
    //verifica se restou uma nota B depois das trocas
	for(int u=1;u<=vertex;u++){
		if(nota[u]=='B'){
            //se encontrou uma nota B retorna false
			return false;
		}
	}
    //todas as notas são A, retorna true
	return true;
}
int main()
{

    int n;//numero de vertices
    int m;//numero de arestas
 
    //le numero de vértices e arestas
	while (cin>> n>>m)
    {   
    	
        vertex=n;
        vector<int> adj[vertex+1];//cria o vetor de adjacência
        char notas[1001];//vetor das notas musicais
        int u, v; //arco(u,v) do grafo
        int cont=0; //contador
        
        //le nota e conta a quantidade de Bs
        for(int i=1;i<=vertex;i++){
            cin>>nota[i];
            //conta as notas Bs encontradas
            if(nota[i]=='B'){
        	    cont++;
			}
        }
        //le e adiciona aresta
        for(int i =1;i<=m;i++){
            cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);//grafo não direcionado
        }
      	
        //se a quantidade de Bs for par 
        if(cont%2==0){
            //verifica se existe caminho entre os dois bs
            if(existeCaminho(adj, nota)){
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
