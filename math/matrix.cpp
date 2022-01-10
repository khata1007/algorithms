#include<bits/stdc++.h>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; i++)

typedef long long ll;

template <class T>
struct Matrix{
    vector<vector<T>> A;

    //----------コンストラクタ----------//
    Matrix(){}
    Matrix(size_t n, size_t m) : A(n, vector<T>(m, 0)) {} //n行m列
    Matrix(size_t n) : A(n, vector<T>(n, 0)) {}; //n行n列

    size_t height() const {return A.size();}
    size_t width() const {return A[0].size();}

    //添え字アクセスで行を返す. 普通に使う分には下の方が呼ばれる
    inline const vector<T>& operator[](int k) const {return A.at(k);}
    inline       vector<T>& operator[](int k)       {return A.at(k);} //const関数にすると怒られる. なぜ?

    // +=, -=, *=,
    Matrix& operator +=(const Matrix& B){
        size_t h = height(), w = width();
        assert(h == B.height() && w == B.width());
        for(int i = 0; i < h; i++)
            for(int j = 0; j < w; j++)
                (*this)[i][j] += B[i][j];
        return *this;
    }
    Matrix& operator -=(const Matrix& B){
        size_t h = height(), w = width();
        assert(h == B.height() && w == B.width());
        for(int i = 0; i < h; i++)
            for(int j = 0; j < w; j++)
                (*this)[i][j] -= B[i][j];
        return *this;
    }
    Matrix& operator *=(const Matrix& B){
        size_t n = height(), m = B.width(), p = width();
        assert(p == B.height());
        vector<vector<T>> C(n, vector<T>(m, 0));
        for(int i = 0; i < n; i++)
            for(int k = 0; k < p; k++)
                for(int j = 0; j < m; j++)
                    C[i][j] += A[i][k]*B[k][j];
        A.swap(C);
        return (*this);
    }
    Matrix& modmul (const Matrix& B, const long long md){
        size_t n = height(), m = B.width(), p = width();
        assert(p == B.height());
        vector<vector<T>> C(n, vector<T>(m, 0));
        for(int i = 0; i < n; i++)
            for(int k = 0; k < p; k++)
                for(int j = 0; j < m; j++)
                    (C[i][j] += A[i][k]*B[k][j]) %= md;
        A.swap(C);
        return (*this);
    }

    // +, -, *, pow
    Matrix operator +(const Matrix& B) {return (Matrix(*this) += B);}
    Matrix operator -(const Matrix& B) {return (Matrix(*this) -= B);}
    Matrix operator *(const Matrix& B) {return (Matrix(*this) *= B);}

    Matrix pow(long long k){
        Matrix B = Matrix::I(height());
        Matrix work = Matrix(*this);
        while(k > 0){
            if(k&1) B *= work;
            work *= work;
            k >>= 1LL;
        }
        return B;
    }

    Matrix modpow(long long k, long long m){
        Matrix B = Matrix::I(height());
        Matrix work = Matrix(*this);
        while(k > 0){
            if(k&1) B.modmul(work, m);
            work.modmul(work, m);
            k >>= 1LL;
        }
        return B;
    }

    //単位行列を得る
    static Matrix I(size_t n){
        Matrix mat(n);
        for(int i = 0; i < n; i++) mat[i][i] = 1;
        return mat;
    }

    //行列式（det(A)）


    //cout
    friend ostream &operator<<(ostream &os, Matrix &p) {
        size_t n = p.height(), m = p.width();
        for(int i = 0; i < n; i++) {
            os << "[";
            for(int j = 0; j < m; j++) {
                os << p[i][j] << (j + 1 == m ? "]\n" : ",");
            }
        }
        return (os);
    }
};

int main(void){
    //MatrixのVerify
    cout << "Identifier Matrix:" << endl;
    Matrix<int> I = Matrix<int>::I(3);
    cout << I;

    Matrix<int> A(3, 3), B(3, 3);
    for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) A[i][j] = (i+j)*j % 4;
    for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) B[i][j] = (i+j)*i % 4; //てきとー
    cout << "Matrix A:" << endl;
    cout << A;
    cout << "Matrix B:" << endl;
    cout << B;

    Matrix<int> C = A*B;
    cout << C;
    cout << "A * B mod " << 3 << endl;
    A.modmul(B, 3);
    cout << A;
    return 0;
}