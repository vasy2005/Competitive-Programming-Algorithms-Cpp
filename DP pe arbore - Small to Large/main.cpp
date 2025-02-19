///DP pe arbore - Small to Large
///E. Count Paths
///https://codeforces.com/contest/1923/problem/E
#include <iostream>
#include <vector>
#include <map>

#define NMAX 200005

using namespace std;

int t;
int n;
int c[NMAX];
int x, y;
vector<int> l[NMAX];
vector<map<int, int>> cnt;
long long ans;
int i, ti;

void dfs(int, int = -1);

int main()
{
    cin >>t;

    for (ti = 1; ti <= t; ++ti)
    {
        cin >>n;
        for (i = 1; i <= n; ++i)
            cin >>c[i];

        for (i = 1; i <= n; ++i)
            l[i].clear();
        for (i = 2; i <= n; ++i)
        {
            cin >>x>>y;
            l[x].push_back(y);
            l[y].push_back(x);
        }

        ans = 0;
        cnt.assign(n+2, {});
        dfs(1);

        cout <<ans<<'\n';
    }
    return 0;
}

void dfs(int vf, int tata)
{
    int best = -1;
    for (auto vfnou: l[vf])
        if (vfnou != tata)
        {
            dfs(vfnou, vf);

            if (best == -1 || cnt[vfnou].size() > cnt[best].size())
                best = vfnou;
        }

    for (auto vfnou: l[vf])
        if (vfnou != tata && vfnou != best)
        {
            for (auto it: cnt[vfnou])
            {
                int col = it.first, counter = it.second;
                if (col != c[vf])
                    ans += 1LL * cnt[best][col] * counter;
                cnt[best][col] += counter;
            }
        }

    if (best != -1)
        swap(cnt[best], cnt[vf]);
    ans += cnt[vf][c[vf]];
    cnt[vf][c[vf]] = 1;
}
