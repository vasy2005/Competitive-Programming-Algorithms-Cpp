/// https://codeforces.com/contest/707/problem/D
/// codeforces D. Persistent Bookcase
#include <iostream>
#include <bitset>

#define NMAX 1005
#define QMAX 100005

using namespace std;

int n, m, q;
int v[NMAX];
int com, pos, x;
int ans;
int i;

struct Node
{
    bitset<NMAX> val = 0;
    int counter = 0;
    Node *l = NULL, *r = NULL;

    Node(Node *crtl, Node *crtr)
    {
        l = crtl; r = crtr;
    }
    Node(bitset<NMAX> x, Node *crtl, Node *crtr)
    {
        val = x; l = crtl; r = crtr;
    }
    Node(bitset<NMAX> x)
    {
        val = x;
    }
    Node(bitset<NMAX> x, int c)
    {
        val = x; counter = c;
    }
};

Node* build(int st = 1, int dr = n);
Node* update(Node *node, Node *crt, int pos, int q, int st = 1, int dr = n);
Node* query(Node *node, int pos, int st = 1, int dr = n);
int dfs(Node *node, int st = 1, int dr = n);

Node *root[QMAX];
int _time;

int main()
{
    cin >>n>>m>>q;

    root[0] = build(); _time = 0;

    for (i = 1; i <= q; ++i)
    {
        cin >>com>>pos;
        if (com <= 3)
        {
            if (com != 3) cin >>x;
            root[_time+1] = update(root[_time], query(root[_time], pos), pos, com); _time++;
        }
        else
            root[++_time] = root[pos];
    }

    for (i = 1; i <= q; ++i)
        cout <<dfs(root[i])<<'\n';
    return 0;
}

Node* build(int st, int dr)
{
    if (st == dr)
        return new Node(0);

    int mij = (st+dr)/2;
    return new Node(build(st, mij), build(mij+1, dr));
}

Node* update(Node *node, Node *crt, int pos, int q, int st, int dr)
{
    if (st == dr)
    {
        auto val = crt->val;
        int counter = crt->counter;
        if (q == 1)
        {
            if (!val[x-1]) counter ++;
            val[x-1] = 1;
        }
        else
            if (q == 2)
            {
                if (val[x-1]) counter --;
                val[x-1] = 0;
            }
            else
                {
                    counter = m-counter;
                    val.flip();
                }
        return new Node(val, counter);
    }

    int mij = (st+dr)/2;
    if (pos <= mij)
        return new Node(update(node->l, crt, pos, q, st, mij), node->r);
    else
        return new Node(node->l, update(node->r, crt, pos, q, mij+1, dr));
}

Node* query(Node *node, int pos, int st, int dr)
{
    if (st == dr)
        return node;

    int mij = (st+dr)/2;
    if (pos <= mij)
        return query(node->l, pos, st, mij);
    else
        return query(node->r, pos, mij+1, dr);
}

int dfs(Node *node, int st, int dr)
{
    if (st == dr)
        return node->counter;

    int mij = (st+dr)/2;
    return dfs(node->l, st, mij) + dfs(node->r, mij+1, dr);
}
