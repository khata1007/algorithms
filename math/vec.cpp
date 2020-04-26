//幾何ライブラリ 不安ならdouble -> long doubleに置換

#include <bits/stdc++.h>

using namespace std;

typedef complex<double> P;

#define EPS (1e-10)

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