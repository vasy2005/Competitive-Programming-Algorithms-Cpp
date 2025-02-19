///infoarena Trie
#include <fstream>

#define ALFMAX 26
#define SMAX 25

using namespace std;

ifstream fin("trie.in");
ofstream fout("trie.out");

struct Trie
{
private:
    int cnt = 0;
    int lvs = 0;
    Trie* next[ALFMAX] = {};

public:
    void _insert(const char s[], int pos = 0)
    {
        lvs++;
        if (!s[pos])
        {
            cnt++;
            return;
        }

        if (!next[s[pos]-'a'])
            next[s[pos]-'a'] = new Trie;
        next[s[pos]-'a']->_insert(s, pos+1);
    }

    int _count(const char s[], int pos = 0)
    {
        if (!s[pos]) return cnt;
        if (!next[s[pos]-'a']) return 0;
        return next[s[pos]-'a']->_count(s, pos+1);
    }

    void _erase(const char s[], int pos = 0)
    {
        lvs--;
        if (!s[pos])
        {
            cnt--;
            return;
        }

        next[s[pos]-'a']->_erase(s, pos+1);
        if (!next[s[pos]-'a']->lvs)
        {
            delete next[s[pos]-'a'];
            next[s[pos]-'a'] = NULL;
        }
    }

    int lcp(const char s[], int pos = 0)
    {
        if (!s[pos]) return 0;
        if (!next[s[pos]-'a']) return 0;
        return 1 + next[s[pos]-'a']->lcp(s, pos+1);
    }
};

Trie trie;
int n;
int com; char s[SMAX];
int i, j;

int main()
{
    while (fin >>com)
    {
        fin >>s;
        if (com == 0)
        {
            trie._insert(s);
            continue;
        }
        if (com == 1)
        {
            trie._erase(s);
            continue;
        }
        if (com == 2)
        {
            fout <<trie._count(s)<<'\n';
            continue;
        }
        if (com == 3)
        {
            fout <<trie.lcp(s)<<'\n';
            continue;
        }
    }

    fout.close();
    return 0;
}
