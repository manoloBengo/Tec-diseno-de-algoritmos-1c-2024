#include <iostream>
#include <vector>

using namespace std;

using vertice = int;
using arista = pair<vertice,vertice>;
using grafo = vector<vector<vertice>>;

grafo construir_lista_de_adyacencias(vector<arista> aristas, int n){
    vector<vector<vertice>> lista = vector<vector<vertice>>(n, vector<vertice>(0));
    vertice u;
    vertice v;
    for(int i = 0; i<aristas.size(); i++){
        u = aristas[i].first;
        v = aristas[i].second;
        lista[u-1].push_back(v);
        lista[v-1].push_back(u);
    }
    return lista;
}


// EJERCICIO 1 ---------------------------------------------
// Determinar si un gafo conexo es bipartito.
// Devolver un ciclo si no lo es, o una biparticion si lo es.

vector<vertice> ciclo_ej1;
pair<vector<vertice>, vector<vertice>> biparticion_ej1;
vector<vector<vertice>> orden_dfs;
vector<int> paridades;
int contador_paridad = 0;

void DFS(grafo G, vertice v, vertice w, int n, vector<int> &marcas){
    //cout<< w <<","<<v<<"\n";
    if(marcas[v-1] != n+1){
        paridades[v-1] = contador_paridad;
        marcas[v-1] = n+1;
        if(w!=0){
            orden_dfs[v-1].push_back(w);
            orden_dfs[w-1].push_back(v);
        }
        for(int i = 0; i<G[v-1].size(); i++){
            contador_paridad++;
            DFS(G, G[v-1][i], v, n, marcas);
            contador_paridad--;
        }
    }
}

bool grafo_conexo_es_bipartito(grafo G, int n){
    vertice v = 1;
    vector<int> marcas = vector<int>(n,0);
    orden_dfs = vector<vector<vertice>>(n,vector<vertice>(0));
    paridades = vector<int>(n);
    DFS(G,v,0,n,marcas); // Arbol generador de G. O(n+m).
    grafo T = orden_dfs;

    // Hasta aca obtuve con DFS un arbol (lista de adyacencias) generador de G, en tiempo O(n+m).
    // Ahora quiero solucionar el problema de saber si es bipartito o no.

    // NO hace falta hacer un Bucket sort en G y T, porque ya vienen ordenados ambos.
    // Ademas, T siempre va a respetar el orden dado por G.

    // Comparo las adyacencias de G y T en O(n+m).

    vector<vector<vertice>> G_T = vector<vector<vertice>>(n, vector<vertice>(0)); //O(n)
    // Los siguientes dos loops recorren una sola vez las dos listas de adyacencias G y T.
    // Esto quiere decir que iteran unas 4m veces (2m por cada lista). Esto es O(n+m).
    for(int i = 0; i<n; i++){
        int contador_t = 0;
        for(int j = 0; j<G[i].size();j++){
            if(contador_t >= T[i].size()){
                G_T[i].push_back(G[i][j]);
            }else {
                if (G[i][j] == T[i][contador_t]) {
                    contador_t++;
                } else {
                    if (G[i][j] > T[i][contador_t]) {
                        i--;
                        contador_t++;
                    } else {
                        G_T[i].push_back(G[i][j]);
                    }
                }
            }
        }
    }
    // Ya tengo a mi grafo G_T que contiene a los elementos que estan en G y no en T.

    // Ahora comparo la paridad entre todos los vertices en G_T basado en el vector paridades,
    // donde paridades[i-1] guada un numero par si el vertice i es de paridad par,
    // o un numero impar si el vertice i tiene paridad impar.
    vector<int> p = paridades;
    vertice u1,u2;
    bool es_bipartito = true;
    for(int i = 0; i<G_T.size(); i++){
        for(int j = 0; j<G_T[i].size(); j++){
            if(paridades[i]%2 == paridades[G_T[i][j]-1]%2){
                u1 = i+1;
                u2 = G_T[i][j];
                es_bipartito = false;
                break;
            }
        }
        if(!es_bipartito){
            break;
        }
    }

    // Ya determine si es o no bipartito, basado en las propiedades del enunciado.
    // Retorno una biparticion si es bipartito, o un ciclo impa si no lo es.
    if(es_bipartito){
        vector<vertice> V,W;
        for(int k = 0; k<paridades.size(); k++){
            if(paridades[k]%2 == 0){
                V.push_back(k+1);
            }else{
                W.push_back(k+1);
            }
        }
        biparticion_ej1 = make_pair(V,W);
    }else{
        //ciclo_ej1 = leaf_or_cycle(T, u1, u2); // Recordar que aca hay que agregarle la arista u1u2 a T.
    }
    return es_bipartito;
}


int main() {
    vector<arista> E = {make_pair(1,3), make_pair(1,4),
                        make_pair(1,5), make_pair(2,3),
                        make_pair(2,4), make_pair(2,5)
                        };
    int n = 5;
    grafo G = construir_lista_de_adyacencias(E,n);
    //Por como arme el algoritmo, hace falta hacer un Bucket sort en G.
    bool rta = grafo_conexo_es_bipartito(G,n);
    if(rta){
        cout << "El grafo es bipartito.";
    }else{
        cout << "El grafo NO es bipartito.";
    }
    return 0;
}
