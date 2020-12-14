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

int main() {
    cin.tie(0); cout.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    lint n; cin >> n;
    vec<lint> a_list(n);
    range(i, 0, n) cin >> a_list.at(i);
    vec<lint> a_list_copy = a_list;
    sort(a_list_copy.begin(), a_list_copy.end());
    unordered_map<lint, lint> compressed_val;
    range(i, 0, n) compressed_val.emplace(a_list_copy.at(i), i + 1);
    vec<lint> bit(2 * n + 10, 0);
    auto update = [&](lint i, lint v) {
        while (i <= n) {
            bit.at(i) += v;
            i += i & -i;
        }
    };
    auto sum = [&](lint i) {
        lint ans = 0;
        while (i > 0) {
            ans += bit.at(i);
            i -= i & -i;
        }
        return ans;
    };
    lint res = 0;
    range(i, 0, n) {
        res += i - sum(compressed_val.at(a_list.at(i)));
        update(compressed_val.at(a_list.at(i)), 1);
    }
    cout << res << "\n";
}