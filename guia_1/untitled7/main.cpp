#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> mem1;
vector<vector<int>> mem2;
int m;

struct Skyscraper {
    int height;
    int length;
};
bool esMenor(int a, int c){
    return a<c;
}

bool esMayor(int a, int c){
    return a>c;
}

int sumSubsecCreciente(vector<Skyscraper> &skyline, int h,int j,vector<vector<int>> &mem1){
    if(j==skyline.size()-1){
        if(h<skyline[j].height){
            return skyline[j].length;
        }else{
            return 0;
        }
    }
    if(mem1[h][j]==-1){
        if(esMayor(skyline[j].height,h)){
            mem1[h][j]=max(sumSubsecCreciente(skyline,skyline[j].height,j+1,mem1) + skyline[j].length,
                           sumSubsecCreciente(skyline,h,j+1,mem1));
        }else{
            mem1[h][j]=sumSubsecCreciente(skyline,h,j+1,mem1);
        }
    }
    return mem1[h][j];
}

int sumSubsecDecreciente(vector<Skyscraper> &skyline, int h,int j,vector<vector<int>> &mem2){
    if(j==skyline.size()-1){
        if(h>skyline[j].height){
            return skyline[j].length;
        }else{
            return 0;
        }
    }
    if(mem2[h][j]==-1){
        if(esMenor(skyline[j].height,h)){
            mem2[h][j]=max(sumSubsecDecreciente(skyline,skyline[j].height,j+1,mem2) + skyline[j].length,
                           sumSubsecDecreciente(skyline,h,j+1,mem2));
        }else{
            mem2[h][j]=sumSubsecDecreciente(skyline,h,j+1,mem2);
        }
    }
    return mem2[h][j];
}

int maximo(vector<Skyscraper> skyline){
    int m=0;
    for(int i=0;i<skyline.size();i++){
        if(skyline[i].height>m){
            m=skyline[i].height;
        }
    }
    return m;
}

int main(){
    int T;
    cin>> T;
    vector<vector<Skyscraper>> r;
    for(int i=0;i<T;i++){
        int N;
        cin >> N;
        vector<Skyscraper> skyline(N);
        for(int j=0; j<N; j++) {
            cin >> skyline[j].height;
        }
        for(int k=0; k<N;k++){
            cin>>skyline[k].length;
        }
        r.push_back(skyline);
        m = maximo(skyline)+1;
        mem1 = vector<vector<int>>(m, vector<int>(N+1, -1));
        mem2 = vector<vector<int>>(m+1, vector<int>(N+1, -1));
        int c=sumSubsecCreciente(r[i],0,0,mem1);
        int d=sumSubsecDecreciente(r[i],m,0,mem2);
        cout<< "Case " << i+1 << ". ";
        if(c>=d){
            cout<< "Increasing ("<<c<<")"<<". "<< "Decreasing ("<<d<<")"<<"."<<"\n";
        }else{
            cout<< "Decreasing ("<<d<<")"<<". "<<"Increasing ("<<c<<")"<<"."<<"\n";
        }
    }
    return 0;
}

