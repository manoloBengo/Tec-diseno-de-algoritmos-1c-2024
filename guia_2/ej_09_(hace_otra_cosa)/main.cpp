#include <iostream>
#include <vector>

using namespace std;

int indice = 0;

int iesimo_merge(vector<int> &A, vector<int> &B, int a0, int af, int b0, int bf, int &e){
    if(af-a0 == 0 and bf-b0 == 0){
        return 0;
    }

    int am = a0 + ((af-a0)/2);
    int bm = b0 + ((bf-b0)/2);

    if(A[am] == e){
        indice = indice + am - a0;
        af = a0;
    }
    if(B[bm] == e){
        indice = indice + bm - b0;
        bf = b0;
    }

    int nuevo_a0 = a0;
    int nuevo_af = af;
    int nuevo_b0 = b0;
    int nuevo_bf = bf;

    if(B[bm] > e){
        nuevo_b0 = b0;
        nuevo_bf = bm;
    }
    if(B[bm] < e){
        nuevo_b0 = bm + 1;
        nuevo_bf = bf;
        indice = indice + 1 + bm - b0;
    }
    if(A[am] > e){
        nuevo_a0 = a0;
        nuevo_af = am;
    }
    if(A[am] < e){
        nuevo_a0 = am + 1;
        nuevo_af = af;
        indice = indice + 1 + am - a0;
    }

    iesimo_merge(A,B,nuevo_a0,nuevo_af,nuevo_b0,nuevo_bf,e);

    return 0;
}

int main() {
    vector<int> A = {1,5,6,9,10,14};
    vector<int> B = {3,8,11,12,19,21};
    int e = 13;
    iesimo_merge(A,B,0,A.size()-1,0,B.size()-1,e);
    cout << indice;
    return 0;
    //FUNCIONA!!!!
    //T(n)
}
