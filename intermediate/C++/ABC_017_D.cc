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
    const lint MOD = 1e9 + 7;
    lint N, M; cin >> N >> M;
    vec<lint> f_list(N);
    range(i, 0, N) {
        cin >> f_list.at(i);
        f_list.at(i) -= 1;
    }

    vec<lint> num_choices(N + 1, 0);
    num_choices.at(0) = 1;
    vec<lint> num_choices_cuml(N + 1, 0);
    num_choices_cuml.at(0) = 1;
    lint left = 0;
    vec<lint> num_supplements(M, 0);
    range(right, 1, N + 1) {
        lint supplement = f_list.at(right - 1);
        if (num_supplements.at(supplement) > 0) {
            if (left == 0) left += 1;
            while (left < right and num_supplements.at(supplement) >= 1) {
                num_supplements.at(f_list.at(left - 1)) -= 1;
                left += 1;
            }
        }
        num_choices.at(right) = num_choices_cuml.at(right - 1) - (left >= 2 ? num_choices_cuml.at(left - 2) : 0LL);
        num_choices.at(right) %= MOD;
        if (num_choices.at(right) < 0) num_choices.at(right) += MOD;
        num_choices_cuml.at(right) = (num_choices_cuml.at(right - 1) + num_choices.at(right)) % MOD;
        num_supplements.at(supplement) += 1;
    }
    cout << num_choices.at(N) << "\n";
}