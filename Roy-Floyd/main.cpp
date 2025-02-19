///infoarena Floyd-Warshall/Roy-Floyd
#include <fstream>

#define NMAX 105
#define INF 10000005

using namespace std;

ifstream fin("royfloyd.in");
ofstream fout("royfloyd.out");

int n, m;
int x, y, z;
int mat[NMAX][NMAX];
int i, j;

int main()
{
    fin >>n;
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
            fin >>mat[i][j];

    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
            if (!mat[i][j] && i != j) mat[i][j] = INF;

    for (z = 1; z <= n; ++z)
        for (x = 1; x <= n; ++x)
            for (y = 1; y <= n; ++y)
                mat[x][y] = min(mat[x][y], mat[x][z]+mat[z][y]);

    for (i = 1; i <= n; ++i)
    {
        for (j = 1; j <= n; ++j)
            if (mat[i][j] == INF) fout <<0<<' ';
            else fout <<mat[i][j]<<' ';
        fout <<'\n';
    }
    fout.close();
    return 0;
}
