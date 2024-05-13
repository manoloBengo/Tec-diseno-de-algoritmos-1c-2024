#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <limits>
#include <queue>

using namespace std;

using id = int;
using peso = int;
using nivel = int;
using arista = pair<id, id>;
int infinito = numeric_limits<int>::max();
struct Vertice{
    id id_;
    peso p = infinito;
    nivel lvl = infinito;
    vector<pair<id, peso>> vecindario;
    int padre_en_T;
};
using grafo = vector<vector<pair<id, peso>>>; // id es el id del vecino, y peso es el peso de la arista que tiene con ese vecino

void camino_vgeodesico_con_menor_peso(grafo &H, id v){
    // Construyo los vertices a partir de una lista de adyacencias con pesos incluidos.
    vector<Vertice> G;
    Vertice w;
    for(int i = 0; i<H.size(); i++){
        w.id_ = i;
        w.vecindario = H[i];
        G.push_back(w);
    }

    // Hago BFS para encontrar elcamio v-geodesico de menor peso para cada vertice.
    queue<id> Q;
    nivel nivel_ = 0;
    G[0].lvl = nivel_;
    G[0].p = 0;
    Q.push(G[0].id_);
    while(!Q.empty()){
        Vertice& u = G[Q.front()];
        for(int j = 0; j<u.vecindario.size(); j++){
            if(G[u.vecindario[j].first].p == infinito){
                Q.push(u.vecindario[j].first);
            }
            if(G[u.vecindario[j].first].p >= u.p + u.vecindario[j].second){
                if(G[u.vecindario[j].first].lvl >= u.lvl + 1){
                    G[u.vecindario[j].first].p = u.p + u.vecindario[j].second;
                    G[u.vecindario[j].first].padre_en_T = u.id_;
                    G[u.vecindario[j].first].lvl = u.lvl + 1;
                }
            }
        }
        Q.pop();
    }

    // Me guardo todos los pesos con los que terminaron los vertices i != v del grafo. Este es
    //el peso del camino v-geodesico de menor peso para el vertice i. Como me guarde ademas el
    //padre de i en dicho camino, accediendo al i de menor peso puedo encontrar mi camino v-geosdesico
    //de menor peso.
    // BFS asegura abarcar todas las aristas que conectan vertices de nivel j con vertices de nivel j+1,
    //para todos los pares de vertices del grafo.
    int menor_peso = infinito;
    int id_menor_peso = -1;
    for(int k = 0; k<G.size(); k++){
        if(menor_peso > G[k].p){
            menor_peso = G[k].p;
            id_menor_peso = k;
        }
    }

    // Como fui guardando y actualizando los padres de cada vertice, puedo desde el id del menos pesado
    //recorrer el abol hasta llegar a v, en O(n).
    int padre = id_menor_peso;
    vector<id> camino;
    camino.push_back(id_menor_peso);
    while(G[padre].id_ != G[0].id_){
        padre = G[padre].padre_en_T;
        camino.push_back(padre);
    }
    cout << "El camino pasa po los vertices: ";
    for(int m = camino.size()-1; m>=0; m--){
        cout << camino[m]<<" ";
    }
};



int main() {
    //vector<vector<pair<id, peso>>>
    grafo entrada = {
            {make_pair(2,3), make_pair(3,5), make_pair(4,1)}, //id 0
            {make_pair(4,11), make_pair(6,21)}, //id 1
            {make_pair(0,3), make_pair(3,-15), make_pair(6,-8)}, //id 2
            {make_pair(0,5), make_pair(2,-15), make_pair(5,-6)}, //id 3
            {make_pair(0,1), make_pair(1,11), make_pair(5,-11)}, //id 4
            {make_pair(3,-6), make_pair(4,-11), make_pair(6,0)}, //id 5
            {make_pair(1,21), make_pair(2,-8), make_pair(5,0)} //id 6
    };
    camino_vgeodesico_con_menor_peso(entrada, 0);
    return 0;
}


/*
            ejemplo 1:
            {make_pair(1,10), make_pair(2,-8)}, //id 0
            {make_pair(0,10), make_pair(2,5), make_pair(3,2), make_pair(4,-4)}, //id 1
            {make_pair(0,-8), make_pair(1,5), make_pair(3,7)}, //id 2
            {make_pair(1,2), make_pair(2,7), make_pair(5,-19)}, //id 3
            {make_pair(1,-4)}, //id 4
            {make_pair(3,-19)} //id 5

            ejemplo 2:
            {make_pair(2,3), make_pair(3,5), make_pair(4,1)}, //id 0
            {make_pair(4,11), make_pair(6,21)}, //id 1
            {make_pair(0,3), make_pair(3,-15), make_pair(6,-8)}, //id 2
            {make_pair(0,5), make_pair(2,-15), make_pair(5,-6)}, //id 3
            {make_pair(0,1), make_pair(1,11), make_pair(5,-11)}, //id 4
            {make_pair(3,-6), make_pair(4,-11), make_pair(6,0)}, //id 5
            {make_pair(1,21), make_pair(2,-8), make_pair(5,0)} //id 6
*/