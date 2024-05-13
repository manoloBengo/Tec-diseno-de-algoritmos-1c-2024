#include <iostream>
#include <limits>
#include <vector>

using namespace std;

const float Infinito = std::numeric_limits<float>::infinity();
int c = 10;
vector<int> B = {5,2,6,6};
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

pair<float, float> optiPago_bottomUp(vector<int> &B, int n, int c) {
    vector<vector<pair<float, float>>> Memo(
            n + 1,
            vector<pair<float, float>>(c + 1, {Infinito, Infinito})
    );
    Memo[0][0] = {0, 0};

    for (int i = 1; i <= n; i++) {
        for (int j = c; j >= 0; j--) {



            pair<float, float> r = Memo[i - 1][max(0, j - B[i])];
            Memo[i][j] = min(
                    {B[i] + r.first, 1.0 + r.second},
                    Memo[i - 1][j]
            );
        }
    }

    return Memo[n][c];
}



int main() {
    //inicializo la matriz M con todos valores infinitos.
    M = vector<vector<pair<float,float>>>(
            c + 1,
            vector<pair<float, float>>(c + 1, {-1, -1})
    );
    for(int k = 0; k <= B.size(); k++){
        for(int l = 0; l <= c; l++){
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
    pair<int,int> respuesta = optiPago_bottomUp(B, B.size(), c);
    cout << respuesta.first << "," << respuesta.second;

    return 0;
}

