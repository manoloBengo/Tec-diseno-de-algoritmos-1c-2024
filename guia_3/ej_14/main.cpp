#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <cmath>

using namespace std;

struct Vertice{ // Vertice con atributos: vecindarios in and out, marca, cantidad de hijos.
    int id;
    vector<int> d_in;
    vector<int> d_out;
    int padre;
    int cant_hijos; // Va llevando la cuenta de cuantos hijos no estan marcados con un -1 o un 5.
    int marca = 0;
};

using grafo = vector<Vertice>; // Los IDs de los vertices van de 0 a n-1, para facilitar indexacion.

vector<int> not_cycle;
vector<int> cycle;
bool cazador_de_ciclos(grafo &G){  // grafo como lista de adyacencias.
    stack<int> S; // Solo pusheo ids
    G[0].marca = 1;
    if(G[0].d_in.size() > 0){
        G[0].padre = G[0].d_in[0];
    }else{
        G[0].padre = -1;
    }
    S.push(G[0].id);
    while(!S.empty()){
        int u = S.top();
        G[u].marca = 1;
        //S.pop();



        if(G[u].cant_hijos == 0){
            G[u].marca = -1;
            if(G[u].padre != -1){
                G[G[u].padre].cant_hijos --;
            }
            not_cycle.push_back(G[u].id);
            S.pop();
        }else{
            for(int i = 0; i<G[u].d_out.size(); i++){
                if(G[G[u].d_out[i]].marca != 5){
                    G[G[u].d_out[i]].padre = G[u].id; // Le asigno el padre al vertice.
                    if(G[G[u].d_out[i]].marca == 1){ // Si en algun momento me encuentro con que el vertice u tiene un
                                                     //vecino(out) con la marca 1, entonces hay un ciclo.
                        int id_cabeza_del_ciclo = G[G[u].d_out[i]].id;
                        cycle.push_back(G[G[u].d_out[i]].id);
                        while(id_cabeza_del_ciclo != S.top()){
                            if(G[S.top()].marca == 1){
                                cycle.push_back(S.top());
                            }
                            S.pop();
                        }
                        cycle.push_back(G[G[u].d_out[i]].id);
                        return true; // Si en algun momento me encuentro con que el vertice u tiene un
                        //vecino(out) con la marca 1, entonces hay un ciclo.
                    }
                    G[G[u].d_out[i]].marca = 5; // La marca 5 es para los que estan en la pila pero no fueron analizados.
                    S.push(G[u].d_out[i]); // Agrego a la pila solamente si el vertice no esta marcado con -1.

                }else{
                    G[u].cant_hijos--;
                }
            }
        }
    }
    return false; // Si ya no hay elementos en la pila, no hay ciclo.
}

//ATENCION. El algoritmo funciona asumiendo que arrancamos en un vertice con d_in = 0, o en un vertice que forma parte de un ciclo.

int main() {
    grafo g;
    // v.padre == -2 es para que arranquen sin padre.
    Vertice u; u.id = 0; u.marca = 0; u.d_out = {2,3}; u.d_in = {1}; u.cant_hijos = 2; u.padre = -2; g.push_back(u);
    Vertice v; v.id = 1; v.marca = 0; v.d_out = {0}; v.d_in = {4}; v.cant_hijos = 1; v.padre = -2; g.push_back(v);
    Vertice w; w.id = 2; w.marca = 0; w.d_out = {}; w.d_in = {0,3,4}; w.cant_hijos = 0; w.padre = -2; g.push_back(w);
    Vertice x; x.id = 3; x.marca = 0; x.d_out = {2,4}; x.d_in = {0}; x.cant_hijos = 2; x.padre = -2; g.push_back(x);
    Vertice y; y.id = 4; y.marca = 0; y.d_out = {1,2}; y.d_in = {3}; y.cant_hijos = 2; y.padre = -2; g.push_back(y);

    // Aristas (dirigidas de izq. a der.): uv, vw, vx, xu, correspondientes a los ids 0-1, 1-2, 1-3, 3-2, 3-4, 4-2, 4-0. Hay un ciclo.
    bool rta = cazador_de_ciclos(g);
    if(rta){
        cout <<"Hay ciclos, por ejemplo: "<<"\n";
        for(int k = cycle.size()-1; k>=0; k--){
            cout << cycle[k] << " ";
        }
    }else{
        cout <<"No hay ciclos."<<"\n";
    }
    return 0;
}

/*TESTING 1:
    Vertice u; u.id = 0; u.marca = 0; u.d_out = {1}; u.d_in = {}; u.cant_hijos = 1; u.padre = -2; g.push_back(u);
    Vertice v; v.id = 1; v.marca = 0; v.d_out = {2,3}; v.d_in = {0}; v.cant_hijos = 2; v.padre = -2; g.push_back(v);
    Vertice w; w.id = 2; w.marca = 0; w.d_out = {}; w.d_in = {1,3}; w.cant_hijos = 0; w.padre = -2; g.push_back(w);
    Vertice x; x.id = 3; x.marca = 0; x.d_out = {2}; x.d_in = {1}; x.cant_hijos = 1; x.padre = -2; g.push_back(x);
    // Aristas (dirigidas de izq. a der.): uv, vw, vx, xu, correspondientes a los ids 0-1, 1-2, 1-3, 3-2. No hay un ciclo.
*/
/*TESTING 2:
    Vertice u; u.id = 0; u.marca = 0; u.d_out = {1}; u.d_in = {}; u.cant_hijos = 1; u.padre = -2; g.push_back(u);
    Vertice v; v.id = 1; v.marca = 0; v.d_out = {2,3}; v.d_in = {0}; v.cant_hijos = 2; v.padre = -2; g.push_back(v);
    Vertice w; w.id = 2; w.marca = 0; w.d_out = {}; w.d_in = {1,3}; w.cant_hijos = 0; w.padre = -2; g.push_back(w);
    Vertice x; x.id = 3; x.marca = 0; x.d_out = {2}; x.d_in = {1}; x.cant_hijos = 1; x.padre = -2; g.push_back(x);
    Vertice y; y.id = 4; y.marca = 0; y.d_out = {0,2}; y.d_in = {3}; y.cant_hijos = 2; y.padre = -2; g.push_back(y);
    // Aristas (dirigidas de izq. a der.): uv, vw, vx, xu, correspondientes a los ids 0-1, 1-2, 1-3, 3-2, 3-4, 4-2, 4-0. Hay un ciclo.
*/