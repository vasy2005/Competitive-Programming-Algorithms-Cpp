///infoarena Eliminare Gaussiana
#include <fstream>
#include <vector>
#include <iomanip>

#define NMAX 305
#define EPS 0.0000001

using namespace std;

ifstream fin("gauss.in");
ofstream fout("gauss.out");

int n, m;
double mat[NMAX][NMAX];
vector<double> ans;
bool ok;
int i, j;

bool elim(double [][NMAX], vector<double>&);

int main()
{
    fin >>n>>m; m ++;
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j)
            fin >>mat[i][j];

    int ok = elim(mat, ans);

    if (ok)
        for (i = 1; i < m; ++i)
            fout <<setprecision(10)<<fixed<<ans[i]<<' ';
    else
        fout <<"Imposibil";

    fout <<'\n';
    fout.close();
    return 0;
}

bool elim(double mat[][NMAX], vector<double> &ans)
{
    int i, j, k;
    int l = 1, c = 1;
    while (l <= n && c < m)
    {
        for (k = l; k <= n; ++k)
            if (mat[k][c] < -EPS || mat[k][c] > EPS) //!= 0
                break;
        if (k == n+1)
        {
            c ++;
            continue;
        }

        if (l != k)
            for (j = c; j <= m; ++j)
                swap(mat[l][j], mat[k][j]);

        for (k = l+1; k <= n; ++k)
        {
            double x = mat[k][l];
            for (j = c; j <= m; ++j)
                mat[k][j] -= mat[l][j] * (x / mat[l][l]);
        }

        l++; c++;
    }

    ans.resize(m+2);

    for (i = n; i > 0; --i)
        for (j = 1; j <= m; ++j)
            if (mat[i][j] < -EPS || mat[i][j] > EPS) //!= 0
            {
                if (j == m)
                    return 0;

                ans[j] = mat[i][m];
                for (k = j+1; k < m; ++k)
                    ans[j] -= ans[k]*mat[i][k];
                ans[j] /= mat[i][i];

                break;
            }

    return 1;
}
