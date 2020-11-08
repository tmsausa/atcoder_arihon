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
    lint N, L, T; cin >> N >> L >> T;
    vec<lint> X_list(N), W_list(N);
    range(i, 0, N) {
        cin >> X_list.at(i) >> W_list.at(i);
        W_list.at(i) = W_list.at(i) == 1 ? 1 : -1;
    }
    vec<lint> final_pos_list(N);
    range(i, 0, N) {
        lint final_pos = (X_list.at(i) + T % L * W_list.at(i)) % L;
        if (final_pos < 0) final_pos += L;
        final_pos_list.at(i) = final_pos;
    }
    sort(final_pos_list.begin(), final_pos_list.end());
    lint zekken_first_ant = 0;
    lint first_ant_direction = W_list.at(0), first_ant_pos = X_list.at(0);
    range(i, 1, N) {
        if (first_ant_direction == W_list.at(i)) continue;
        lint num_times_to_meet = 0;
        if (X_list.at(i) - first_ant_pos < 2 * T) {
            num_times_to_meet += 1;
            num_times_to_meet += (2 * T - (X_list.at(i) - first_ant_pos)) / L;
        }
        zekken_first_ant += first_ant_direction * num_times_to_meet;
        zekken_first_ant %= N;
        if (zekken_first_ant < 0) zekken_first_ant += N;
    }
    lint final_first_ant_pos = (first_ant_pos + T * first_ant_direction) % L;
    if (final_first_ant_pos < 0) final_first_ant_pos += L;
    lint first_ant_idx = lower_bound(final_pos_list.begin(), final_pos_list.end(), final_first_ant_pos) - final_pos_list.begin();
    cout << final_first_ant_pos << "\n";
    cout << first_ant_idx << " " << final_pos_list.at(first_ant_idx) << "\n";
    range(i, first_ant_idx - 3, first_ant_idx + 3) cout << final_pos_list.at(i) << '\n';
    unordered_map<lint, lint> zekken_to_idx;
    range(z, zekken_first_ant, N) zekken_to_idx.emplace(z, (first_ant_idx + z - zekken_first_ant) % N);
    range(z, 0, zekken_first_ant) zekken_to_idx.emplace(z, (first_ant_idx + N - zekken_first_ant + z) % N);
    // cout << zekken_to_idx << "\n";
    // range(z, 0, N) cout << final_pos_list.at(zekken_to_idx.at(z)) << "\n";
}