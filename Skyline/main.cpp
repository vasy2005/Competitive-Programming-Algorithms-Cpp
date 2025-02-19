///Sursa Virtual Judge UVA105 The Skyline Problem
///https://vjudge.net/problem/UVA-105
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

#define NMAX 5005

using namespace std;

struct Building
{
    int l, r, h;
};

struct Wall
{
    int x, h;
    bool start;
};

int n;
Building v[NMAX];
multiset<int> s;
int prevmax, maxim;
vector<Wall> wall;
int i;

bool compwall(Wall, Wall);

int main()
{
    while (cin >>v[++n].l>>v[n].h>>v[n].r);
    n--;

    for (i = 1; i <= n; ++i)
    {
        wall.push_back({v[i].l, v[i].h, 1});
        wall.push_back({v[i].r, v[i].h, 0});
    }

    sort(wall.begin(), wall.end(), compwall);

    prevmax = 0;
    s.insert(0);
    bool ok = 0;
    for (i = 0; i < 2*n; ++i)
    {
        if (wall[i].start)
            s.insert(wall[i].h);
        else
            s.erase(s.find(wall[i].h));

        maxim = *(s.rbegin());
        if (maxim != prevmax)
        {
            if (ok) cout <<' ';
            cout <<wall[i].x<<' '<<maxim;
            prevmax = maxim; ok = 1;
        }
    }
    cout <<'\n';
    return 0;
}

bool compwall(Wall a, Wall b)
{
    if (a.x != b.x)
        return a.x < b.x;

    if (a.start && b.start)
        return a.h > b.h;

    if (!a.start && !b.start)
        return a.h < b.h;

    return a.start;
}
