#include <bits/stdc++.h>

#define rep(i, n) for(int i = 0; i < n; i++)

typedef long long ll;
typedef long double ld;
using namespace std;
int mod = 1000000007;

ld dist(double x1, double y1, double x2, double y2){
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

int main(void){
    int N; cin >> N;
    ld ans = 2000.0;
    int X_int[N], Y_int[N];
    ld X[N], Y[N];
    rep(i, N) cin >> X_int[i] >> Y_int[i];
    rep(i, N){
        X[i] = (ld) X_int[i];
        Y[i] = (ld) Y_int[i];
    }

    //まずは2点を選ぶnC2通りについて考える
    for(int i = 0; i < N; i++){
        for(int j = i+1; j < N; j++){
            ld cx = (X[i]+X[j])/2;
            ld cy = (Y[i]+Y[j])/2;
            ld r = dist(cx, cy, X[j], Y[j]);
            bool ok = true;
            for(int k = 0; k < N; k++){
                if(k == i || k == j) continue;
                if(dist(cx, cy, X[k], Y[k]) > r) ok = false;
            }
            if(ok) ans = min(ans, r);
        }
    }

    //次に3点を選ぶnC3通りについて考える
    for(int i = 0; i < N; i++){
        for(int j = i+1; j < N; j++){
            for(int k = j+1; k < N; k++){
                //三角形は成立するか?
                ld x1, y1, x2, y2, x3, y3;
                x1 = X[i]; y1 = Y[i];
                x2 = X[j]; y2 = Y[j];
                x3 = X[k]; y3 = Y[k];
                //A:(x2-x1, y2-y1)とB:(x3-x1, y3-y1)が平行なら成立しない
                //外積A×Bの大きさはベクトルA,Bのつくる平行四辺形の面積
                //これが0なら平行
                //ただしこれはintで計算したい
                if((X_int[j]-X_int[i])*(Y_int[k]-Y_int[i]) == (X_int[k]-X_int[i])*(Y_int[j]-Y_int[i])){
                    //cout << "parallel: " << X_int[i] << " " << Y_int[i] << " " << X_int[j] << " " << Y_int[j] << " " << X_int[k] << " " << Y_int[k] << endl;
                    continue;
                }
                //外接円の中心,半径を求める
                ld cx, cy, r;
                cy = ((x3-x1)*(x1*x1 + y1*y1 - x2*x2 - y2*y2) - (x2-x1)*(x1*x1 + y1*y1 - x3*x3 - y3*y3))/((x3-x1)*(y1-y2)*2 - (x2-x1)*(y1-y3)*2);
                if(x1 == x2){
                    cx = ((y1-y3)*cy*2 - x1*x1 - y1*y1 + x3*x3 + y3*y3)/((x3-x1)*2);
                }
                else{
                    cx = ((y1-y2)*cy*2 - x1*x1 - y1*y1 + x2*x2 + y2*y2)/((x2-x1)*2);
                }
                r = dist(cx, cy, x3, y3);

                bool ok = true;
                for(int judge = 0; judge < N; judge++){
                    if(judge == i || judge == j || judge == k) continue;
                    if(dist(cx, cy, X[judge], Y[judge]) > r) ok = false;
                }
                if(ok) ans = min(ans, r);
            }
        }
    }
    double res = ans;
    printf("%.10f\n", res);
    return 0;
}