///infoarena Paduri de multimi disjuncte
#include <fstream>
#include <vector>

#define NMAX 100005

using namespace std;

ifstream fin("disjoint.in");
ofstream fout("disjoint.out");

int n, m;
int op, x, y;
int sz[NMAX], tata[NMAX];
int i;

void make_set(int);
int find_set(int);
void union_sets(int, int);

int main()
{
    fin >>n>>m;

    for (i = 1; i <= n; ++i)
        make_set(i);

    for (i = 1; i <= m; ++i)
    {
        fin >>op>>x>>y;
        if (op == 1)
            union_sets(x, y);
        else
            fout <<(find_set(x) == find_set(y)? "DA": "NU")<<'\n';
    }
    fout.close();
    return 0;
}

void union_sets(int x, int y)
{
    x = find_set(x);
    y = find_set(y);

    if (x == y) return;

    if (sz[x] < sz[y])
        swap(x, y);

    tata[y] = x; sz[x] += sz[y];
}

int find_set(int vf)
{
    if (tata[vf] == vf) return vf;
    return tata[vf] = find_set(tata[vf]);
}

void make_set(int vf)
{
    tata[vf] = vf; sz[vf] = 0;
}
