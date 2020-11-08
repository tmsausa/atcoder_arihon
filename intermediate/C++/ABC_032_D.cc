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
    lint N, W; cin >> N >> W;
    vec<plint> item_list(N);
    range(i, 0, N) {
        lint v, w; cin >> v >> w;
        item_list.at(i) = {v, w};
    }
    if (N <= 30) {
        lint Nf = N / 2, Nl = N - Nf;
        vec<plint> former_item_list(Nf);
        vec<plint> latter_item_list(Nl);
        range(i, 0, Nf) former_item_list.at(i) = item_list.at(i);
        range(i, 0, Nl) latter_item_list.at(i) = item_list.at(Nf + i);
        vec<plint> latter_item_superset;
        range(state, 0, 1 << Nl) {
            lint sum_v = 0, sum_w = 0;
            range(i, 0, Nl) {
                if ((state >> i) & 1) {
                    sum_v += latter_item_list.at(i).first;
                    sum_w += latter_item_list.at(i).second;
                }
            }
            latter_item_superset.emplace_back(sum_v, sum_w);
        }
        sort(latter_item_superset.begin(), latter_item_superset.end(),
            [](const plint& a, const plint& b) {return a.second < b.second;});
        lint cur_max_v = 0;
        vec<plint> latter_item_superset_clean;
        for (const plint& item : latter_item_superset) {
            if (item.first > cur_max_v) {
                latter_item_superset_clean.emplace_back(item);
                cur_max_v = item.first;
            }
        }
        // cout << latter_item_superset << "\n";
        // cout << latter_item_superset_clean << "\n";
        lint ans = 0;
        range(state, 0, 1 << Nf) {
            lint sum_v = 0, sum_w = 0;
            range(i, 0, Nf) if ((state >> i) & 1) {
                sum_v += former_item_list.at(i).first;
                sum_w += former_item_list.at(i).second;
            }
            if (sum_w > W) continue;
            lint rest_w = W - sum_w;
            auto it_ub = upper_bound(
                latter_item_superset_clean.begin(),
                latter_item_superset_clean.end(),
                plint{-1, rest_w},
                [](const plint& a, const plint& b) {return a.second < b.second;});
            if (it_ub == latter_item_superset_clean.begin()) {
                ans = max(ans, sum_v);
            }
            else {
                ans = max(ans, sum_v + (--it_ub)->first);
            }
        }
        cout << ans << "\n";
    } else if (all_of(item_list.begin(), item_list.end(),
        [](const plint& item) {return item.second <= 1000;})) {
        const lint MAX_WEIGHT = min(W, 1000 * N);
        vec<vec<lint>> dp(N, vec<lint>(MAX_WEIGHT + 1, 0));
        dp.at(0).at(item_list.at(0).second) = item_list.at(0).first;
        range(i, 1, N) {
            lint v, w;
            tie(v, w) = item_list.at(i);
            range(j, 0, MAX_WEIGHT + 1) {
                dp.at(i).at(j) = (j < w)
                    ? dp.at(i - 1).at(j) : max(dp.at(i - 1).at(j), dp.at(i - 1).at(j - w) + v);
            }
        }
        lint ans = 0;
        range(j, 0, MAX_WEIGHT + 1) ans = max(ans, dp.at(N - 1).at(j));
        cout << ans << "\n";
    } else {  // v <= 1000
        const lint MAX_VALUE = 1000 * N;
        vec<vec<lint>> dp(N, vec<lint>(MAX_VALUE + 1, 1LL << 59));
        dp.at(0).at(0) = 0;
        dp.at(0).at(item_list.at(0).first) = item_list.at(0).second;
        range(i, 1, N) {
            lint v, w;
            tie(v, w) = item_list.at(i);
            range(j, 0, MAX_VALUE + 1) {
                dp.at(i).at(j) = (j < v)
                    ? dp.at(i - 1).at(j) : min(dp.at(i - 1).at(j), dp.at(i - 1).at(j - v) + w);
            }
        }
        lint ans = 0;
        range(j, 0, MAX_VALUE + 1) if (dp.at(N - 1).at(j) <= W) ans = j;
        cout << ans << "\n";
    }
}