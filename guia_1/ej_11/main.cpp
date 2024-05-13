#include <iostream>
#include <math.h>
#include <vector>
#include <limits>

using namespace std;

int menosInfinito = numeric_limits<int>::min();
int Infinito = numeric_limits<int>::max();
vector<vector<int>> memo;
vector<vector<int>> vfinal;

int N = 50;
vector<int> v = {2,1,2,4,5,2,1,2,2,1,1};

bool esPosible(int i, int c, vector<int> vparcial){
    if(c > N or i >= v.size() or (c != N and i == v.size()-1)){
        return 0;
    }
    if(c == N and i == v.size()-1){
        vfinal.push_back(vparcial);
        return 1;
    }
    if(memo[i][c] == -1){
        vparcial.push_back(0);
        int camino_mult = esPosible(i+1, c*v[i+1], vparcial);
        vparcial.pop_back();

        vparcial.push_back(1);
        int camino_suma = esPosible(i+1, c+v[i+1], vparcial);
        vparcial.pop_back();

        vparcial.push_back(2);
        int camino_pote = esPosible(i+1, pow(c, v[i+1]), vparcial);
        vparcial.pop_back();

        memo[i][c] = (camino_mult > 0 or camino_suma > 0 or camino_pote > 0);
    }
    return memo[i][c];
}

int main() {
    memo = vector<vector<int>>(v.size()+1, vector<int>(N+1, -1));
    vector<int> vparcial = {};
    bool respuesta = esPosible(0, v[0], vparcial);
    if(respuesta == false){
        cout<<"No es posible."<<"\n";
    }else{
        cout<<"Es posible."<<"\n";
    }
    cout<< "La estructura de memoizacion quedo tal que asi: "<<"\n";
    for(int i = 0; i<memo.size();i++){
        for(int j = 0; j<memo[0].size();j++){
            cout<<memo[i][j]<< ", ";
        }
        cout<<"\n";
    }
    cout<< "Las soluciones halladas por el algoritmo de programacion dinamica fueron: "<<"\n";
    for(int i = 0; i<vfinal.size();i++){
        for(int j = 0; j<vfinal[i].size();j++){
            cout<<vfinal[i][j]<< ", ";
        }
        cout<<"\n";
    }
    return 0;
}
