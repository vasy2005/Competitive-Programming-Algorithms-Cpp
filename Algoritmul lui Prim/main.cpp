///pbinfo Prim
#include <fstream>
#include <vector>

#define NMAX 105
#define INF 10000005

using namespace std;

ifstream fin("prim.in");
ofstream fout("prim.out");

int n, m; int start;
int x, y, cost;
vector<pair<int, int>> l[NMAX];
int dmin[NMAX];
bool f[NMAX];
int minim;
int vfmin;
int vf;
int suma;
int tata[NMAX];
int i, j;

int main()
{
    fin >>n>>m; start = 1;
    for (i = 1; i <= m; ++i)
    {
        fin >>x>>y>>cost;
        l[x].push_back({y, cost});
        l[y].push_back({x, cost});
    }

    for (i = 1; i <= n; ++i)
        dmin[i] = INF, tata[i] = start;

    for (auto vfnou: l[start])
        dmin[vfnou.first] = vfnou.second;

    f[start] = 1;
    dmin[start] = 0; tata[start] = 0;
    for (i = 1; i < n; ++i)
    {
        minim = INF;
        for (j = 1; j <= n; ++j)
            if (!f[j] && minim > dmin[j])
                minim = dmin[j], vfmin = j;

        f[vfmin] = 1; suma += minim;
        for (auto vfnou: l[vfmin])
        {
            vf = vfnou.first; cost = vfnou.second;
            if (!f[vf] && dmin[vf] > cost)
            {
                dmin[vf] = cost;
                tata[vf] = vfmin;
            }
        }
    }

    fout <<suma<<'\n';
    for (i = 1; i <= n; ++i) fout <<tata[i]<<' ';
    fout <<'\n';
    fout.close();
    return 0;
}
