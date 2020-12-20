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
    const lint MAX_NUM = 2e5 + 1;
    const lint bucket_size = (lint)ceil(sqrt(MAX_NUM));
    const lint bucket_num = MAX_NUM / bucket_size + (MAX_NUM % bucket_size ? 1 : 0);
    vec<vec<bool>> bucket(bucket_num, vec<bool>(bucket_size, false));
    vec<lint> num_items_in_bucket(bucket_num, 0);
    lint Q; cin >> Q;
    range(_, 0, Q) {
        lint T, X; cin >> T >> X;
        if (T == 1) {
            lint bucket_idx = X / bucket_size;
            lint idx = X % bucket_size;
            bucket.at(bucket_idx).at(idx) = true;
            num_items_in_bucket.at(bucket_idx) += 1;
        } else {
            lint cur_sum = 0;
            lint bucket_idx = 0;
            while (bucket_idx < bucket_num and cur_sum + num_items_in_bucket.at(bucket_idx) < X) {
                cur_sum += num_items_in_bucket.at(bucket_idx);
                bucket_idx += 1;
            }
            lint idx = 0;
            while (idx < bucket_size and cur_sum + bucket.at(bucket_idx).at(idx) < X) {
                cur_sum += bucket.at(bucket_idx).at(idx);
                idx += 1;
            }
            cout << bucket_idx * bucket_size + idx << "\n";
            bucket.at(bucket_idx).at(idx) = false;
            num_items_in_bucket.at(bucket_idx) -= 1;
        }
    }
}