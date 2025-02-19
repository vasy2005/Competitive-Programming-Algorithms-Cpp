/// Boyer–Moore algoritmul elementului (votului) majoritar
/// avarcolaci ONI 2014
/// https://kilonova.ro/problems/226
#include <fstream>

#define TMAX 20

using namespace std;

ifstream fin("avarcolaci.in");
ofstream fout("avarcolaci.out");

int t;
int n;
int x;
int cand[TMAX];
int ti, i;

int main()
{
    fin >>t;
    for (ti = 1; ti <= t; ++ti)
    {
        fin >>n;

        int k = 0; cand[ti] = -1;
        for (i = 1; i <= 2*n; ++i)
        {
            fin >>x;
            if (k == 0)
                cand[ti] = x, k = 1;
            else
                if (cand[ti] == x)
                    k++;
                else
                    k--;
        }
    }

    fin.close();
    fin.open("avarcolaci.in");

    fin >>t;
    for (ti = 1; ti <= t; ++ti)
    {
        fin >>n;
        int k = 0;
        for (i = 1; i <= 2*n; ++i)
        {
            fin >>x;
            if (cand[ti] == x)
                k++;
        }
        if (k > n)
            fout <<cand[ti]<<'\n';
        else
            fout <<"Mozart\n";
    }

    fout.close();
    return 0;
}
