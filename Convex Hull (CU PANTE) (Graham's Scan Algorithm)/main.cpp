#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>

#define NMAX 100005
#define int long long
#define Point pair<int, int>
#define x first
#define y second
#define INF LLONG_MAX
#define PI 3.14159

using namespace std;

int n, l;
Point p0; int ind;
vector<Point> pct;
int i;

bool comp(Point, Point);
int orientation(Point, Point, Point);
double dist(Point, Point);

signed main()
{
    cin >>n>>l;
    pct.resize(n);
    p0 = {INF, INF}; ind = 0;
    for (i = 0; i < n; ++i)
    {
        cin >>pct[i].x>>pct[i].y;
        if (p0.y > pct[i].y)
            p0 = pct[i], ind = i;
        else
            if (p0.y == pct[i].y && p0.x > pct[i].x)
                p0 = pct[i], ind = i;
    }

    swap(pct[0], pct[ind]);
    sort(pct.begin()+1, pct.end(), comp);

    vector<Point> st;
    st.push_back(pct[0]);
    st.push_back(pct[1]);
    for (i = 2; i < (int)pct.size(); ++i)
    {
        while (st.size() > 2 && orientation(st[st.size()-2], st[st.size()-1], pct[i]) >= 0)
            st.pop_back();
        st.push_back(pct[i]);
    }

    double ans = 0;
    for (i = 1; i < (int)st.size(); ++i)
        ans += dist(st[i-1], st[i]);
    ans += dist(st[0], st.back());
    ans += 2.00*PI*l;

    cout <<(int)(ans + 0.5)<<'\n';
    return 0;
}

double dist(Point a, Point b)
{
    int aux = (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
    return sqrt(aux);
}

bool comp(Point a, Point b)
{
    return orientation(p0, a, b) < 0;
}

int orientation(Point a, Point b, Point c)
{
    return (b.y-a.y)*(c.x-b.x) - (c.y-b.y)*(b.x-a.x);
}
