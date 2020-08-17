#include<bits/stdc++.h>

using namespace std;

vector<complex<double>> fft(vector<complex<double>> a, bool inv = false){
    int N = a.size();
    int sgn = (inv) ? -1 : 1;
    if(N == 1) return a;

    //f に偶数次の係数, g に奇数次の係数を格納
    vector<complex<double>> f(N/2), g(N/2);
    for(int i = 0; i < (N >> 1); i++){
        f[i] = a[(i << 1) + 0];
        g[i] = a[(i << 1) + 1];
    }

    f = fft(f, inv);
    g = fft(g, inv);

    //複素数体上の乗法単位元の原子根 zeta を用意
    complex<double> zeta(cos(2.0 * M_PI / N), sin(2.0 * M_PI / N) * sgn);
    complex<double> pow_zeta = 1;

    for(int i = 0; i < N; i++){
        a[i] = f[i % (N >> 1)] + pow_zeta * g[i % (N >> 1)];
        pow_zeta *= zeta;
    }
    return a;
}

vector<complex<double>> fft(vector<double> a, bool inv = false){
    vector<complex<double>> a_complex(a.size());
    for(int i = 0; i < a.size(); i++) a_complex[i] = complex<double>(a[i], 0);
    return fft(a_complex, inv);
}

vector<complex<double>> inv_fft(vector<complex<double>> a){
    int N = a.size();
    a = fft(a, true);
    for(int i = 0; i < N; i++){
        a[i] /= N;
    }
    return a;
}

vector<double> convolve(vector<double> a, vector<double> b){
    int s = a.size() + b.size() - 1; //(a-1次) * (b-1次) に必要なサイズは (a-1) + (b-1) + 1 = a+b-1
    int t = 1;
    while(t < s) t <<= 1;
    a.resize(t, 0);
    b.resize(t, 0);
    vector<complex<double>> A = fft(a);
    vector<complex<double>> B = fft(b);
    for(int i = 0; i < t; i++){
        A[i] *= B[i];
    }
    for(int i = 0; i < t; i++) cout << A[i] << " "; cout << endl;
    A = inv_fft(A);
    a.resize(s);
    for(int i = 0; i < s; i++) a[i] = A[i].real();
    return a;
}

int main(void){
    /*
    int N, M; cin >> N >> M;
    vector<double> A(N), B(M);
    for(int i = 0; i < N; i++) cin >> A[i];
    for(int i = 0; i < M; i++) cin >> B[i];

    //-----------畳み込みのverify------------//
    vector<double> C;
    C = convolve(A, B);
    for(int i = 0; i < C.size(); i++) cout << C[i] << " "; cout << endl;

    //-----------fftのverify-------------//
    //vector<complex<double>> C;
    //C = inv_fft(fft(A));
    //for(int i = 0; i < C.size(); i++) cout << C[i].real() << " "; cout << endl;
    return 0;
    */
    
}