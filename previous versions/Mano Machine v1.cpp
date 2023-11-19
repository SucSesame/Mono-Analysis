#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<cmath>

using namespace std;

struct player{
    int cnt[11];
    vector<int> r, g, b, y;
    vector<string> acs;
}p[4], pp;

struct n_card{
    string c;
    int n;
}n_cards[72], n_pile[72];

const string colors[4] = {"Red", "Green", "Blue", "Yellow"};
const string action[8] = {"Skip", "Eat", "Reverse", "Trader", "Greed", "Gambler", "Joker", "Sticky Fingers"};
const int v[10] = {0, 0, 1, 2, 2, 2, 2, 2, 1, 0};
string a_cards[24], a_pile[24];
int a_num = 0, n_num = 0;

float S(struct player px){
    int sum = 0;
    for(int i = 1; i <= 10; i++)
        sum += px.cnt[i] * px.cnt[i];
    return sum;
}

float Q(struct player px){
    float t = 1.0, sum = 0;
    for(int i = 1; i < px.r.size(); i++) t *= px.r[i] - px.r[i - 1];
    sum += pow(px.r.size() / t, 2); t = 1;
    for(int i = 1; i < px.g.size(); i++) t *= px.g[i] - px.g[i - 1];
    sum += pow(px.g.size() / t, 2); t = 1;
    for(int i = 1; i < px.b.size(); i++) t *= px.b[i] - px.b[i - 1];
    sum += pow(px.b.size() / t, 2); t = 1;
    for(int i = 1; i < px.y.size(); i++) t *= px.y[i] - px.y[i - 1];
    sum += pow(px.y.size() / t, 2); t = 1;
    return sum * 2;
}

float R(struct player px){
    int sum = 0;
    for(int i = 1; i <= 10; i++)
        sum += px.cnt[i] * v[i];
    return sum;
}

float evaluate(struct player px){
    return R(px) + Q(px) + S(px);
}

void shuffle(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 18; j++){
            n_cards[i * 18 + j].n = j % 9 + 1;
            n_cards[i * 18 + j].c = colors[i];
            //cout << i * 18 + j << " " << n_cards[i * 18 + j].c << " " <<  n_cards[i * 18 + j].n << endl;
        }
    }
    int num = 0;
    for(int i = 0; i < 8; i++){
        if(i == 0 || i == 2){
            for(int j = 0; j < 3; j++){
                a_cards[num] = action[i];
                num++;
            }
        }
        if(i == 1){
            for(int j = 0; j < 6; j++){
                a_cards[num] = action[i];
                num++;
            }
        }
        if(i == 3 || i == 5 || i == 6 || i == 7){
            for(int j = 0; j < 2; j++){
                a_cards[num] = action[i];
                num++;
            }
        }
        if(i == 4){
            for(int j = 0; j < 4; j++){
                a_cards[num] = action[i];
                num++;
            }
        }
    }
    random_shuffle(n_cards, n_cards + 72);
    random_shuffle(a_cards, a_cards + 24);
}

void initialize(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 7; j++){
            if(n_cards[n_num].c == "Red") p[i].r.push_back(n_cards[n_num].n);
            if(n_cards[n_num].c == "Green") p[i].g.push_back(n_cards[n_num].n);
            if(n_cards[n_num].c == "Blue") p[i].b.push_back(n_cards[n_num].n);
            if(n_cards[n_num].c == "Yellow") p[i].y.push_back(n_cards[n_num].n);
            p[i].cnt[n_cards[n_num].n]++;
            n_num++;
        }
        for(int j = 0; j < 2; j++){
            p[i].acs.push_back(a_cards[a_num]);
            a_num++;
        }
        sort(p[i].r.begin(), p[i].r.end());
        sort(p[i].g.begin(), p[i].g.end());
        sort(p[i].b.begin(), p[i].b.end());
        sort(p[i].y.begin(), p[i].y.end());
    }
}

void print(struct player px){
    cout << "Red: ";
    for(int i: px.r) cout << i << " ";
    cout << endl << "Green: ";
    for(int i: px.g) cout << i << " ";
    cout << endl << "Blue: ";
    for(int i: px.b) cout << i << " ";
    cout << endl << "Yellow: ";
    for(int i: px.y) cout << i << " ";
    cout << endl;

    for(int i = 1; i <= 10; i++) cout << px.cnt[i] << " ";
    cout << endl;
    for(string i: px.acs) cout << i << " ";
    cout << endl;
    cout << evaluate(px) << endl;
}

int judge(struct player p){
    int k = 0;
    bool flag = 0;
    for(int i = 1; i <= 10; i++)
        k += p.cnt[i] / 4;
    if(k == 2) return 2;
    k = 0;

    for(int i = 1; i <= 10; i++){
        k += p.cnt[i] / 3;
        if(p.cnt[i] == 2 || p.cnt[i] == 5) flag = 1;
    }
    if(k == 2 && flag) return 1;

    int sq1 = 0, sq2 = 0, cnt = 0;
    vector<int> r, g, b, y;
    for(int i: p.r) r.push_back(i);
    for(int i: p.g) g.push_back(i);
    for(int i: p.b) b.push_back(i);
    for(int i: p.y) y.push_back(i);

    flag = 1;
    for(int i = 1; i <= 10; i++)
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
    for(int i = 1;  i <= 10; i++) if(p.cnt[i] > 2) flag = 1;
    if(r.size() == 8)
        for(int i = 1; i < 8; i++){
            if(r[i] - r[i - 1] == 1) k++;
            else if(r[i] == r[i - 1]) cnt++;
                 else k = 0;
            if(k == 3) k = 0, sq2++;
        }
    if(g.size() == 8)
        for(int i = 1; i < 8; i++){
            if(g[i] - g[i - 1] == 1) k++;
            else if(g[i] == g[i - 1]) cnt++;
                 else k = 0;
            if(k == 3) k = 0, sq2++;
        }
    if(b.size() == 8)
        for(int i = 1; i < 8; i++){
            if(b[i] - b[i - 1] == 1) k++;
            else if(b[i] == b[i - 1]) cnt++;
                 else k = 0;
            if(k == 3) k = 0, sq2++;
        }
    if(y.size() == 8)
        for(int i = 1; i < 8; i++){
            if(y[i] - y[i - 1] == 1) k++;
            else if(y[i] == y[i - 1]) cnt++;
                 else k = 0;
            if(k == 3) k = 0, sq2++;
        }
    if(k + cnt + sq2 * 4 >= 8 && !flag) return 2;
    sq2 = 0; k = 0;
    if(r.size() / 4 + g.size() / 4 + b.size() / 4 + y.size() / 4 == 2){
        for(int i = 1; i < r.size(); i++) if(r[i] - r[i - 1] == 1) k++; else k = 0;
        for(int i = 1; i < g.size(); i++) if(g[i] - g[i - 1] == 1) k++; else k = 0;
        for(int i = 1; i < b.size(); i++) if(b[i] - b[i - 1] == 1) k++; else k = 0;
        for(int i = 1; i < y.size(); i++) if(y[i] - y[i - 1] == 1) k++; else k = 0;
        if(k == 6) return 2;
    }

    vector<int> t, tp;
    cnt = 0;
    for(int i = 1; i <= 10; i++){
        if(p.cnt[i] > 4) return 0;
        if(p.cnt[i] >= 2) tp.push_back(i);
    }
    for(int i: tp){
        cnt = 0;
        for(int j: r)  if(j == i && cnt < 2) cnt++; else t.push_back(j);
        for(int j: g)  if(j == i && cnt < 2) cnt++; else t.push_back(j);
        for(int j: b)  if(j == i && cnt < 2) cnt++; else t.push_back(j);
        for(int j: y)  if(j == i && cnt < 2) cnt++; else t.push_back(j);
        k = 0; cnt = 0; sq1 = 0;
        for(int i = 1; i < t.size(); i++){
            if(t[i] - t[i - 1] == 1) k++;
            else if(t[i] == t[i - 1]) cnt++;
                 else k = 0;
            if(k == 2) sq1++, k = 0;
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
                for(int j = 1; j < r.size(); j++)  if(r[j] - r[j - 1] != 1) return 0;
                for(int j = 1; j < g.size(); j++)  if(g[j] - g[j - 1] != 1) return 0;
                for(int j = 1; j < b.size(); j++)  if(b[j] - b[j - 1] != 1) return 0;
                for(int j = 1; j < y.size(); j++)  if(y[j] - y[j - 1] != 1) return 0;
                return 1;
            }
            cnt = 0, k = 0; sq1 = 0;
            for(int j = 1; j < r.size(); j++){
                if(r[j] - r[j - 1] == 1) k++;
                else if(r[j] == r[j - 1]) cnt++;
                     else k = 0;
                if(k == 2) sq1++, k = 0;
            }
            if(cnt + k == 3 && k > 0) sq1++;
            cnt = 0, k = 0;
            for(int j = 1; j < g.size(); j++){
                if(g[j] - g[j - 1] == 1) k++;
                else if(g[j] == g[j - 1]) cnt++;
                     else k = 0;
                if(k == 2) sq1++, k = 0;
            }
            if(cnt + k == 3 && k > 0) sq1++;
            cnt = 0, k = 0;
            for(int j = 1; j < b.size(); j++){
                if(b[j] - b[j - 1] == 1) k++;
                else if(b[j] == b[j - 1]) cnt++;
                     else k = 0;
                if(k == 2) sq1++, k = 0;
            }
            if(cnt + k == 3 && k > 0) sq1++;
            cnt = 0, k = 0;
            for(int j = 1; j < y.size(); j++){
                if(y[j] - y[j - 1] == 1) k++;
                else if(y[j] == y[j - 1]) cnt++;
                     else k = 0;
                if(k == 2) sq1++, k = 0;
            }
            if(cnt + k == 3 && k > 0) sq1++;
        }
        t.clear();
    }
    return 0;
}

int main(){
    srand(unsigned(time(0)));
    shuffle();
    initialize();
    print(p[0]);
    /*int t = 0;
    cout << "Red: "; cin >> t;
    while(t != -1) pp.r.push_back(t), pp.cnt[t]++, cin >> t;
    cout << "Green: "; cin >> t;
    while(t != -1) pp.g.push_back(t), pp.cnt[t]++, cin >> t;
    cout << "Blue: "; cin >> t;
    while(t != -1) pp.b.push_back(t), pp.cnt[t]++, cin >> t;
    cout << "Yellow: "; cin >> t;
    while(t != -1) pp.y.push_back(t), pp.cnt[t]++, cin >> t;
    sort(pp.r.begin(), pp.r.end());
    sort(pp.g.begin(), pp.g.end());
    sort(pp.b.begin(), pp.b.end());
    sort(pp.y.begin(), pp.y.end());

    print(pp);
    cout << judge(pp) << endl;*/
    return 0;
}