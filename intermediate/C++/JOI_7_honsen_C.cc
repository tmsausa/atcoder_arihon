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
    lint N, M; cin >> N >> M;
    vec<lint> P_list(N);
    range(i, 0, N) cin >> P_list.at(i);
    sort(P_list.begin(), P_list.end());
    lint max_score = 0;
    // case 1: only throw one.
    for (const lint& score : P_list) if (score <= M) {
        max_score = max(max_score, score);
    }
    vec<lint> score_list_pair;
    range(i, 0, N) range(j, i, N) {
        score_list_pair.emplace_back(P_list.at(i) + P_list.at(j));
    }
    sort(score_list_pair.begin(), score_list_pair.end());
    // case 2: throw two.
    for (const lint& score : score_list_pair) if (score <= M) {
        max_score = max(max_score, score);
    }
    // case 3: throw three.
    for (const lint& score : P_list) {
        if (score > M) continue;
        lint max_acceptable = M - score;
        auto it_ub = upper_bound(score_list_pair.begin(), score_list_pair.end(), max_acceptable);
        if (it_ub != score_list_pair.begin()) {
            lint optimal_rest_score = *--it_ub;
            max_score = max(max_score, optimal_rest_score + score);
        }
    }
    // case 4: throw four.
    for (const lint& score : score_list_pair) {
        if (score > M) continue;
        lint max_acceptable = M - score;
        auto it_ub = upper_bound(score_list_pair.begin(), score_list_pair.end(), max_acceptable);
        if (it_ub != score_list_pair.begin()) {
            lint optimal_rest_score = *--it_ub;
            max_score = max(max_score, optimal_rest_score + score);
        }
    }
    cout << max_score << "\n";
}