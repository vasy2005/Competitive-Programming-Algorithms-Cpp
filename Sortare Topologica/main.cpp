#include <fstream>
#include <cstring>

#define SMAX 260

using namespace std;

int n;
char s[SMAX];
int i;

int main()
{
    cin >> n;
    cin >> s;

    for (i = 0; s[i + n - 1] != 0; ++i)
    {
        char aux = s[i];
        s[i] = 0;
        cout << s;
        cout << s + i + n;
        s[i] = aux;
    }
    return 0;
}

//s = "cezarabcdefgh0"
// 
//aux = 'z'
// //i = 2
//n = 3

//cout <<p+3