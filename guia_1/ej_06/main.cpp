#include <iostream>
#include <limits>
#include <vector>

using namespace std;

const float Infinito = std::numeric_limits<float>::infinity();
int c = 491;
vector<int> B = {5,50,10,10,1,1,1,20,1,1,1,1,200,200,55,73,500,500,5,5,5,1,1,1,1,56,34,24,2342,42,222};
vector<vector<pair<float,float>>> M(c);


pair<float,float> optiPago_backtracking(vector<int> &B, int i, int j){
    if(i < 0 and j > 0){
        return {Infinito, Infinito};
    }
    if(j <= 0){
        return {0,0};
    }
    pair<float,float> result = optiPago_backtracking(B, i-1, j-B[i]);
    return min({B[i] + result.first, 1.0 + result.second},
                  optiPago_backtracking(B, i-1, j));
}

pair<float,float> optiPago_topDown(vector<int> &B, int i, int j){
    if(i <= 0 and j > 0){
        return {Infinito, Infinito};
    }else{
        if(j <= 0){
            return {0,0};
        }
    }
    if(M[i-1][j].first == -1){
        pair<float,float> nuevo_par = optiPago_topDown(B, i-1, j-B[i-1]);
        M[i-1][j] = min(
                {B[i-1] + nuevo_par.first, 1.0 + nuevo_par.second},
                optiPago_topDown(B, i-1, j));
    }
    return M[i-1][j];

}



int main() {
    //inicializo la matriz M con todos valores infinitos.
    M = vector<vector<pair<float,float>>>(
            c + 1,
            vector<pair<float, float>>(c + 1, {-1, -1})
            );
    for(int k = 0; k < B.size(); k++){
        for(int l = 0; l < c; l++){
            M[k][l] = {-1, -1};
        }
    }
    // Para ir viendo la matriz M:
    /*
    for(int k = 0; k < B.size(); k++){
        for(int l = 0; l < c; l++) {
            cout<<M[k][l].first<<",";
        }
        cout<<"\n";
    }
     */
    pair<int,int> respuesta = optiPago_topDown(B, B.size(), c);
    cout << respuesta.first << "," << respuesta.second;

    return 0;
}
