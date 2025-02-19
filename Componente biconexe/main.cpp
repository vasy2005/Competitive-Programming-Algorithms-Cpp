///pbinfo #1572 ComponenteBiconexe
#include <fstream>
#include <vector>
#include <stack>

#define TMAX 20
#define NMAX 100005

using namespace std;

ifstream fin("componentebiconexe.in");
ofstream fout("componentebiconexe.out");

int cer;
int n, m;
int x, y;
vector<int> l[NMAX];
int low[NMAX], disc[NMAX];
int counter;
bool art[NMAX];
vector<pair<int, int>> mcrt;
vector<int> cb[NMAX]; int nr;
stack<int> s;
int start, fiustart;
vector<int> pctart;
int ti, i;

void dfs(int, int);
void cerinta1();
void cerinta2();
void cerinta3();

int main()
{
    fin >>cer;

    fin >>n>>m;
    for (i = 1; i <= m; ++i)
    {
        fin >>x>>y;
        l[x].push_back(y);
        l[y].push_back(x);
    }

    start = 1;
    dfs(1, -1);

    if (fiustart > 1)
        art[start] = 1;
    for (i = 1; i <= n; ++i)
        if (art[i])
            pctart.push_back(i);

    if (cer == 1)
        cerinta1();
    else
        if (cer == 2)
            cerinta2();
        else
            cerinta3();
    fout.close();
    return 0;
}

void cerinta1()
{
    int i;
    fout <<nr<<'\n';
    for (i = 1; i <= nr; ++i)
    {
        fout <<cb[i].size()<<' ';
        for (auto vf: cb[i])
            fout <<vf<<' ';
        fout <<'\n';
    }
}

void cerinta2()
{
    int i;
    fout <<pctart.size()<<'\n';
    for (auto vf: pctart)
        fout <<vf<<' ';
    fout <<'\n';
}

void cerinta3()
{
    int i;
    fout <<mcrt.size()<<'\n';
    for (auto crt: mcrt)
        fout <<crt.first<<' '<<crt.second<<'\n';
}

void dfs(int vf, int tata)
{
    low[vf] = disc[vf] = ++counter;

    s.push(vf);
    for (auto vfnou: l[vf])
    {
        if (vfnou == tata)
            continue;

        if (!disc[vfnou])
        {
            if (vf == start)
                fiustart ++;
            dfs(vfnou, vf);

            low[vf] = min(low[vf], low[vfnou]);

            if (low[vfnou] >= disc[vf])
            {
                if (vf != start) art[vf] = 1;

                if (low[vfnou] > disc[vf])
                    mcrt.push_back({vf, vfnou});

                int fiu; nr++;
                do
                {
                    fiu = s.top(); s.pop();
                    cb[nr].push_back(fiu);
                }
                while (fiu != vfnou);
                cb[nr].push_back(vf);
            }
        }
        else
            low[vf] = min(low[vf], disc[vfnou]);
    }
}
