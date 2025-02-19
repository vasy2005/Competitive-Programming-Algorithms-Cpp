/// codeforces E. Partition Game
/// https://codeforces.com/contest/1527/problem/E
#include <iostream>

#define NMAX 35005
#define KMAX 105
#define INF LONG_MAX
#define int long long

using namespace std;

int n, k;
int v[NMAX];
int dp[KMAX][NMAX];
int last[NMAX];
int aint[NMAX*4];
int lazy[NMAX*4];
int i, j, t;

void build(int, int, int, int);
void update(int, int, int, int, int, int);
int query(int, int, int, int, int);

signed main()
{
    cin >>n>>k;
    for (i = 1; i <= n; ++i)
        cin >>v[i];

    for (i = 1; i <= k; ++i)
        for(j = 1; j <= n; ++j)
            dp[i][j] = INF;

    dp[1][0] = dp[1][1] = 0; last[v[1]] = 1;
    for (j = 2; j <= n; ++j)
    {
        dp[1][j] = dp[1][j-1];
        if (last[v[j]])
            dp[1][j] += j-last[v[j]];
        last[v[j]] = j;
    }

    for (i = 2; i <= k; ++i)
    {
        dp[i][1] = 0;
        build(1, 1, n, i-1);
        for (j = 1; j <= n; ++j)
            last[v[j]] = 0;
        for (j = 2; j <= n; ++j)
        {
            if (last[v[j]] != 0)
                update(1, 1, n, j - last[v[j]], 1, last[v[j]]-1);

            last[v[j]] = j;

            dp[i][j] = min(dp[i][j], query(1, 1, n, 1, j));
        }
    }

    cout <<dp[k][n]<<'\n';
    return 0;
}

void build(int nod, int st, int dr, int lin)
{
    lazy[nod] = 0;
    if (st == dr)
    {
        aint[nod] = dp[lin][st];
        return;
    }

    int mij = (st+dr) / 2;
    build(nod*2, st, mij, lin);
    build(nod*2+1, mij+1, dr, lin);

    aint[nod] = min(aint[nod*2], aint[nod*2+1]);
}

void update(int nod, int st, int dr, int val, int l, int r)
{
    if (lazy[nod] != 0)
    {
        aint[nod] += lazy[nod];

        if (st != dr)
        {
            lazy[nod*2] += lazy[nod];
            lazy[nod*2+1] += lazy[nod];
        }

        lazy[nod] = 0;
    }

    if (st > dr || dr < l || st > r)
        return;

    if (st >= l && dr <= r)
    {
        aint[nod] += val;

        if (st != dr)
        {
            lazy[nod*2] += val;
            lazy[nod*2+1] += val;
        }

        return;
    }

    int mij = (st+dr) / 2;
    update(nod*2, st, mij, val, l, r);
    update(nod*2+1, mij+1, dr, val, l, r);

    aint[nod] = min(aint[nod*2], aint[nod*2+1]);
}

int query(int nod, int st, int dr, int l, int r)
{
    if (lazy[nod])
    {
        aint[nod] += lazy[nod];

        if (st != dr)
        {
            lazy[nod*2] += lazy[nod];
            lazy[nod*2+1] += lazy[nod];
        }

        lazy[nod] = 0;
    }

    if (st > dr || r < st || l > dr)
        return INF;

    if (l <= st && dr <= r)
        return aint[nod];

    int mij = (st+dr) / 2;
    int x = INF, y = INF;
    x = query(nod*2, st, mij, l, r);
    y = query(nod*2+1, mij+1, dr, l, r);

    return min(x, y);
}
