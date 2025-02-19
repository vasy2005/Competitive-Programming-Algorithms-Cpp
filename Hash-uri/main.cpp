///infoarena Hashuri
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin("hashuri.in");
ofstream fout("hashuri.out");

const int MOD = 196613;
vector<vector<int>> m(MOD+3);

int n;
int op, x;
int i;

void adauga(int);
void sterge(int);
vector<int>::iterator gaseste(int);

int main()
{
    fin >>n;
    for (i = 1; i <= n; ++i)
    {
        fin >>op>>x;
        if (op == 1)
        {
            adauga(x);
            continue;
        }

        if (op == 2)
        {
            sterge(x);
            continue;
        }

        fout <<(gaseste(x) != m[x%MOD].end())<<'\n';
    }
    fout.close();
    return 0;
}

void adauga(int x)
{
    if (gaseste(x) != m[x%MOD].end()) return;

    m[x%MOD].push_back(x);
}

void sterge(int x)
{
    for (auto it = m[x%MOD].begin(); it != m[x%MOD].end(); ++it)
        if ((*it) == x)
        {
            m[x%MOD].erase(it);
            break;
        }
}

vector<int>::iterator gaseste(int x)
{
    return find(m[x%MOD].begin(), m[x%MOD].end(), x);
}
