///cses.fi problema 1130 Tree Matching
#include <iostream>
#include <vector>

#define NMAX 200005

using namespace std;

int n;
int x, y;
vector<int> l[NMAX];
int dp[NMAX][2];
bool f[NMAX];
int i;

void dfs(int);

int main()
{
    cin >>n;
    for (i = 1; i < n; ++i)
    {
        cin >>x>>y;
        l[x].push_back(y);
        l[y].push_back(x);
    }

    dfs(1);

    cout <<max(dp[1][0], dp[1][1])<<'\n';
    return 0;
}

void dfs(int vf)
{
    f[vf] = 1;

    dp[vf][1] = -1000000000;
    for (auto vfnou: l[vf])
        if (!f[vfnou])
        {
            dfs(vfnou);
            dp[vf][0] += max(dp[vfnou][0], dp[vfnou][1]);
            dp[vf][1] = max(dp[vf][1], dp[vfnou][0] - max(dp[vfnou][0], dp[vfnou][1]));
        }

    dp[vf][1] += 1 + dp[vf][0];
}
