///pbinfo smallworld
#include <fstream>
#include <vector>

#define NMAX 100005

using namespace std;

ifstream fin("smallworld.in");
ofstream fout("smallworld.out");

int n;
int x, y;
vector<int> l[NMAX];
int down[NMAX], down2[NMAX], ind[NMAX];
int up[NMAX];
bool f[NMAX];
int i, j;

void dfsdown(int);
void dfsup(int);

int main()
{
    fin >>n;
    for (i = 1; i < n; ++i)
    {
        fin >>x>>y;
        l[x].push_back(y);
        l[y].push_back(x);
    }

    dfsdown(1);
    dfsup(1);

    for (i = 1; i <= n; ++i)
        fout <<max(down[i], up[i])<<'\n';
    fout.close();
    return 0;
}

void dfsdown(int vf)
{
    f[vf] = 1;
    for (auto vfnou: l[vf])
        if (!f[vfnou])
        {
            dfsdown(vfnou);
            if (down[vf] < down[vfnou]+1)
            {
                down2[vf] = down[vf];
                down[vf] = down[vfnou] + 1; ind[vf] = vfnou;
            }
            else
                if (down2[vf] < down[vfnou]+1)
                    down2[vf] = down[vfnou] + 1;
        }
}

void dfsup(int vf)
{
    f[vf] = 0;
    for (auto vfnou: l[vf])
        if (f[vfnou])
        {
            up[vfnou] = 1+max(up[vf], ind[vf]==vfnou? down2[vf]: down[vf]);
            dfsup(vfnou);
        }
}
