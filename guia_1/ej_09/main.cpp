#include <iostream>
#include <math.h>
#include <vector>
#include <limits>

using namespace std;

int m = 3;
int n = 3;
vector<vector<int>> A = {
        {-2,  -3,  3},
        {-5, -10,  1},
        {10,  30, -5},
};

vector<vector<int>> memo(m, vector<int>(n, -1));

int travesiaVital(int i, int j) {
    if(i==m and j ==n){
        return 1;
    }
    if(i>m-1 or j>n-1){
        return numeric_limits<int>::max();
    }
    if(memo[i][j] == -1){
        memo[i][j] = max(1, min(travesiaVital(i+1,j), travesiaVital(i,j+1)) - A[i][j]);
    }
    return memo[i][j];
}

int main() {
    int res = travesiaVital(0, 0);
    printf("solution: %d\n", res);
    return 0;
}
