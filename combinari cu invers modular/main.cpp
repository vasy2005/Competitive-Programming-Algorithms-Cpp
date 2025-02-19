#include <fstream>

#define MOD 17

using namespace std;

ifstream fin("combim.in");
ofstream fout("combim.out");

int n, k;

void euclidex(int, int, int&, int&, int&);
int inv(int, int);
int comb(int, int);
int pow(int, int);

int main()
{
    fin >>n>>k;
    fout <<comb(n, k)<<'\n';

    fout.close();
    return 0;
}

int comb(int n, int k)
{
    int i; int a = 1, b = 1, c = 1;
    for (i = n-k+1; i <= n; ++i)
        a = (a * i) % MOD;

    for (i = 2; i <= k; ++i)
        b = (b*i) % MOD;
    //b = inv(b, MOD);
    b = pow(b, MOD-2);

    return ((a) * (b)) % MOD;
}

int pow(int n, int k)
{
    if (!k) return 1;
    if (!n) return 0;
    int val = pow(n, k/2);
    return (k%2? (val*val*(n%MOD))%MOD: (val*val)%MOD);
}

void euclidex(int a, int b, int &d, int &x, int &y)
{
    if (!b)
    {
        d = a;
        x = 1; y = 0;
        return;
    }

    int x0, y0;
    euclidex(b, a%b, d, x0, y0);
    x = y0; y = x0 - a/b * y0;
}

int inv(int a, int mod)
{
    int x = 0, y, d;
    euclidex(a, mod, d, x, y);

    if (x <= 0) x = MOD + x%MOD;

    return x;
}

