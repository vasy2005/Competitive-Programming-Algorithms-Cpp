#include <fstream>
#include <vector>
#define NMAX 100002
using namespace std;
ifstream fin("topsort.in");
ofstream fout("topsort.out");
int n,nr;
vector <int> G[NMAX];
int di[NMAX];
int crt[NMAX]; //nodurile de pe nivelul curent
int niv[2][NMAX];
void citire();
void descompunere();
int main()
{
    citire();
    descompunere();
    return 0;
}
void citire()
{int m,i,x,y;
    fin>>n>>m;
    for(i=0;i<m;i++)
        {
        fin>>x>>y;
        //il adaug pe y in lista de adiacenta a lui x;
        G[x].push_back(y);
        di[y]++;
        }
}
void descompunere()
{int lg[2],i,x,j,icrt=0,iurm=1;
nr=0;
lg[0]=0;
for(i=1;i<=n;i++)
    if(di[i]==0)
        niv[0][lg[0]++]=i;
    while(nr<n)
        {
        for(i=0;i<lg[icrt];i++)
            {
            fout<<niv[icrt][i]<<' ';
            di[niv[icrt][i]]=-1;
            }
        lg[iurm]=0;
        for(i=0;i<lg[icrt];i++)
            {
            x=niv[icrt][i];
            for(j=0;j<G[x].size();j++)
                {
                di[G[x][j]]--;
                if(di[G[x][j]]==0)
                    niv[iurm][lg[iurm]++]=G[x][j];
                }
            }
        nr+=lg[icrt];
        icrt=1-icrt;
        iurm=1-iurm;
        }
}
