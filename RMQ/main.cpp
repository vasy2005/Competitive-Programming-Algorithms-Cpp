///infoarena Range minimum query
#include <fstream>
#include <iostream>

#define NMAX 100005
#define VALMAX 100005

using namespace std;

ifstream fin("rmq.in");
ofstream fout("rmq.out");

int n, m;
int x, y;
int dp[NMAX][22];
int log[VALMAX];
int test[4005][4005][12][12];
int i, j;

int rmq(int, int);

int main()
{
    log[1] = 0;
    for (i = 2; i < VALMAX; ++i)
        log[i] = log[i/2]+1;

    fin >>n>>m;
    for (i = 1; i <= n; ++i)
        fin >>dp[i][0];

    for (j = 1; (1<<j) <= n; ++j)
        for (i = 1; i+(1<<j)-1 <= n; ++i)
            dp[i][j] = min(dp[i][j-1], dp[i+(1<<(j-1))][j-1]);

    for (i = 1; i <= m; ++i)
    {
        fin >>x>>y;
        fout <<rmq(x, y)<<'\n';
    }
    fout.close();
    return 0;
}

int rmq(int x, int y)
{
    int lg = log[y-x+1];
    int l = dp[x][lg];
    int r = dp[y-(1<<lg)+1][lg];
    return min(l, r);
}
