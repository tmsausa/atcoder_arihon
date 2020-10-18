#include <bits/stdc++.h>
#define range(i, l, r) for(long long int (i) = (l); (i) < (r); (i)++)
#define reversed_range(i, l, r) for (long long int (i) = (r) - 1; (i) >= l; (i)--)
using namespace std;
template <typename T>
using vec = vector<T>;
using lint = long long;
using ulint = unsigned long long;
using pint = pair<int, int>;
using plint = pair<lint, lint>;

template <typename S, typename T>
ostream& operator <<(ostream& os, pair<S, T> p) {
    os << "(";
    os << p.first << ", " << p.second;
    return os << ")";
}

template <typename T>
ostream& operator <<(ostream& os, vec<T> v) {
    os << "[";
    if (v.size() == 0) return os << "]";
    for (int i = 0; i < v.size() - 1; i++) {
        os << v.at(i) << ", ";
    }
    return os << v.at(v.size() - 1) << "]";
}

template <typename T>
ostream& operator <<(ostream& os, set<T>& s) {
    os << "{";
    if (s.begin() == s.end()) return os << "}";
    auto it_first_item = s.begin();
    os << *it_first_item;
    for (auto it = ++it_first_item; it != s.end(); it++) {
        os << ", " << *it;
    }
    return os << "}";
}

template <typename T>
ostream& operator <<(ostream& os, unordered_set<T>& s) {
    os << "{";
    if (s.begin() == s.end()) return os << "}";
    auto it_first_item = s.begin();
    os << *it_first_item;
    for (auto it = ++it_first_item; it != s.end(); it++) {
        os << ", " << *it;
    }
    return os << "}";
}

template <typename K, typename V>
ostream& operator <<(ostream& os, map<K, V> m) {
    os << "{";
    if (m.begin() == m.end()) return os << "}";
    auto it_first_item = m.begin();
    os << it_first_item->first << ": " << it_first_item->second;
    for (auto it = ++it_first_item; it != m.end(); it++) {
        os << ", " << it->first << ": " << it->second;
    }
    return os << "}";
}

template <typename K, typename V>
ostream& operator <<(ostream& os, unordered_map<K, V> m) {
    os << "{";
    if (m.begin() == m.end()) return os << "}";
    auto it_first_item = m.begin();
    os << it_first_item->first << ": " << it_first_item->second;
    for (auto it = ++it_first_item; it != m.end(); it++) {
        os << ", " << it->first << ": " << it->second;
    }
    return os << "}";
}

lint pow(lint num, lint e, lint MOD) {
    lint res = 1;
    lint cur_num = num;
    while (e) {
        if (e & 1) {
            res *= cur_num;
            res %= MOD;
        }
        cur_num *= cur_num;
        cur_num %= MOD;
        e >>= 1;
    }
    return res;
}

struct Chocolate {
    lint girl, boy, score;
    Chocolate(lint girl, lint boy, lint score) {
        this->girl = girl;
        this->boy = boy;
        this->score = score;
    }
};

int main() {
    cin.tie(0); cout.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    lint N, M, P, Q, R;
    cin >> N >> M >> P >> Q >> R;
    vec<vec<plint>> chocolate_list(N);
    range(i, 0, R) {
        lint x, y, z; cin >> x >> y >> z;
        x--; y--;
        chocolate_list.at(x).emplace_back(y, z);
    }
    vec<bool> is_girl_in_group(N, false);
    range(i, 0, P) is_girl_in_group.at(N - 1 - i) = true;
    lint ans = 0;
    do {
        vec<lint> boys_score(M, 0);
        range(i, 0, N) {
            if (is_girl_in_group.at(i)) {
                for (const plint& chocolate : chocolate_list.at(i)) boys_score.at(chocolate.first) += chocolate.second;
            }
        }
        sort(boys_score.begin(), boys_score.end(), greater<lint>());
        lint sum_score = 0;
        range(i, 0, Q) sum_score += boys_score.at(i);
        ans = max(ans, sum_score);
    } while (next_permutation(is_girl_in_group.begin(), is_girl_in_group.end()));
    cout << ans << "\n";
}