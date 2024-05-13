#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

// Experimentacion personal en los grafos. Nada entregable,
// solo sandbox para implementar algunos algoritmos y propiedades
// de los grafos. Muchos de aca son extraidos casi tal cual del
// libro de Cormen, "Introduction to Algorithms".


// Estucturas:

//1.Lista de aristas.

struct Vertice {
    int valor;
    bool marcado = false;
};

struct Edge {
    int peso = 1;
    int u;
    bool marcado_u = false;
    int v;
    bool marcado_v = false;
};

struct Grafo {

    vector<int> vertices;
    vector<Edge> edges;
};


//2.Lista de adyacencias.

using Grafo_ady = vector<vector<Vertice>>;

// Algoritmos:
using camino = vector<Edge>;
using pesos = vector<int>;

void ordenar_por_peso(Grafo &G){ //a chequear
    // ordenar crecientemente los edges por su peso en O(n.log(n)).
}

int encontrar_set(vector<vector<int>> &sets, int v){ //a chequear
    int set_id;
    for(int i = 0; i< sets.size(); i++){
        for(int j = 0; j<sets[i].size(); j++){
            if(sets[i][j] == v){
                set_id = i;
            }
        }
    }
    return set_id;
}

void unir_sets(Grafo G, vector<vector<int>> &sets, int u, int v){ //a chequear
    int set1_id = encontrar_set(sets, u);
    int set2_id = encontrar_set(sets, v);
    for(int i = 0; i<sets[set2_id].size(); i++){
        sets[set1_id].push_back(sets[set1_id][i]);
    }
    sets[set2_id] = {};
}

camino mst_Kruskal(Grafo G){ //a chequear
    vector<Edge> A;
    vector<vector<int>> sets;
    for(int i = 0; i < G.vertices.size(); i++){
        vector<int> set_simple = {G.vertices[i]};
        sets.push_back(set_simple);
    }
    ordenar_por_peso(G);
    for(int e = 0; e < G.edges.size(); e++){
        int u = G.edges[e].u;
        int v = G.edges[e].v;
        if(encontrar_set(sets, u) != encontrar_set(sets, v)){
            A.push_back(G.edges[e]);
            unir_sets(G, sets, u, v);
        }
    }
    return A;
}


//ej 15 p3 --------------------------

//mejora que le falta para cumplir con la complejidad:
//  -Ordenar D
bool algoritmo_subcuadratico_ej15_p1(vector<Edge> E, int n) {
    vector<vector<Vertice>> N(n);
    vector<int> D = vector<int>(n, 0);
    int m = E.size();
    for (int i = 0; i < E.size(); i++) {          //1.
        Vertice U;
        Vertice V;
        U.valor = E[i].u;
        V.valor = E[i].v;
        N[V.valor - 1].push_back(U);
        N[U.valor - 1].push_back(V);
        D[U.valor - 1] = D[U.valor - 1] + 1;
        D[V.valor - 1] = D[V.valor - 1] + 1;
    }
    for (int i = 1; i <= n; i++) {
        if (D[i - 1] >= sqrt(m)) {                    //2.
            for (int j = 0; j < N[i - 1].size(); j++) {
                N[i - 1][j].marcado = true;           //3.
            }
            for (int e = 0; e < E.size(); e++) {
                if (E[e].marcado_u and E[e].marcado_v) {
                    return true;                    //4.
                }
            }
            for (int j = 0; j < N[i - 1].size(); j++) {
                N[i - 1][j].marcado = false;           //5.
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (D[i - 1] < sqrt(m)) {                   //6.
            for (int j = 0; j < N[i - 1].size(); j++) {
                N[i - 1][j].marcado = true;           //7.
            }
            for (int k = 1; k <= N[i - 1].size(); k++){
                if(D[k - 1] < sqrt(m)){             //8.
                    for(int l = 1; l<=N[k - 1].size(); l++){
                        if(N[N[i-1][k-1].valor - 1][l - 1].marcado){
                            return true;                  //9.
                        }
                    }
                }
            }
            for (int j = 0; j < N[i - 1].size(); j++) {
                N[i - 1][j].marcado = false;           //10.
            }
        }
    }
    return false;
}

// main:
int main() {
    int n = 5;
    vector<Edge> aristas;
    vector<pair<int,int>> E = {make_pair(1,2),
                      //make_pair(1,3),
                      make_pair(1,5),
                      make_pair(2,4),
                      make_pair(3,4),
                      make_pair(3,5),
                      make_pair(1,4),
                      make_pair(2,3)
                    };
    Edge e;
    for(int i = 0; i <E.size();i++){
        e.u = E[i].first;
        e.v = E[i].second;
        aristas.push_back(e);
    }
    bool rta = algoritmo_subcuadratico_ej15_p1(aristas, n);
    cout << rta;
    return 0;
}
