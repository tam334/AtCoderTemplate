/*
    Union-Find のスニペット
    ここから下をコピペ
*/
#ifdef TEST_SNIPPET
#include "SnippetTestCommon.h"
//競プロ用横着定義
using namespace std;
typedef long long ll;
typedef vector<ll> intVec;
typedef vector<string> strVec;
#define rep(i, l, r) for (ll i = l; i < (ll)(r); i++)
#endif

namespace UnionFind
{
    // 競プロではUFの生データからなんかする場合があるかも？
    // とりあえず公開し、第一引数にしてもらう。
    struct Data
    {
        ll parent;
        ll rank;
    };

    /// @brief UFの親番号の初期化 ノード番号が1-indexed前提
    /// @param parent 親番号
    /// @param nodeNum ノード数
    /// @note この時点でノード数がわからない場合は順次ユーザーでparent.push_back(i)等をする
    void Setup(vector<Data>& ufData, ll nodeNum)
    {
        ufData.resize(nodeNum + 1);
        rep(i, 1, nodeNum + 1)
        {
            ufData[i].parent = i;
            ufData[i].rank = 0;
        }
    }

    ll root(vector<Data>& parent, ll x)
    {
        if(parent[x].parent == x)
        {
            return x;
        }
        else
        {
            return parent[x].parent = root(parent, parent[x].parent);
        }
    }

    /// @brief 結合判定
    /// @param parent 親番号 SetupParentで初期化済み
    /// @param A ノード
    /// @param B ノード
    /// @return 結合か
    bool Find(vector<Data>& parent, ll A, ll B)
    {
        while(parent[B].parent != B)
        {
            B = parent[B].parent;
        }
        while(parent[A].parent != A)
        {
            A = parent[A].parent;
        }
        return A == B;
    }

    /// @brief 結合
    /// @param parent 親番号 SetupParentで初期化済み
    /// @param A 結合される側
    /// @param B 結合する側
    void Union(vector<Data>& parent, ll A, ll B)
    {
        ll rootB = root(parent, B);
        ll rootA = root(parent, A);
        if(rootB == rootA)
        {
            return;
        }

        // 深さが増えにくいように
        if(parent[rootA].rank < parent[rootB].rank)
        {
            parent[rootA].parent = rootB;
        }
        else
        {
            parent[rootB].parent = rootA;
        }

        if(parent[rootA].rank == parent[rootB].rank)
        {
            parent[rootA].rank++;
        }
    }
}

#ifdef TEST_SNIPPET
int main(int, char**)
{
    // AtCoder typical contest 001
    intVec iv = splitI(cin);
    ll N = iv[0];
    ll Q = iv[1];
    vector<UnionFind::Data> parent;
    UnionFind::Setup(parent, N);
    string ans;
    rep(i, 0, Q)
    {
        iv = splitI(cin);
        ll P = iv[0];
        ll A = iv[1];
        ll B = iv[2];
        if(P == 0)
        {
            UnionFind::Union(parent, A, B);
        }
        else
        {
            if(UnionFind::Find(parent, A, B))
            {
                ans += "Yes\n";
            }
            else
            {
                ans += "No\n";
            }
        }
    }
    cout << ans;
    return 0;
}
#endif