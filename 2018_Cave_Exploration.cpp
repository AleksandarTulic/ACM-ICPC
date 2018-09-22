#include <iostream>
#include <cmath>
#include <map>
#include <utility>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>

using namespace std;

int n,m;
vector <vector <int> > graf(10001);
vector <bool> flag1(10001, false), flag3(10001, false);
vector <int> d1(10001, -1),d2(10001, -1);
map <pair<int, int>, bool> flag2;
int br = 0;

void dfs_bridge(int cvor, int pre)
{
    br++;
    flag1[cvor] = true;
    d1[cvor] = br;
    d2[cvor] = br;

    for (int i=0;i<graf[cvor].size();i++)
    {
        if ( flag1[graf[cvor][i]] && graf[cvor][i] != pre ) d2[cvor] = min(d2[cvor], d1[graf[cvor][i]]);
        else if ( graf[cvor][i] != pre )
        {
            dfs_bridge(graf[cvor][i], cvor);
            d2[cvor] = min(d2[cvor], d2[graf[cvor][i]]);
            if ( d2[graf[cvor][i]] > d1[cvor] )
            {
                int a = graf[cvor][i];
                int b = cvor;
                flag2[{a, b}] = true;
                flag2[{b, a}] = true;
            }
        }
    }
}

void bfs(int cvor)
{
    queue <int> q;
    q.push(cvor);

    while (!q.empty())
    {
        int sad = q.front();
        q.pop();
        flag3[sad] = true;

        for (int i=0;i<graf[sad].size();i++)
            if ( !flag3[graf[sad][i]] )
            {
                int a = graf[sad][i];
                int b = sad;

                if ( flag2[{a, b}] || flag2[{b, a}] ) continue;
                q.push(graf[sad][i]);
            }
    }
}

int main()
{
    cin>>n>>m;

    for (int i=0;i<m;i++)
    {
        int a,b;
        cin>>a>>b;

        graf[a].push_back(b);
        graf[b].push_back(a);
    }

    for (int i=0;i<n;i++)
        if ( !flag1[i] )
            dfs_bridge(i, -1);

    bfs(0);

    int broj = 0;
    for (int i=0;i<n;i++)
        if ( flag3[i] ) broj++;

    cout<<broj<<endl;
    return 0;
}
