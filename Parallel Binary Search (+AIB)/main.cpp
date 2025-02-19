///Parallel binary search (+alte chestii gen AIB)
///Problema Meteors
///https://www.spoj.com/problems/METEORS/
#include <iostream>
#include <climits>
#include <vector>

#define NMAX 300005
#define INF 1000000000
#define LL long long
#define st first
#define dr second

using namespace std;

int n, m;
int o[NMAX], p[NMAX];
int k;
int l[NMAX], r[NMAX], a[NMAX];
LL bit[NMAX];
vector<int> li[NMAX];
vector<int> to_check[NMAX];
pair<int, int> bs[NMAX];
int i, j;

void build();
void update(int, int, int);
void update(int, int);
LL query(int, int);
LL query(int);

signed main()
{
    cin >>n>>m;

    for (i = 1; i <= m; ++i)
    {
        cin >>o[i];
        li[o[i]].push_back(i);
    }

    for (i = 1; i <= n; ++i)
        cin >>p[i];

    cin >>k;
    for (i = 1; i <= k; ++i)
        cin >>l[i]>>r[i]>>a[i];

    for (i = 1; i <= n; ++i)
    {
        bs[i] = {0, k+1};
        to_check[(k+1)/2].push_back(i);
    }

    bool changed = 1;
    while (changed)
    {
        changed = 0;

        build();
        for (i = 1; i <= n; ++i)
            if (bs[i].st+1 < bs[i].dr)
                to_check[(bs[i].st+bs[i].dr)/2].push_back(i);

        for (i = 1; i <= k; ++i)
        {
            if (l[i] > r[i])
            {
                update(a[i], 1, r[i]);
                update(a[i], l[i], m);
            }
            else
                update(a[i], l[i], r[i]);

            while (!to_check[i].empty())
            {
                changed = 1;
                int ind = to_check[i].back();
                to_check[i].pop_back();

                long long suma = 0;
                for (auto crt: li[ind])
                {
                    suma += query(crt);
                    if (suma >= p[ind])
                        break;
                }

                if (suma >= p[ind])
                    bs[ind].dr = i;
                else
                    bs[ind].st = i;
            }
        }
    }

    for (i = 1; i <= n; ++i)
        if (bs[i].dr > k)
            cout <<"NIE\n";
        else
            cout <<bs[i].dr<<'\n';
    return 0;
}

LL query(int st, int dr)
{
    return query(dr) - query(st-1);
}

LL query(int pos)
{
    LL ans = 0; pos--;
    for (int i = pos; i >= 0; i = (i & (i+1))-1)
        ans += bit[i];
    return ans;
}

void update(int val, int l, int r)
{
    update(val, l);
    update(-val, r+1);
}

void update(int val, int pos)
{
    pos--;
    for (int i = pos; i < m; i |= (i+1))
        bit[i] += val;
}

void build()
{
    for (int i = 0; i < m; ++i)
        bit[i] = 0;
}
