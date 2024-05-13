#include <iostream>
#include <vector>

using namespace std;

int parejas_golosas(vector<int> a, vector<int> b){
    int cont_a = 0; int cont_b = 0; int parejas = 0;
    while(cont_a < a.size() and cont_b < b.size()){
        if(a[cont_a]-b[cont_b] <= 1 and a[cont_a]-b[cont_b] >= -1){
            parejas++; cont_a++; cont_b++;
        }else{
            if(a[cont_a] < b[cont_b]){
                cont_a++;
            }else{
                cont_b++;
            }
        }
    }
    return parejas;
}

int main() {
    vector<int> a = {1,1,1,3,6,6,7,9,10,11,14,16,16,19};
    vector<int> b = {2,3,3,5,5,5,11,15,15,17,22,23};
    int respuesta = parejas_golosas(a,b);
    cout << respuesta;
    return 0;
}
