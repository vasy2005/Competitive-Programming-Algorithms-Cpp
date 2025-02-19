///infoarena 2SAT
#include <fstream>
#include <stack>
#include <vector>

#define NMAX 100005*2

using namespace std;

ifstream fin("2sat.in");
ofstream fout("2sat.out");

int n, m;
int a, b;
vector<int> l[NMAX];
int f[NMAX];
int low[NMAX], disc[NMAX]; int t;
int fctc[NMAX]; int nr;
stack<int> s;
int i, j;

void dfs(int);

int main()
{
    fin >>n>>m;
    for (i = 1; i <= m; ++i)
    {
        fin >>a>>b;
        l[-a+n].push_back(b+n);
        l[-b+n].push_back(a+n);
        //-a+n este A, a+n este !A
    }

    for (i = 1; i <= n; ++i)
    {
        if (!low[i+n])
            dfs(i+n);
        if (!low[-i+n])
            dfs(-i+n);
    }

    for (i = 1; i <= n; ++i)
        if (fctc[-i+n] == fctc[i+n])
        {
            fout <<-1<<'\n';
            fout.close();
            return 0;
        }

    for (i = 1; i <= n; ++i)
        fout <<(fctc[-i+n] > fctc[i+n])<<' ';
    fout <<'\n';
    fout.close();
    return 0;
}

void dfs(int vf)
{
    low[vf] = disc[vf] = ++t;
    s.push(vf);
    for (auto vfnou: l[vf])
    {
        if (!low[vfnou])
            dfs(vfnou);
        if (low[vfnou] > 0)
            low[vf] = min(low[vf], low[vfnou]);
    }

    if (low[vf] == disc[vf])
    {
        nr ++;
        do
        {
            int crt = s.top(); s.pop();
            fctc[crt] = nr; low[crt] = -1;
            if (crt == vf) break;
        }
        while (1);
    }
}
