#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Construção das Arestas //
class Aresta {
  public: int origem, destino, custo;
};

// Construção do Grafo //
class Grafo {
  public: int V, E; // V-> Número de vértices, E-> Número de Arestas.
  Aresta *aresta; // Define um ponteiro de arestas
};

// Construção para o Subconjunto //
class Subconjunto {
  public: int pai, nivel; // Declaração do pai e do nivel do Subconjunto.
};

// Cria o Grafo //
Grafo *criaGrafo(int V, int E) {
  Grafo *grafo = new Grafo;      // Inicia um novo Grafo.
  grafo->V = V;                  // V vértices.
  grafo->E = E;                  // E arestas.
  grafo->aresta = new Aresta[E]; // O grafo recebe uma nova Aresta e define o tamanho dela como E que seria o numero total de arestas possiveis.

  return grafo;
}

// Determina a definição do elemento i - Comparação de caminho //
int encontrar(Subconjunto subconjunto[], int i) {
  if (subconjunto[i].pai != i) // Encontra a raiz e a torna pai de i.
    subconjunto[i].pai = encontrar(subconjunto, subconjunto[i].pai);

  return subconjunto[i].pai;
}

// Une dois sets de x e y - união por nivel //
void unirSubconjunto(Subconjunto subconjunto[], int x, int y) {
  int raizx = encontrar(subconjunto, x); // Encontra os subconjunto de x.
  int raizy = encontrar(subconjunto, y); // Encontra os subconjunto de y.

  // Determina qual dos subconjunto é o maior, o atrelando como pai.
  if (subconjunto[raizx].nivel < subconjunto[raizy].nivel)
    subconjunto[raizx].pai = raizy;
  else if (subconjunto[raizx].nivel > subconjunto[raizy].nivel)
    subconjunto[raizy].pai = raizx;
  else { // Se os nivels são iguais, torna um deles a raiz e incremente o nivel em 1.
    subconjunto[raizy].pai = raizx;
    subconjunto[raizx].nivel++;
  }
}

// Compara duas arestas de acordo com o custo delas - ordenar crescentemente, em qsort().
int comparaCresc(const void *x, const void *y) {
  Aresta *ArrestaX = (Aresta *)x;
  Aresta *ArrestaY = (Aresta *)y;
  return ArrestaX -> custo > ArrestaY -> custo;
}

// Compara duas arestas de acordo com o custo delas - ordenar decrescentemente, em qsort().
int comparaDescr(const void *x, const void *y) {
  Aresta *ArrestaX = (Aresta *)x;
  Aresta *ArrestaY = (Aresta *)y;
  return ArrestaX -> custo < ArrestaY -> custo;
}

// Construir a árvore geradora mínima utilizando o algoritmo de Kruskal //
int Kruskal(Grafo *grafo) {
  int custoTotal = 0;
  int V = grafo->V;
  Aresta resultado[V]; // Armazena a árvore geradora mínima
  int e = 0; // Variável de índice para resultado[]
  int i = 0; // Variável de índice para as arestas ordenadas.

  Subconjunto *subconjunto = new Subconjunto[(V * sizeof(Subconjunto))];
  // Cria V subconjunto.

  // Determina todos como próprios pais e determina o valor como de nivel como 0.
  for (int v = 0; v < V; ++v) {
    subconjunto[v].pai = v;
    subconjunto[v].nivel = 0;
  }
  
  // Número de arestas a serem inseridas na AGM é V-1.
  while (e < V - 1 && i < grafo->E) {
    Aresta proximo_aresta = grafo->aresta[i++]; // Seleciona a menor aresta; Incrementa o índice para a próxima iteração.
    int u = encontrar(subconjunto, proximo_aresta.origem); // Determina x como o Subconjunto de origem.
    int v = encontrar(subconjunto, proximo_aresta.destino); // Determina y como o Subconjunto de destino.
    if (u != v) { // Caso o não forme um ciclo com ele mesmo.
      resultado[e++] = proximo_aresta;
      unirSubconjunto(subconjunto, u, v); // Uni os subconjunto e determina o melhor deles.
    }
    // Senão, descarta a próxima aresta (proximo_aresta)
  }

  // Determina o custo total da árvore geradora.
  for (i = 0; i < e; ++i)// Executa o for pelo número total de arestas.
    custoTotal += resultado[i].custo; // Soma os valores de cada aresta individualmente e adiciona ao custoTotal.

  return custoTotal;
}

int main() {
  int n, st[2]; // N = Número total de elementos - Árvore Geradora Mínima e Árvore Geradora Máxima.
  cin >> n; // entrada do número total de elementos.
  Grafo *grafo = criaGrafo(n, n); // Chama a função para a criação dos grafos, passando o número de elementos.
  
  for (int i = 0; i < n; i++) {
    cin >> grafo->aresta[i].origem  // Define a origem.
        >> grafo->aresta[i].destino // Define o destino.
        >> grafo->aresta[i].custo;   // Define o custo.
  }
  
  // Ordena todas as arestas em ordem de acordo com o custo que possuem.
  // Ordena em ordem crescente.
  qsort(grafo->aresta, grafo->E, sizeof(grafo->aresta[0]), comparaCresc);
  st[1] = Kruskal(grafo); // Armazena o custo da Árvore Geradora Mínima.
  
  // Ordena em ordem decrescentemente
  qsort(grafo->aresta, grafo->E, sizeof(grafo->aresta[0]), comparaDescr);
  st[0] = Kruskal(grafo); // Armazena o custo da Árvore Geradora Máxima.

  cout << st[0] << endl << st[1] << endl; // Imprime a Árvore Geradora Máxima && // Imprime a Árvore Geradora Mínima.
  return 0;
}
