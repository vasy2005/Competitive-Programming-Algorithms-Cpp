///Kruskal infoarena
#include <fstream>
#include <vector>
#include <algorithm>

#define NMAX 200005
#define NMAX 400005

using namespace std;

ifstream fin("apm.in");
ofstream fout("apm.out");

struct Muchie
{
    int x, y, cost;
};

int n, m;
int x, y, cost;
vector<int> l[NMAX];
vector<Muchie> v;
int cc[NMAX];
int counter;
int minim;
int maxim, imax;
int suma;
vector<pair<int, int>> ans;
int i, j;

bool comp(Muchie, Muchie);
void dfs(int);

int main()
{
    fin >>n>>m;
    for (i = 1; i <= m; ++i)
    {
        fin >>x>>y>>cost;
        l[x].push_back({y});
        l[y].push_back({x});
        v.push_back({x, y, cost});
    }

    sort(v.begin(), v.end(), comp);

    for (i = 1; i <= n; ++i) cc[i] = i;

    for (i = 0; counter < n-1; ++i)
        if (cc[v[i].x] != cc[v[i].y])
        {
            counter ++;
            suma += v[i].cost;
            ans.push_back({v[i].x, v[i].y});

            if (cc[v[i].x] < cc[v[i].y])
            {
                minim = cc[v[i].x];
                maxim = cc[v[i].y]; imax = v[i].y;

            }
            else
                {
                    maxim = cc[v[i].x]; imax = v[i].x;
                    minim = cc[v[i].y];
                }

            dfs(imax);
        }

    fout <<suma<<'\n';
    fout <<ans.size()<<'\n';
    for (auto vf: ans)
        fout <<vf.first<<' '<<vf.second<<'\n';
    fout.close();
    return 0;
}

void dfs(int vf)
{
    cc[vf] = minim;
    for (auto vfnou: l[vf])
        if (cc[vfnou] == maxim)
            dfs(vfnou);
}

bool comp(Muchie a, Muchie b)
{
    return a.cost < b.cost;
}
