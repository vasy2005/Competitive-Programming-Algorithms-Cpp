///infoarena Potrivirea sirurilor
#include <fstream>
#include <vector>
#include <cstring>

#define SMAX 2000005

using namespace std;

ifstream fin("strmatch.in");
ofstream fout("strmatch.out");

int m, n;
char a[SMAX*2], b[SMAX];
int lps[SMAX*2];
int k;
vector<int> rez;
int i;

int main()
{
    fin >>a>>b;
    m = strlen(a); n = strlen(b);
    a[m] = '#'; a[m+1] = 0;
    strcat(a, b);

    k = 0; lps[0] = 0;
    for (i = 1; a[i]; ++i)
    {
        while (k > 0 && a[k] != a[i]) k = lps[k-1];
        if (a[k] == a[i]) k++;
        lps[i] = k;
    }

    for (i = m+1; a[i]; ++i)
        if (lps[i] == m)
            rez.push_back(i - 2*m);

    fout <<rez.size()<<'\n';
    int lim = min((int)rez.size(), 1000);
    for (i = 0; i < lim; ++i)
        fout <<rez[i]<<' ';
    fout <<'\n';
    fout.close();
    return 0;
}
