//infoarena Dijkstra
#include <fstream>
#include <vector>
#include <set>

#define NMAX 50005
#define MMAX 250005
#define INF 100000005

using namespace std;

ifstream fin("dijkstra.in");
ofstream fout("dijkstra.out");

set<pair<int, int>> s;

int n, m; int start;
int x, y, cost;
vector<pair<int, int>> l[NMAX];
int cmin[NMAX];
int vfmin, minim;
int vf;
int i, j;

int main()
{
    fin >>n>>m; start = 1;
    for (i = 1; i <= m; ++i)
    {
        fin >>x>>y>>cost;
        l[x].push_back({y, cost});
    }

    for (i = 1; i <= n; ++i)
        cmin[i] = INF;
    cmin[start] = 0;

    s.insert({0, start});
    while (!s.empty())
    {
        vfmin = (*s.begin()).second; minim = (*s.begin()).first;
        s.erase(s.begin());

        for (auto vfnou: l[vfmin])
        {
            vf = vfnou.first; cost = vfnou.second;
            if (cmin[vf] > minim + cost)
            {
                s.erase({cmin[vf], vf});
                cmin[vf] = minim + cost;
                s.insert({cmin[vf], vf});
            }
        }
    }

    for (i = 1; i <= n; ++i)
    {
        if (i == start) continue;
        if (cmin[i] == INF) fout <<0<<' ';
        else fout <<cmin[i]<<' ';
    }
    fout <<'\n';
    fout.close();
    return 0;
}
