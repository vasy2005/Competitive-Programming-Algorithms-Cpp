#include <iostream>
#include <stack>

#define NMAX 40004

using namespace std;

int n;
int h[NMAX];
int l[NMAX], r[NMAX];
stack<int> s;
int maxim, suma;
int i;

int main()
{
    cin >>n;
    for (i = 1; i <= n; ++i)
    {
        cin >> h[i];
    }

    s.push(0);
    for (i = 1; i <= n; ++i)
    {
        while (s.size() > 1 && h[s.top()] >= h[i])
            s.pop();

        l[i] = s.top();

        s.push(i);
    }

    s.clear();
    s.push(n + 1);
    for (i = n; i >= 1; --i)
    {
        while (s.size() > 1 && h[s.top()] >= h[i])
            s.pop();

        r[i] = s.top();

        s.push(i);
    }

    for (i = 1; i <= n; ++i)
    {
        suma = (r[i] - l[i] - 1) * h[i];
        maxim = max(maxim, suma);
    }

    cout <<maxim<<'\n';
    return 0;
}
