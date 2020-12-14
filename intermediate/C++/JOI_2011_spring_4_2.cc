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

template <typename T, typename E>
struct SegmentTree {
private:
    typedef function<T(T, T)> F;
    typedef function<T(T, E)> G;
    int n;
    F merge_func;
    G update_func;
    T identity_item;
    vector<T> nodes;

public:
    SegmentTree(int n_, F merge_func, G update_func, T identity_item, const vector<T>& v=vector<T>()) {
        this->merge_func = merge_func;
        this->update_func = update_func;
        this->identity_item = identity_item;
        nodes_init(n_);
        if (n_ == (int)v.size()) build(n_, v);
    }

    void nodes_init(int n_) {
        n = 1;
        while (n < n_) n *= 2;
        nodes.clear();
        nodes.resize(2 * n - 1, identity_item);
    }

    void build(int n_, const vector<T>& v) {
        for (int i = 0; i < n_; i++) {
            nodes.at(i + n - 1) = v.at(i);
        }
        for (int i = n - 2; i >= 0; i--) {
            nodes.at(i) = merge_func(nodes.at(i * 2 + 1), nodes.at(i * 2 + 2));
        }
    }

    void update(int idx, E value) {
        int node_idx = idx + n - 1;
        nodes.at(node_idx) = update_func(nodes.at(node_idx), value);
        int current_idx = node_idx;
        while (current_idx) {
            current_idx = (current_idx - 1) / 2;
            nodes.at(current_idx) = merge_func(nodes.at(2 * current_idx + 1), nodes.at(2 * current_idx + 2));
        }
    }

    T query(int query_left, int query_right, int cur_idx, int cur_left, int cur_right) {
        if (cur_right <= query_left || query_right <= cur_left) return identity_item;
        if (query_left <= cur_left && cur_right <= query_right) return nodes.at(cur_idx);
        T value_from_left = query(query_left, query_right, 2 * cur_idx + 1, cur_left, (cur_left + cur_right) / 2);
        T value_from_right = query(query_left, query_right, 2 * cur_idx + 2, (cur_left + cur_right) / 2, cur_right);
        return merge_func(value_from_left, value_from_right);
    }

    T query(int query_left, int query_right) {
        return query(query_left, query_right, 0, 0, n);
    }
};

int main() {
    cin.tie(0); cout.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    lint N; cin >> N;
    vec<lint> w_list(N), book_list(N);
    range(i, 0, N) cin >> w_list.at(i);
    range(i, 0, N) cin >> book_list.at(i);
    SegmentTree<lint, lint> dp(N, [](lint a, lint b) {return max(a, b);}, [](lint a, lint b) {return b;}, 0);
    lint cost_sum = 0, max_cost = 0;
    range(i, 0, N) {
        cost_sum += w_list.at(i) * 2;
        book_list.at(i) -= 1;
        dp.update(book_list.at(i), dp.query(0, book_list.at(i)) + w_list.at(book_list.at(i)) * 2);
        max_cost = max(max_cost, dp.query(book_list.at(i), book_list.at(i) + 1));
    }
    cout << cost_sum - max_cost << "\n";
}