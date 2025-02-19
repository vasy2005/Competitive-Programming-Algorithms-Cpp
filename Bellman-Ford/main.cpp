///infoarena Algoritmul Bellman-Ford
#include <fstream>
#include <vector>
#include <set>

#define NMAX 50005
#define MMAX 250005
#define INF 100000005

using namespace std;

ifstream fin("bellmanford.in");
ofstream fout("bellmanford.out");

set<pair<int, int>> s;

int n, m; int start;
int x, y, cost;
vector<pair<int, int>> l[NMAX];
int dmin[NMAX];
int neg[NMAX];
int vfmin, minim;
int vf;
bool negativ;
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
        dmin[i] = INF;
    dmin[start] = 0;

    s.insert({0, start});
    while (!s.empty() && !negativ)
    {
        vfmin = (*s.begin()).second; minim = (*s.begin()).first;
        s.erase(s.begin());

        for (auto vfnou: l[vfmin])
        {
            vf = vfnou.first; cost = vfnou.second;
            if (dmin[vf] > minim + cost)
            {
                s.erase({dmin[vf], vf});
                dmin[vf] = minim + cost;
                s.insert({dmin[vf], vf});
                neg[vf]++;
                if (neg[vf] > n)
                {
                    negativ = 1;
                    break;
                }
            }
        }
    }

    if (negativ) fout <<"Ciclu negativ!\n";
    else
        {
            for (i = 1; i <= n; ++i)
            {
                if (i == start) continue;
                if (dmin[i] == INF) fout <<0<<' ';
                else fout <<dmin[i]<<' ';
            }
            fout <<'\n';
        }
    fout.close();
    return 0;
}
