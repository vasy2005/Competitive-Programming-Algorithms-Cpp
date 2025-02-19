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
int dp[NMAX][20];
int in[NMAX], out[NMAX];
int counter;
bool f[NMAX];
int i, j;

void dfs(int);
int lca(int, int);
bool is_ancestor(int, int);

int main()
{
    fin >>n>>m;
    for (i = 2; i <= n; ++i)
    {
        fin >>dp[i][0];
        l[dp[i][0]].push_back(i);
    }

    for (j = 1; j <= 18; ++j)
        for (i = 1; i <= n; ++i)
            dp[i][j] = dp[dp[i][j-1]][j-1];

    dfs(1);

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
    if (is_ancestor(x, y)) return x;
    if (is_ancestor(y, x)) return y;

    int i;
    for (i = 18; i >= 0; --i)
        if (!is_ancestor(dp[x][i], y))
            x = dp[x][i];

    return dp[x][0];
}

bool is_ancestor(int x, int y)
{
    if (!x || x == y) return 1;

    return (in[x] < in[y] && out[x] > out[y]);
}

void dfs(int vf)
{
    f[vf] = 1;
    in[vf] = ++counter;
    for (auto vfnou: l[vf])
        if (!f[vfnou]) dfs(vfnou);
    out[vf] = ++counter;
}
