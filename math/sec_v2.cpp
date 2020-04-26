#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef complex<double> P;

//最小包含円.不安ならdouble -> long doubleに置換してね

#define EPS (1e-10)
#define rep(i, n) for(int i = 0; i < n; i++)

double dist(P c1, P c2){
    return sqrt((c1.real()-c2.real())*(c1.real()-c2.real()) + (c1.imag()-c2.imag())*(c1.imag()-c2.imag()));
}

double dot(P c1, P c2){
    return c1.real()*c2.real() + c1.imag()*c2.imag();
}

double product(P c1, P c2){
    return c1.real()*c2.imag() - c1.imag()*c2.real();
}

double norm(P c){
    return sqrt(dot(c, c));
}

P intersection(P a1, P a2, P b1, P b2){
    P a = a2-a1, b = b2-b1;
    return a1 + a * (product(b, b1-a1) / product(b, a));
}

bool is_intersected(P a1, P a2, P b1, P b2){
    return ( product(a2-a1, b1-a1) * product(a2-a1, b2-a1) < EPS) && (product(b2-b1, a1-b1) * product(b2-b1, a2-b1) < EPS);
}

//外接円の中心を得る
P circum_coordinate(P a1, P a2, P a3){
    double px, py;
    double x1, y1, x2, y2, x3, y3;
    x1 = a1.real(); y1 = a1.imag();
    x2 = a2.real(); y2 = a2.imag();
    x3 = a3.real(); y3 = a3.imag();

    py = ((x3-x1)*(x1*x1 + y1*y1 - x2*x2 - y2*y2) - (x2-x1)*(x1*x1 + y1*y1 - x3*x3 - y3*y3))/((x3-x1)*(y1-y2)*2.0 - (x2-x1)*(y1-y3)*2.0);
    if(x2-x1 < EPS) px = ((y1-y3)*2.0*py - x1*x1 - y1*y1 + x3*x3 + y3*y3)/((x3-x1)*2.0);
    else px = ((y1-y2)*2.0*py - x1*x1 - y1*y1 + x2*x2 + y2*y2)/((x2-x1)*2.0);
    return P(px, py);
}

int main(void){
    int N; cin >> N;
    double ans = 2000.0;
    P CO[N];
    rep(i, N){
        double x, y; cin >> x >> y;
        CO[i] = P(x, y);
    }
    for(int i = 0; i < N; i++){
        P p1 = CO[i];
        for(int j = i+1; j < N; j++){
            P p2 = CO[j];
            P center = P((p1.real()+p2.real())/2, (p1.imag()+p2.imag())/2);
            double range = dist(p1, p2)/2;
            bool ok = true;

            for(int k = 0; k < N; k++){
                if(k == i || k == j) continue;
                if(dist(CO[k], center) > range + EPS) ok = false;
            }
            if(ok){
                ans = min(ans, range);
            }
        }
    }

    for(int i = 0; i < N; i++){
        P p1 = CO[i];
        for(int j = i+1; j < N; j++){
            P p2 = CO[j];
            for(int k = j+1; k < N; k++){
                P p3 = CO[k];
                //p1, p2, p3が同一直線上(すなわち外積0) -> continue. absを忘れずに
                if(abs(product(p2-p1, p3-p1)) < EPS){
                    continue;
                }
                P center = circum_coordinate(p1, p2, p3); //外接円の中心座標
                double range = dist(center, p3); //外接円の半径
                bool ok = true;
                for(int l = 0; l < N; l++){
                    if(l == i || l == j || l == k) continue;
                    if(dist(CO[l], center) > range) ok = false;
                }
                if(ok) ans = min(ans, range);
            }
        }
    }
    double res = ans;
    printf("%.10f\n", res);
}