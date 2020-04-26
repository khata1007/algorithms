#include <bits/stdc++.h>

#define rep(i, n) for(int i = 0; i < n; i++)

using namespace std;
using ll = long long;
int mod = 1000000007;
int Rank[1000001];

vector<int> sort_cyclic_shifts(string const &s){
    int n = s.size();
    const int alphabet = 256;
    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);

    //k = 0でのソート
    rep(i, n) cnt[s[i]]++; //各文字の出現回数をカウント
    for(int i = 1; i < alphabet; i++) cnt[i] += cnt[i-1];
    rep(i, n) p[--cnt[s[i]]] = i;

    c[p[0]] = 0;
    int classes = 1;
    for(int i = 1; i < n; i++){
        if(s[p[i]] != s[p[i-1]]) classes++;
        c[p[i]] = classes-1;
    }

    //k = 1からk = logn + 1のソート
    vector<int> pn(n), cn(n);

    for(int k = 0; (1 << k) < n; k++){
        for(int i = 0; i < n; i++){
            pn[i] = p[i] - (1 << k);
            if(pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for(int i = 0; i < n; i++) cnt[c[pn[i]]]++;
        for(int i = 1; i < classes; i++) cnt[i] += cnt[i-1];
        for(int i = n-1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];

        cn[p[0]] = 0;
        classes = 1;
        for(int i = 1; i < n; i++){
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << k) % n)]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << k)) % n]};
            if(cur != prev) ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}

vector<int> suffix_array_construction(string s){
    s += "$";
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}

void construct_lcp(string s, vector<int>& sf, vector<int>& lcp){
    int n = s.length();
    for(int i = 0; i < n; i++) Rank[sf[i]] = i;

    int h = 0;
    for(int i = 0; i < n; i++){
        if(Rank[i] == 0) continue;
        int j = sf[Rank[i] - 1];

        if(h > 0) h--;
        for(; j+h < n && i+h < n; h++){
            if(s[j+h] != s[i+h]) break;
        }
        lcp[Rank[i]-1] = h;
    }
}

int main(void){
    string s; cin >> s;
    vector<int> sf = suffix_array_construction(s);
    vector<int> lcp(sf.size(), 0);
    construct_lcp(s, sf, lcp);
    rep(i, sf.size()){
        cout << lcp[i] << endl;
    }
    return 0;
}