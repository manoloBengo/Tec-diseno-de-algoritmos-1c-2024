#include <iostream>
#include <vector>

using namespace std;

using vertice = int;
using arista = pair<vertice,vertice>;
struct Arista{
    int id;
    vertice first;
    vertice second;
    bool estaEnCiclo = false;
};
using grafo = vector<vector<vertice>>;

grafo construir_lista_de_adyacencias(vector<arista> aristas, int n){
    vector<vector<vertice>> lista = vector<vector<vertice>>(n, vector<vertice>(0));
    vertice u;
    vertice v;
    for(int i = 0; i<aristas.size(); i++){
        u = aristas[i].first;
        v = aristas[i].second;
        lista[u].push_back(v);
        lista[v].push_back(u);
    }
    return lista;
}

vector<Arista> construir_Aristas(vector<arista> e){
    vector<Arista> a;
    for(int i = 0; i<e.size(); i++){
        Arista u;
        u.id = i;
        u.first = e[i].first;
        u.second = e[i].second;
        a.push_back(u);
    }
    return a;
}

bool esCactus(grafo G, vector<Arista> aristas_con_bool ,int n){

}

int main() {
    vector<arista> E = {make_pair(0,1),
                        make_pair(0,3),
                        make_pair(1,4),
                        make_pair(2,3),
                        make_pair(2,4),
                        make_pair(3,4)};
    int n = 5;
    // Genero el grafo G como lista de adyacaencias, y guardo en aristas_con_bool
    //el id y bool "estaEnCiclo" de cada arista, en la posicion correspondiente al id.
    grafo G = construir_lista_de_adyacencias(E, n);
    vector<Arista> aristas_con_bool = construir_Aristas(E);
    bool rta = esCactus(G, aristas_con_bool, 5);
    return 0;
}
