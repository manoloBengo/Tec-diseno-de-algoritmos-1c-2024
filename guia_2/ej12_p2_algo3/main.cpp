#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<vector<int>> tablero;
int n;
pair<int,int> la_ocupada;
vector<int> numeros_disponibles;

void distribuir_en_tablero_dc(int i0, int i1, int j0, int j1, pair<int,int> c){
    // Las variables i0,i1,j0,j1 determinan los limites.
    // La variable c es la casilla ocupada del tablero.

    // Casos base.
    if(i1-i0 == 1 and j1-j0 == 1){
        for(int k=i0; k<=i1;k++){
            for(int l=j0; l<=j1; l++){
                if((k != c.first or l != c.second) and tablero[k][l] == -1){
                    tablero[k][l] = numeros_disponibles.back();
                }
            }
        }
        numeros_disponibles.pop_back();
        return;
    }

    // Empezamos a definir variables para el paso recursivo.
    vector<int> cuadrante_ocupado = {0,0,0,0};
    pair<int,int> par_ = make_pair(-1,-1);
    vector<pair<int,int>> casillas_ocupadas(4);
    casillas_ocupadas = {par_,par_,par_,par_};

    // Veo donde esta la casilla ocupada
    int mid_i = i0+((i1-i0)/2);
    int mid_j = j0+((j1-j0)/2);
    if(c.first <= mid_i){
        if(c.second <= mid_j){
            cuadrante_ocupado[0] = 1;

            casillas_ocupadas[0] = c;
            casillas_ocupadas[1] = make_pair(mid_i,mid_j+1);
            casillas_ocupadas[2] = make_pair(mid_i+1,mid_j);
            casillas_ocupadas[3] = make_pair(mid_i+1,mid_j+1);

            tablero[mid_i][mid_j+1] = numeros_disponibles.back();
            tablero[mid_i+1][mid_j] = numeros_disponibles.back();
            tablero[mid_i+1][mid_j+1] = numeros_disponibles.back();
            numeros_disponibles.pop_back();
        }else{
            cuadrante_ocupado[1] = 1;

            casillas_ocupadas[0] = make_pair(mid_i,mid_j);
            casillas_ocupadas[1] = c;
            casillas_ocupadas[2] = make_pair(mid_i+1,mid_j);
            casillas_ocupadas[3] = make_pair(mid_i+1,mid_j+1);

            tablero[mid_i][mid_j] = numeros_disponibles.back();
            tablero[mid_i+1][mid_j] = numeros_disponibles.back();
            tablero[mid_i+1][mid_j+1] = numeros_disponibles.back();
            numeros_disponibles.pop_back();
        }
    }else{
        if(c.second <= mid_j){
            cuadrante_ocupado[2] = 1;

            casillas_ocupadas[0] = make_pair(mid_i,mid_j);
            casillas_ocupadas[1] = make_pair(mid_i,mid_j+1);
            casillas_ocupadas[2] = c;
            casillas_ocupadas[3] = make_pair(mid_i+1,mid_j+1);

            tablero[mid_i][mid_j] = numeros_disponibles.back();
            tablero[mid_i][mid_j+1] = numeros_disponibles.back();
            tablero[mid_i+1][mid_j+1] = numeros_disponibles.back();
            numeros_disponibles.pop_back();
        }else{
            cuadrante_ocupado[3] = 1;

            casillas_ocupadas[0] = make_pair(mid_i,mid_j);
            casillas_ocupadas[1] = make_pair(mid_i,mid_j+1);
            casillas_ocupadas[2] = make_pair(mid_i+1,mid_j);
            casillas_ocupadas[3] = c;

            tablero[mid_i][mid_j] = numeros_disponibles.back();
            tablero[mid_i][mid_j+1] = numeros_disponibles.back();
            tablero[mid_i+1][mid_j] = numeros_disponibles.back();
            numeros_disponibles.pop_back();
        }
    }

    distribuir_en_tablero_dc(i0,mid_i,j0,mid_j,casillas_ocupadas[0]);
    distribuir_en_tablero_dc(i0,mid_i,mid_j+1,j1,casillas_ocupadas[1]);
    distribuir_en_tablero_dc(mid_i+1,i1,j0,mid_j,casillas_ocupadas[2]);
    distribuir_en_tablero_dc(mid_i+1,i1,mid_j+1,j1,casillas_ocupadas[3]);

    return;
}

int main() {
    n = 16;
    la_ocupada = make_pair(10,9);
    tablero = vector<vector<int>>(n, vector<int>(n, -1));
    tablero[la_ocupada.first][la_ocupada.second] = 0;
    int cant_num = n*n;
    for(int i = 10; i<=cant_num; i++){
        numeros_disponibles.push_back(i);
    }
    distribuir_en_tablero_dc(0,n-1,0,n-1, la_ocupada);

    for(int k=0; k<n;k++) {
        for (int l = 0; l<n; l++) {
            cout << tablero[k][l]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}
