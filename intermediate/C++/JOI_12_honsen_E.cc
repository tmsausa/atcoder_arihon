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

vec<lint> compress(vec<int>& ll, vec<int>& ur, int w) {
    vec<lint> result;
    int N = ll.size();
    range(i, 0, N) range(d, -1, 2) {
        int tll = ll.at(i) + d, tur = ur.at(i) + d;
        if (0 <= tll and tll <= w) result.emplace_back(tll);
        if (0 <= tur and tur <= w) result.emplace_back(tur);
    }
    sort(result.begin(), result.end());
    result.erase(unique(result.begin(), result.end()), result.end());
    range(i, 0, N) {
        ll[i] = lower_bound(result.begin(), result.end(), ll[i]) - result.begin();
        ur[i] = lower_bound(result.begin(), result.end(), ur[i]) - result.begin();
    }
    return result;
}

int main() {
    cin.tie(0); cout.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    const int MAX_VALUE_COORD = 1e6;
    int N, K; cin >> N >> K;
    vec<int> ll_x(N, 0), ll_y(N, 0), ll_d(N, 0), ur_x(N, 0), ur_y(N, 0), ur_d(N, 0);
    range(i, 0, N) {
        int x1, y1, d1, x2, y2, d2;
        cin >> x1 >> y1 >> d1 >> x2 >> y2 >> d2;
        x2--; y2--; d2--;
        ll_x[i] = x1;
        ll_y[i] = y1;
        ll_d[i] = d1;
        ur_x[i] = x2;
        ur_y[i] = y2;
        ur_d[i] = d2;
    }
    vec<lint> map_x = compress(ll_x, ur_x, MAX_VALUE_COORD);
    vec<lint> map_y = compress(ll_y, ur_y, MAX_VALUE_COORD);
    vec<lint> map_d = compress(ll_d, ur_d, MAX_VALUE_COORD);
    int num_fish[map_x.size()][map_y.size()][map_d.size()];
    memset(num_fish, 0, sizeof(num_fish));
    range(n, 0, N) range(x, ll_x[n], ur_x[n] + 1) range(y, ll_y[n], ur_y[n] + 1) range(d, ll_d[n], ur_d[n] + 1) num_fish[x][y][d] += 1;
    lint ans = 0;
    range(i, 0, map_x.size() - 1) range(j, 0, map_y.size() - 1) range(k, 0, map_d.size() - 1) {
        if (num_fish[i][j][k] >= K) ans += (map_x[i + 1] - map_x[i]) * (map_y[j + 1] - map_y[j]) * (map_d[k + 1] - map_d[k]);
    }
    cout << ans << "\n";
}