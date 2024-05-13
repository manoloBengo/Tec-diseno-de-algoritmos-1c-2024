#include <iostream>
#include <math.h>
#include <vector>
#include <limits>

using namespace std;

vector<int> w = {6, 3, 2, 1};
vector<int> s = {10, 3, 1, 2};
int menosInfinito = numeric_limits<int>::min();
int Infinito = numeric_limits<int>::max();
vector<vector<int>> memo;

int pilaCauta(vector<int> &w, vector<int> &s, int i, int k) {
    if (i == -1) return 0;
    if (k > s[i]) return pilaCauta(w, s, i - 1, k);
    if (memo[i][k] == -1) {
        memo[i][k] = max(
                pilaCauta(w, s, i - 1, k + w[i]) + 1,
                pilaCauta(w, s, i - 1, k)
        );
    }
    return memo[i][k];
}
int main() {
    int max_w = 0;
    for (int i = 0; i < w.size(); i++) {
        max_w += w[i];
    }
    memo = vector<vector<int>>(w.size(), vector<int>(max_w, -1));

    cout << pilaCauta(w, s, w.size() - 1, 0);
    return 0;
}
