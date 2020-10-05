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

struct Edge {
    lint s, e, cost, time;
    Edge(lint s, lint e, lint cost, lint time) {
        this->s = s;
        this->e = e;
        this->cost = cost;
        this->time = time;
    }
};

struct UnionFind {
private:
    vector<int> parent;
    vector<int> num_components;

public:
    UnionFind(int n) {
        num_components.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent.emplace_back(i);
        }
    }

    int root(int x) {
        if (parent.at(x) == x) return x;
        parent.at(x) = root(parent.at(x));
        return parent.at(x);
    }

    bool is_connected(int x, int y) {
        return root(x) == root(y);
    }

    int num_connected(int x) {
        return num_components.at(root(x));
    }

    void unite(int x, int y) {
        int root_x = root(x);
        int root_y = root(y);
        if (root_x == root_y) return;
        int rank_x = num_components.at(root_x);
        int rank_y = num_components.at(root_y);
        if (rank_x < rank_y) {
            parent.at(root_x) = root_y;
            num_components.at(root_y) += rank_x;
        }
        else {
            parent.at(root_y) = root_x;
            num_components.at(root_x) += rank_y;
        }
    }
};

using ld = long double;

ld kruskal(lint num_vertices, ld target, vec<Edge>& road_list) {
    sort(road_list.begin(), road_list.end(),
        [&](const Edge& a, const Edge& b) {
            return a.cost - target * a.time < b.cost - target * b.time;});
    UnionFind uf(num_vertices);
    ld total_cost = 0;
    for (const Edge& road : road_list) {
        ld cost = road.cost - target * road.time;
        if (!uf.is_connected(road.s, road.e) or cost < 0.) {
            uf.unite(road.s, road.e);
            total_cost += cost;
        }
    }
    return total_cost;
}

int main() {
    cin.tie(0); cout.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    lint N, M; cin >> N >> M;
    vec<Edge> road_list;
    range(i, 0, M) {
        lint s, e, c, t; cin >> s >> e >> c >> t;
        road_list.emplace_back(s, e, c, t);
    }
    ld lo = 0, hi = 1e6;
    range(_, 0, 100) {
        // cout << lo << " " << hi << "\n";
        ld mid = (lo + hi) / 2;
        ld total_cost = kruskal(N, mid, road_list);
        if (total_cost <= 0) hi = mid;
        else lo = mid;
    }
    cout << lo << "\n";
}
