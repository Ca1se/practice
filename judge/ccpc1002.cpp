#include<iostream>
#include<assert.h>
#include<cmath>
#define ll long long
using namespace std;
const ll maxn = 1e10 + 5;
ll n, mod;

inline ll V2IDX(ll v, ll N, ll Ndr, ll nv) {
    return v >= Ndr ? (N/v - 1) : (nv - v);
}

ll primesum(ll N) {
    ll *S;
    ll *V;

    ll r = (ll)sqrt(N);
    ll Ndr = N/r;

    assert(r*r <= N and (r+1)*(r+1) > N);

    ll nv = r + Ndr - 1;

    V = new ll[nv];
    S = new ll[nv];

    for (ll i=0; i<r; i++) {
        V[i] = N/(i+1);
    }
    for (ll i=r; i<nv; i++) {
        V[i] = V[i-1] - 1;
    }

    for (ll i=0; i<nv; i++) {
        S[i] = V[i] * (V[i] + 1) / 2 - 1;
    }

    for (ll p=2; p<=r; p++) {
        if (S[nv-p] > S[nv-p+1]) {
            ll sp = S[nv-p+1];
            ll p2 = p*p;
            for (ll i=0; i<nv; i++) {
                if (V[i] >= p2) {
                    S[i] -= p * (S[V2IDX(V[i]/p, N, Ndr, nv)] - sp);
                } else {
                    break;
                }
            }
        }
    }

    return S[0];
}

ll axn(ll n) {
    ll x1 = 3 + n + 1;
    ll x2 = n - 1;
    if(n % 2){
        x2 /= 2;
    }else{
        x1 /= 2;
    }
    return (x1 % mod) * (x2 % mod) % mod;
}

int main() {
    int t;
    cin >> t;
    while(t--){
        cin >> n >> mod;
        ll sump = (primesum(n + 1) - 2) % mod;
        ll sumn = axn(n);
        cout << ((sump + sumn) % mod) << endl;
    }
    return 0;
}