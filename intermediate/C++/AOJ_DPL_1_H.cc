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
    lint num_items_former_half = N / 2, num_items_latter_half = N - num_items_former_half;
    vec<plint> item_list_former_half(num_items_former_half), item_list_latter_half(num_items_latter_half);
    range(i, 0, num_items_former_half) {
        lint v, w; cin >> v >> w;
        item_list_former_half.at(i) = {v, w};
    }
    range(i, 0, num_items_latter_half) {
        lint v, w; cin >> v >> w;
        item_list_latter_half.at(i) = {v, w};
    }
    // enumerate latter half
    vec<plint> possibilities_choices_latter_half;
    range(state, 0, 1 << num_items_latter_half) {
        lint sum_score = 0, sum_weight = 0;
        range(i, 0, num_items_latter_half) {
            if ((state >> i) & 1) {
                sum_score += item_list_latter_half.at(i).first;
                sum_weight += item_list_latter_half.at(i).second;
            }
        }
        possibilities_choices_latter_half.emplace_back(sum_score, sum_weight);
    }
    sort(possibilities_choices_latter_half.begin(), possibilities_choices_latter_half.end(),
        [](const plint& a, const plint& b) {return a.second < b.second;});
    // eliminate suboptimal ones
    lint res = 0;
    vec<lint> score_list_good_ones, weight_list_good_ones;
    lint cur_max_score = 0;
    for (const plint& possibility : possibilities_choices_latter_half) {
        lint sum_score, sum_weight;
        tie(sum_score, sum_weight) = possibility;
        if (sum_score > cur_max_score) {
            score_list_good_ones.emplace_back(sum_score);
            weight_list_good_ones.emplace_back(sum_weight);
            cur_max_score = sum_score;
            if (sum_weight <= W) res = max(res, sum_score);
        }
    }
    // enumerate former half
    range(state, 0, 1 << num_items_former_half) {
        lint sum_score = 0, sum_weight = 0;
        range(i, 0, num_items_former_half) {
            if ((state >> i) & 1) {
                sum_score += item_list_former_half.at(i).first;
                sum_weight += item_list_former_half.at(i).second;
            }
            if (sum_weight > W) continue;
            lint rest_weight = W - sum_weight;
            auto it_ub = upper_bound(weight_list_good_ones.begin(), weight_list_good_ones.end(), rest_weight);
            if (it_ub != weight_list_good_ones.begin()) {
                lint rest_sum_score = score_list_good_ones.at(it_ub - weight_list_good_ones.begin() - 1);
                res = max(res, sum_score + rest_sum_score);
            } else {
                res = max(res, sum_score);
            }
        }
    }
    cout << res << "\n";
}