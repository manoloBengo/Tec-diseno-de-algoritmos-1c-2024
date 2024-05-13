#include <iostream>
#include <math.h>
#include <vector>
#include <limits>

using namespace std;

int menosInfinito = numeric_limits<int>::min();
int Infinito = numeric_limits<int>::max();
vector<vector<int>> memo_a;
vector<vector<vector<int>>> memo_b;

int n = 3;
int s = 14;
int k = 6;


int dados_distinguibles(int n, int s){
    if((s > 0 and n == 0 ) or (s < 0)){
        return 0;
    }
    if(s == 0 and n == 0){
        return 1;
    }
    if(memo_a[n][s] == -1){
        int suma = 0;
        for(int l = 1; l<=k; l++){
            suma = suma + dados_distinguibles(n-1, s-l);
        }
        memo_a[n][s] = suma;
    }
    return memo_a[n][s];
}

int dados_indistinguibles(int n, int s, int k){
    if((s > 0 and n == 0 ) or (s < 0) or (k*n < s)){
        return 0;
    }
    if((s == 0 and n == 0) or (k == n and s == 0)){
        return 1;
    }
    if(memo_b[n][s][k] == -1){
        int suma = 0;
        for(int l = 1; l<=k; l++){
            suma = suma + dados_indistinguibles(n-1, s-l, l);
        }
        memo_b[n][s][k] = suma;
    }
    return memo_b[n][s][k];
}

int main() {
    memo_a = vector<vector<int>>(n+1, vector<int>(s+1, -1));
    memo_b = vector<vector<vector<int>>>(n+1, vector<vector<int>>(s+1, vector<int>(k+1, -1)));
    int respuesta_distinguibles = dados_distinguibles(n,s);
    int respuesta_indistinguibles = dados_indistinguibles(n,s,k);
    cout<<"La cantidad de posibilidades para dados distinguibles es: "<<respuesta_distinguibles<<"\n";
    cout<<"La cantidad de posibilidades para dados indistinguibles es: "<<respuesta_indistinguibles;
    return 0;
}
