///infoarena - stramosi
#include <fstream>

#define NMAX 250005
#define LOGMAX 20

using namespace std;

ifstream fin("stramosi.in");
ofstream fout("stramosi.out");

int n, m; int x;
int p, q;
int dp[NMAX][LOGMAX];
int i, j;

int main()
{
    fin >>n>>m;
    for (i = 1; i <= n; ++i)
    {
        fin >>x;
        dp[i][0] = x;
    }

    for (j = 1; j <= 18; ++j)
        for (i = 1; i <= n; ++i)
            dp[i][j] = dp[dp[i][j-1]][j-1];

    for (i = 1; i <= m; ++i)
    {
        fin >>q>>p;
        for (j = 18; j >= 0; --j)
            if ((p>>j)&1) q = dp[q][j];

        fout <<q<<'\n';
    }
    fout.close();
    return 0;
}
