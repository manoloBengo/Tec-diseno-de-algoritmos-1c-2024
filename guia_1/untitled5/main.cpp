#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

const float infinity = numeric_limits<float>::infinity();
vector<vector<pair<float, float>>> top_down_memo;

pair<float, float> cc_backtracking(vector<int> &B, int i, int j) {
    if (i < 0 && j > 0) {
        return {infinity, infinity};
    } else if (j <= 0) {
        return {0, 0};
    } else {
        pair<float, float> r = cc_backtracking(B, i - 1, j - B[i]);
        return min(
                {B[i] + r.first, 1.0 + r.second},
                cc_backtracking(B, i - 1, j)
        );
    }
}

int main(int argc, char *argv[]) {
    vector<int> B = {3,8,5,1};
    int c = 10;
    pair<float,float> result = cc_backtracking(B, B.size(), c);
    cout<<result.first<<", "<<result.second;
    return 0;
}