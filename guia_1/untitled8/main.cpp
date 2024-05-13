#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int menosInfinito = numeric_limits<int>::min();
int Infinito = numeric_limits<int>::max();

int murciaAsc(int i, int h, int &N, vector<int> &alturas, vector<int> &anchos, vector<vector<int>> &memo){
    if(i>=N){
        return 0;
    }
    if(memo[i][h] == -1){
        int max1;
        if(alturas[i] <= h){
            max1 = menosInfinito;
        }else{
            max1 = murciaAsc(i+1, alturas[i], N, alturas, anchos, memo) + anchos[i];
        }
        int max2 = murciaAsc(i+1, h, N, alturas, anchos, memo);
        int maximo = max(max1, max2);
        memo[i][h] = maximo;
    }
    return memo[i][h];
}

int murciaDes(int i, int h, int &N, vector<int> &alturas, vector<int> &anchos, vector<vector<int>> &memo){
    if(i<0){
        return 0;
    }
    if(memo[i][h] == -1){
        int max1;
        if(alturas[i] <= h){
            max1 = menosInfinito;
        }else{
            max1 = murciaDes(i-1, alturas[i], N, alturas, anchos, memo) + anchos[i];
        }
        int max2 =  murciaDes(i-1, h, N, alturas, anchos, memo);
        int maximo = max(max1, max2);
        memo[i][h] = maximo;
    }
    return memo[i][h];
}

int maximo(vector<int> v){
    int maximo = menosInfinito;
    for(int i = 0; i < v.size(); i++){
        if(v[i] > maximo){
            maximo = v[i];
        }
    }
    return maximo;
}

int main() {
    int test_cases;
    cin>>test_cases;
    for(int caso = 0; caso < test_cases; caso++){
        int cant_edificios;
        cin>>cant_edificios;
        vector<int> alturas(cant_edificios);
        vector<int> anchos(cant_edificios);
        for(int i = 0; i < cant_edificios; i++){
            cin >> alturas[i];
        }
        for(int j = 0; j < cant_edificios; j++){
            cin >> anchos[j];
        }

        int ascendente;
        int descendente;

        vector<vector<int>> memo;
        int max_altura = maximo(alturas);

        memo = vector<vector<int>>(cant_edificios, vector<int>(max_altura + 1, -1));
        ascendente = murciaAsc(0, 0, cant_edificios, alturas, anchos, memo);

        memo = vector<vector<int>>(cant_edificios, vector<int>(max_altura + 1, -1));
        descendente =  murciaDes(cant_edificios-1, 0, cant_edificios, alturas, anchos, memo);
        cout << "Case "<< caso + 1 <<". ";
        if(ascendente >= descendente){
            cout << "Increasing ("<< ascendente << "). Decreasing ("<< descendente << ")."<< "\n";
        }else{
            cout << "Decreasing ("<< descendente << "). Increasing ("<< ascendente << ")."<< "\n";
        }
    }
    return 0;
}
