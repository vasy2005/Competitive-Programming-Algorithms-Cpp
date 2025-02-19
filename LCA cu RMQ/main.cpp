///infoarena Lowest Common Ancestor
#include <fstream>
#include <vector>

#define NMAX 100005

using namespace std;

ifstream fin("lca.in");
ofstream fout("lca.out");

int n, m;
int x, y;
vector<int> l[NMAX];
int dp[2*NMAX][22];
int logaritm[NMAX*2];
vector<pair<int, int>> euler;
int first[NMAX];
bool f[NMAX];
int i, j;

void dfs(int, int);
int lca(int, int);

int main()
{
    logaritm[1] = 0;
    for (i = 2; i < 2*NMAX; ++i)
        logaritm[i] = logaritm[i/2]+1;

    fin >>n>>m;
    for (i = 2; i <= n; ++i)
    {
        fin >>x;
        l[x].push_back(i);
        l[i].push_back(x);
    }

    dfs(1, 0);

    for (i = 0; i < euler.size(); ++i)
        dp[i][0] = i;

    int l, r;
    for (j = 1; (1<<j) <= euler.size(); ++j)
        for (i = 0; i+(1<<j)-1 < euler.size(); ++i)
        {
            l = dp[i][j-1];
            r = dp[i+(1<<(j-1))][j-1];
            dp[i][j] = (euler[l].second < euler[r].second? l: r);
        }

    for (i = 1; i <= m; ++i)
    {
        fin >>x>>y;
        fout <<lca(x, y)<<'\n';
    }
    fout.close();
    return 0;
}

int lca(int x, int y)
{
    x = first[x]; y = first[y];
    if (x > y) swap(x, y);

    int lg = logaritm[y-x+1];

    int l = dp[x][lg];
    int r = dp[y-(1<<lg)+1][lg];

    return (euler[l].second < euler[r].second? euler[l].first: euler[r].first);
}

void dfs(int vf, int niv)
{
    f[vf] = 1;
    first[vf] = euler.size();
    euler.push_back({vf, niv});

    for (auto vfnou: l[vf])
        if (!f[vfnou])
        {
            dfs(vfnou, niv+1);
            euler.push_back({vf, niv});
        }
}
