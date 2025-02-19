///infoarena Ciclu Eulerian
#include <fstream>
#include <vector>

#define NMAX 100005
#define MMAX 500005

using namespace std;

ifstream fin("ciclueuler.in");
ofstream fout("ciclueuler.out");

int n, m;
int x, y;
vector<int> l[NMAX];
int d[NMAX];
vector<pair<int, int>> v;
bool f[MMAX];
vector<int> ans;
int i, j;

bool grad_par();
void euler(int);

int main()
{
    fin >>n>>m;
    for (i = 1; i <= m; ++i)
    {
        fin >>x>>y;
        v.push_back({x, y});
        l[x].push_back(v.size()-1);
        l[y].push_back(v.size()-1);
        d[x]++; d[y]++;
    }

    if (!grad_par())
    {
        fout <<-1<<'\n';
        fout.close();
        return 0;
    }

    euler(1);

    ans.pop_back();
    for (auto i: ans) fout <<i<<' ';
    fout <<'\n';
    fout.close();
    return 0;
}

void euler(int x)
{
    int ind, y;
    while (!l[x].empty())
    {
        ind = l[x].back(); l[x].pop_back();

        if (!f[ind])
        {
            f[ind] = 1;

            if (v[ind].first == x) y = v[ind].second;
            else y = v[ind].first;

            euler(y);
        }
    }

    ans.push_back(x);
}

bool grad_par()
{
    int i;
    for (i = 1; i <= n; ++i)
        if (d[i]%2 == 1) return 0;
    return 1;
}
