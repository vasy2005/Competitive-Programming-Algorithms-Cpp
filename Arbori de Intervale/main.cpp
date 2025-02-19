///infoarena Arbori de intervale
#include <fstream>
#include <iostream>

#define NMAX 100005

using namespace std;

ifstream fin("arbint.in");
ofstream fout("arbint.out");

int n, m;
int op, a, b;
int v[NMAX];
int aint[NMAX*4];
int i;

void build(int, int, int);
int query(int, int, int, int, int);
void update(int, int, int, int, int);

int main()
{
    fin >>n>>m;
    for (i = 1; i <= n; ++i)
        fin >>v[i];

    build(1, 1, n);

    for (i = 1; i <= m; ++i)
    {
        fin >>op>>a>>b;
        if (op == 0)
            fout <<query(1, 1, n, a, b)<<'\n';
        else
            update(1, 1, n, a, b);
    }
    fout.close();
    return 0;
}

void build(int nod, int st, int dr)
{
    if (st == dr)
    {
        aint[nod] = v[st];
        return;
    }

    int mij = (st+dr) / 2;
    build(nod*2, st, mij);
    build(nod*2+1, mij+1, dr);

    aint[nod] = max(aint[nod*2], aint[nod*2+1]);
}

int query(int nod, int st, int dr, int a, int b)
{
    if (a <= st && dr <= b)
    {
        cout <<st<<' '<<dr<<'\n';
        return aint[nod];
    }

    int ansl = 0, ansr = 0;
    int mij = (st+dr) / 2;
    if (a <= mij)
        ansl = query(nod*2, st, mij, a, b);
    if (mij+1 <= b)
        ansr = query(nod*2+1, mij+1, dr, a, b);

    return max(ansl, ansr);
}

void update(int nod, int st, int dr, int pos, int val)
{
    if (st == dr)
    {
        aint[nod] = val;
        return;
    }

    int mij = (st+dr) / 2;
    if (pos <= mij) update(nod*2, st, mij, pos, val);
    else
        update(nod*2+1, mij+1, dr, pos, val);

    aint[nod] = max(aint[nod*2], aint[nod*2+1]);
}
