/// Virtual / Auxiliary Trees
///E. Count Paths
///https://codeforces.com/contest/1923/problem/E
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <map>

#define NMAX 200005

using namespace std;

int t;
int n;
int c[NMAX];
int x, y;
vector<int> l[NMAX];
long long ans;
int in[NMAX], out[NMAX]; int counter;
vector<pair<int, int>> euler;
int rmq[NMAX][20];
int logaritm[NMAX*3];
int first[NMAX];
vector<vector<int>> aux[NMAX];
vector<int> v[NMAX];
vector<map<int, int>> cnt;
vector<int> nimic;
int ti, i, j;

void dfs(int, int = -1, int = 1);
bool comp(int, int);
void compute_lca();
int lca(int, int);
void dfs2(int, int, int = -1);

int main()
{
    cin >>t;

    logaritm[1] = 0;
    for (i = 2; i < NMAX*3; ++i)
        logaritm[i] = logaritm[i/2] + 1;

    for (ti = 1; ti <= t; ++ti)
    {
        cin >>n;
        for (i = 1; i <= n; ++i)
            cin >>c[i];

        euler.clear();
        for (i = 1; i <= n; ++i)
        {
            l[i].clear(); v[i].clear();
            aux[i].clear();
            aux[i].assign(n+2, nimic);
            in[i] = out[i] = 0;
        }
        for (i = 2; i <= n; ++i)
        {
            cin >>x>>y;
            l[x].push_back(y);
            l[y].push_back(x);
        }

        ///construim virtual tree
        counter = 0;
        dfs(1);
        compute_lca();

        for (int i = 1; i <= n; ++i)
            v[c[i]].push_back(i);

        for (i = 1; i <= n; ++i)
        {
            if (v[i].size() <= 1) continue;
            sort(v[i].begin(), v[i].end(), comp);
            int lg = v[i].size();
            for (j = 0; j < lg-1; ++j)
            {
                int x = lca(v[i][j], v[i][j+1]);
                v[i].push_back(x);
            }

            sort(v[i].begin(), v[i].end(), comp);
            v[i].resize(unique(v[i].begin(), v[i].end()) - v[i].begin());
        }

        for (i = 1; i <= n; ++i)
        {
            if (!v[i].size()) continue;
            stack<int> s;
            s.push(v[i][0]);
            for (j = 1; j < v[i].size(); ++j)
            {
                while (s.size() && out[s.top()] < in[v[i][j]])
                    s.pop();
                aux[i][s.top()].push_back(v[i][j]);
                aux[i][v[i][j]].push_back(s.top());
                s.push(v[i][j]);
            }
        }
        // virtual tree finished

        ///dp
        ans = 0;
        for (i = 1; i <= n; ++i)
        {
            if (!v[i].size()) continue;

            for (j = 1; j <= n; ++j)
                if (aux[i][j].size())
                {
                    cnt.clear();
                    cnt.assign(n+2, {});
                    dfs2(i, j);
                    //cout <<i<<' '<<j<<'\n';
                    break;
                }
        }

        cout <<ans<<'\n';
    }
    return 0;
}

void dfs2(int col, int vf, int tata)
{
    int best = -1;
    for (auto vfnou: aux[col][vf])
        if (vfnou != tata && vf != vfnou)
        {
            dfs2(col, vfnou, vf);

            if (best == -1 || cnt[vfnou].size() > cnt[best].size())
                best = vfnou;
        }

    for (auto vfnou: aux[col][vf])
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

int lca(int x, int y)
{
    x = first[x]; y = first[y];
    if (x > y) swap(x, y);

    int lg = logaritm[y-x+1];
    int a = rmq[x][lg];
    int b = rmq[y-(1<<lg)+1][lg];

    return (euler[a].second < euler[b].second? euler[a].first: euler[b].first);
}

void compute_lca()
{
    int i, j;

    for (i = 0; i < euler.size(); ++i)
        rmq[i][0] = i;

    for (j = 1; (1<<j) <= euler.size(); ++j)
        for (i = 0; i+(1<<j)-1 < euler.size(); ++i)
        {
            int x = rmq[i][j-1];
            int y = rmq[i+(1<<(j-1))][j-1];
            rmq[i][j] = (euler[x].second < euler[y].second? x: y);
        }
}

bool comp(int a, int b)
{
    return in[a] < in[b];
}

void dfs(int vf, int tata, int niv)
{
    in[vf] = ++counter;
    first[vf] = euler.size();
    euler.push_back({vf, niv});

    for (auto vfnou: l[vf])
        if (vfnou != tata)
        {
            dfs(vfnou, vf, niv+1);
            euler.push_back({vf, niv});
        }

    out[vf] = ++counter;
}
