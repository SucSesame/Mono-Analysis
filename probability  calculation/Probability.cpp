#pragma GCC optimize(3)

#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<cstdio>

using namespace std;

struct player{
    int cnt[11];
    vector<int> r, g, b, y;
    vector<string> acs;
}tp;

struct n_card{
    string c;
    int n;
}n_cards[72], n_pile[72];

const string colors[4] = {"Red", "Green", "Blue", "Yellow"};
const string action[8] = {"Skip", "Eat", "Reverse", "Trader", "Greed", "Gambler", "Joker", "Sticky Fingers"};

long long ans[10], n = 0, m = 0;
pair<int, int> ps[8];
int judging;

void trans(){
    tp.r.clear(); tp.g.clear(); tp.b.clear(); tp.y.clear();
    for(int i = 0; i <= 10; ++i) tp.cnt[i] = 0;
    tp.acs.clear();

    for(int i = 0; i < 8; ++i){
        if(ps[i].first == 0) tp.r.push_back(ps[i].second), tp.cnt[ps[i].second]++;
        if(ps[i].first == 1) tp.g.push_back(ps[i].second), tp.cnt[ps[i].second]++;
        if(ps[i].first == 2) tp.b.push_back(ps[i].second), tp.cnt[ps[i].second]++;
        if(ps[i].first == 3) tp.y.push_back(ps[i].second), tp.cnt[ps[i].second]++;
    }
}

void print(struct player pp){
    cout << "Red: ";
    for(int i: pp.r) cout << i << " ";
    cout << endl << "Green: ";
    for(int i: pp.g) cout << i << " ";
    cout << endl << "Blue: ";
    for(int i: pp.b) cout << i << " ";
    cout << endl << "Yellow: ";
    for(int i: pp.y) cout << i << " ";
    cout << endl;

    for(int i = 1; i <= 10; ++i) cout << pp.cnt[i] << " ";
    cout << endl;
    for(string i: pp.acs) cout << i << " ";
    cout << endl;
}

int judge(struct player p){
    int k = 0;
    bool flag = 0;
    for(int i = 1; i <= 10; ++i)
        k += p.cnt[i] / 4;
    if(k == 2) return 2;
    k = 0;

    for(int i = 1; i <= 10; ++i){
        k += p.cnt[i] / 3;
        if(p.cnt[i] == 2 || p.cnt[i] == 5) flag = 1;
    }
    if(k == 2 && flag) return 4;

    int sq1 = 0, sq2 = 0, cnt = 0;
    vector<int> r, g, b, y;
    for(int i: p.r) r.push_back(i);
    for(int i: p.g) g.push_back(i);
    for(int i: p.b) b.push_back(i);
    for(int i: p.y) y.push_back(i);

    flag = 1;
    for(int i = 1; i <= 10; ++i)
        if(p.cnt[i] % 2) flag = 0;
    if(flag && !(r.size() % 2 + g.size() % 2 + b.size() % 2 + y.size() % 2)){
        for(int i = 0; i < r.size(); i += 2)
            if(r[i] != r[i + 1]) flag = 0;
        for(int i = 0; i < g.size(); i += 2)
            if(g[i] != g[i + 1]) flag = 0;
        for(int i = 0; i < b.size(); i += 2)
            if(b[i] != b[i + 1]) flag = 0;
        for(int i = 0; i < y.size(); i += 2)
            if(y[i] != y[i + 1]) flag = 0;
        if(flag) return 3;
    }
    
    k = 0; flag = 0;
    for(int i = 1;  i <= 10; ++i) if(p.cnt[i] > 2) flag = 1;
    if(r.size() == 8)
        for(int i = 1; i < 8; ++i){
            if(r[i] - r[i - 1] == 1) ++k;
            else if(r[i] == r[i - 1]) ++cnt;
                 else k = 0;
            if(k == 3) k = 0, ++sq2;
        }
    if(g.size() == 8)
        for(int i = 1; i < 8; ++i){
            if(g[i] - g[i - 1] == 1) ++k;
            else if(g[i] == g[i - 1]) ++cnt;
                 else k = 0;
            if(k == 3) k = 0, ++sq2;
        }
    if(b.size() == 8)
        for(int i = 1; i < 8; ++i){
            if(b[i] - b[i - 1] == 1) ++k;
            else if(b[i] == b[i - 1]) ++cnt;
                 else k = 0;
            if(k == 3) k = 0, ++sq2;
        }
    if(y.size() == 8)
        for(int i = 1; i < 8; ++i){
            if(y[i] - y[i - 1] == 1) ++k;
            else if(y[i] == y[i - 1]) ++cnt;
                 else k = 0;
            if(k == 3) k = 0, ++sq2;
        }
    if(k + cnt + sq2 * 4 >= 8 && !flag) return 2;
    sq2 = 0; k = 0;
    if(r.size() / 4 + g.size() / 4 + b.size() / 4 + y.size() / 4 == 2){
        for(int i = 1; i < r.size(); ++i) if(r[i] - r[i - 1] == 1) ++k; else k = 0;
        for(int i = 1; i < g.size(); ++i) if(g[i] - g[i - 1] == 1) ++k; else k = 0;
        for(int i = 1; i < b.size(); ++i) if(b[i] - b[i - 1] == 1) ++k; else k = 0;
        for(int i = 1; i < y.size(); ++i) if(y[i] - y[i - 1] == 1) ++k; else k = 0;
        if(k == 6) return 2;
    }

    vector<int> t, tp;
    cnt = 0;
    for(int i = 1; i <= 10; ++i){
        if(p.cnt[i] > 4) return 0;
        if(p.cnt[i] >= 2) tp.push_back(i);
    }
    for(int i: tp){
        cnt = 0;
        for(int j: r)  if(j == i && cnt < 2) ++cnt; else t.push_back(j);
        for(int j: g)  if(j == i && cnt < 2) ++cnt; else t.push_back(j);
        for(int j: b)  if(j == i && cnt < 2) ++cnt; else t.push_back(j);
        for(int j: y)  if(j == i && cnt < 2) ++cnt; else t.push_back(j);
        k = 0; cnt = 0; sq1 = 0;
        for(int i = 1; i < t.size(); ++i){
            if(t[i] - t[i - 1] == 1) ++k;
            else if(t[i] == t[i - 1]) ++cnt;
                 else k = 0;
            if(k == 2) ++sq1, k = 0;
        }
        if(cnt + k + sq1 * 3 >= 6){
            if(r.size() == 8 || g.size() == 8 || b.size() == 8 || y.size() == 8) return 1;
            if(p.cnt[i] == 2){
                r.clear(); g.clear(); b.clear(); y.clear();
                for(int j: p.r)  if(j != i) r.push_back(j);
                for(int j: p.g)  if(j != i) g.push_back(j);
                for(int j: p.b)  if(j != i) b.push_back(j);
                for(int j: p.y)  if(j != i) y.push_back(j);
                if(r.size() % 3 + g.size() % 3 + b.size() % 3 + y.size() % 3) return 0;
                for(int j = 1; j < r.size(); ++j)  if(r[j] - r[j - 1] != 1) return 0;
                for(int j = 1; j < g.size(); ++j)  if(g[j] - g[j - 1] != 1) return 0;
                for(int j = 1; j < b.size(); ++j)  if(b[j] - b[j - 1] != 1) return 0;
                for(int j = 1; j < y.size(); ++j)  if(y[j] - y[j - 1] != 1) return 0;
                return 1;
            }
            cnt = 0, k = 0; sq1 = 0;
            for(int j = 1; j < r.size(); ++j){
                if(r[j] - r[j - 1] == 1) ++k;
                else if(r[j] == r[j - 1]) ++cnt;
                     else k = 0;
                if(k == 2) ++sq1, k = 0;
            }
            if(cnt + k == 3 && k > 0) ++sq1;
            cnt = 0, k = 0;
            for(int j = 1; j < g.size(); ++j){
                if(g[j] - g[j - 1] == 1) ++k;
                else if(g[j] == g[j - 1]) ++cnt;
                     else k = 0;
                if(k == 2) ++sq1, k = 0;
            }
            if(cnt + k == 3 && k > 0) ++sq1;
            cnt = 0, k = 0;
            for(int j = 1; j < b.size(); ++j){
                if(b[j] - b[j - 1] == 1) ++k;
                else if(b[j] == b[j - 1]) ++cnt;
                     else k = 0;
                if(k == 2) ++sq1, k = 0;
            }
            if(cnt + k == 3 && k > 0) ++sq1;
            cnt = 0, k = 0;
            for(int j = 1; j < y.size(); ++j){
                if(y[j] - y[j - 1] == 1) ++k;
                else if(y[j] == y[j - 1]) ++cnt;
                     else k = 0;
                if(k == 2) ++sq1, k = 0;
            }
            if(cnt + k == 3 && k > 0) ++sq1;
        }
        t.clear();
    }
    return 0;
}

void enumerate(int depth, int x){
    if(depth >= 8){
        trans();
        judging = judge(tp);
        ans[judging]++;
        if(judging){
            ++m;
            if(m % 10000 == 0) cout << m << ": " << ans[1] << " " << ans[2] << " " << ans[3] << " " << ans[4] << endl, print(tp);
        } 
        ++n;
        return ;
    }
    for(int i = x; i < 72; ++i){
        ps[depth] = make_pair(i / 18, (i % 18) / 2 + 1);
        enumerate(depth + 1, i + 1);
    }
    return ;
}

int main(){
    freopen("charts.txt","w",stdout);
    enumerate(0, 0);
    cout << n << " " << m << endl;
    cout << ans[1] << " " << ans[2] << " " << ans[3] << " " << ans[4] << endl;
    return 0;
}