#ifdef CPTEST
#include "C.h"
#endif
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
//競プロ用横着定義
using namespace std;
typedef long long ll;
typedef vector<ll> intVec;
typedef vector<string> strVec;
#define rep(i, l, r) for (ll i = l; i < (ll)(r); i++)
string str(ll v)
{
    return to_string(v);
}
ll num(string s)
{
    return strtoll(s.c_str(), nullptr, 10);
}

bool isDebugPrintOn = true;

//ユーティリティ
//1行読み取り
string readLine()
{
    string buf;
    getline(std::cin, buf);
    return buf;
}

//文字列結合
string Join(intVec iv, string separator)
{
    string buf;
    for(ll i:iv)
    {
        buf += str(i) + separator;
    }
    buf.erase(buf.size() - separator.size(), separator.size());
    return buf;
}
string Join(strVec sv, string separator)
{
    string buf;
    for(string s:sv)
    {
        buf += s + separator;
    }
    buf.erase(buf.size() - separator.size(), separator.size());
    return buf;
}

//文字列をスペース区切りでintの配列に分解
intVec splitI(const string& org, ll size = -1)
{
    intVec dst;
    if(size > 0)
    {
        dst.reserve(size);
    }
    ll ofs = 0;
    size_t sp = 0;
    const char* cstr = org.c_str();
    do
    {
        sp = org.find_first_of(' ', ofs);
        dst.push_back(strtoll(&cstr[ofs], nullptr, 10));
        ofs = sp + 1;
    } while(sp != string::npos);
    return dst;
}

//文字列をスペース区切りでstringに分解
void splitS(const string& org, strVec& dst)
{
    ll ofs = 0;
    size_t sp = 0;
    do
    {
        sp = org.find_first_of(' ', ofs);
        dst.push_back(org.substr(ofs, sp - ofs));
        ofs = sp + 1;
    } while(sp != string::npos);
}

//テスト実行用デバッグ出力
void DebugPrint(const string& str)
{
    if(isDebugPrintOn)
    {
        cout << str << endl;
    }
}
void DebugPrint(const ll val)
{
    if(isDebugPrintOn)
    {
        cout << to_string(val) << endl;
    }
}
void DebugPrint(const intVec& iv)
{
    if(isDebugPrintOn)
    {
        string buf;
        buf = "[";
        buf += Join(iv, ", ");
        buf += "]";
        cout << buf << endl;
    }
}
void DebugPrint(const strVec& sv)
{
    if(isDebugPrintOn)
    {
        string buf;
        buf = "[";
        buf += Join(sv, ", ");
        buf += "]";
        cout << buf << endl;
    }
}

string Impl_C(const vector<string> &inputs)
{
    // show me your moves!
    return inputs[0] + "\n";
}

#ifndef CPTEST
int main(int, char**)
{
    isDebugPrintOn = false;
    vector<string> inputs;
    inputs.push_back(readLine());
    cout << Impl_C(inputs);
}
#endif
