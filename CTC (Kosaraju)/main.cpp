///infoarena Componente tare conexe
#include <fstream>
#include <vector>
#include <algorithm>

#define NMAX 100005

using namespace std;

ifstream fin("ctc.in");
ofstream fout("ctc.out");

int n, m;
int x, y;
vector<int> l[NMAX];
vector<int> lt[NMAX];
bool f[NMAX];
vector<int> postord;
vector<int> ctc[NMAX]; int nr;
int i, j;

void dfs(int);
void dfst(int);

int main()
{
    fin >>n>>m;
    for (i = 1; i <= m; ++i)
    {
        fin >>x>>y;
        l[x].push_back(y);
        lt[y].push_back(x);
    }

    for (i = 1; i <= n; ++i)
        if (!f[i])
            dfs(i);

    ///postordine invers e sortare topologica
    for (i = postord.size()-1; i >= 0; --i)
        if (f[postord[i]])
        {
            nr ++;
            dfst(postord[i]);
        }

    fout <<nr<<'\n';
    for (i = 1; i <= nr; ++i)
    {
        for (auto vf: ctc[i])
            fout <<vf<<' ';
        fout <<'\n';
    }
    fout.close();
    return 0;
}

void dfst(int vf)
{
    f[vf] = 0;
    ctc[nr].push_back(vf);
    for (auto vfnou: lt[vf])
        if (f[vfnou])
            dfst(vfnou);
}

void dfs(int vf)
{
    f[vf] = 1;
    for (auto vfnou: l[vf])
        if (!f[vfnou])
            dfs(vfnou);

    postord.push_back(vf);
}


for (i = 1; i <= n; ++i)
    if (!f[i])
        dfs(i);

void dfs(int vf)
{
    f[vf] = 1;
    for (auto vfnou: l[vf])
        if (!f[vfnou])
            dfs(vfnou);
    postord.push_back(vf);
}

for (i = postord.size()-1; i >= 0; --i)
    if (f[postord[i]])
        dfst(postord[i]);

void dfst(int vf)
{
    f[vf] = 0;
    comp[nr].push_back(vf);
    for (auto vfnou: lt[vf])
        if (f[vfnou])
            dfst(vfnou);
}
