#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int n = 9; //cantidad de dias
vector<vector<float>>Memo(n); //estructura de memoizacion
vector<int> precios = {0,6,3,2,0,9,9,2,9}; //precios por dia
const float Infinito = std::numeric_limits<float>::infinity(); //mi indefinido va a ser el -infinito

float maximaGanancia(vector<int> &p, int d, int a){
    if(a < 0 or a > d){
        return -Infinito;
    }
    if(d == 0){
        return 0;
    }
    if(Memo[d-1][a] == -Infinito){
        float ganancia = max(max(maximaGanancia(p, d-1,a),
                               maximaGanancia(p, d-1, a+1) - precios[n-d]),
                               maximaGanancia(p, d-1, a-1) + precios[n-d]);
        Memo[d-1][a] = ganancia;
    }
    return Memo[d-1][a];
}

int main() {
    //lleno a la estructura Memo de -infinitos
    for(int k = 0; k < n; k++){
        vector<float> v(n/2);
        Memo[k] = v;
    }
    for(int k = 0; k < n; k++){
        vector<float> v(n/2);
        for(int l = 0; l < n/2; l++){
            Memo[k][l] = -Infinito;
        }
    }
    // Para ver si se genero correctamente la estructura Memo:
    float respuesta = maximaGanancia(precios, n,0);

    cout<<"La maxima ganancia es de "<<respuesta<<"\n";
    for(int k = 0; k < n; k++){
        for(int l = 0; l < n/2; l++) {
            cout<<Memo[k][l]<<",";
        }
        cout<<"\n";
    }
    return 0;
}
