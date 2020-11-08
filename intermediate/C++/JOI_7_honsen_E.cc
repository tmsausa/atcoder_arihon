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
    int w, h, n; cin >> w >> h >> n;
    int lower_left_x[n], upper_right_x[n];
    int lower_left_y[n], upper_right_y[n];
    range(i, 0, n) {
        int x0, y0, x1, y1;
        cin >> x0 >> y0 >> x1 >> y1;
        x1--; y1--;
        lower_left_x[i] = x0;
        lower_left_y[i] = y0;
        upper_right_x[i] = x1;
        upper_right_y[i] = y1;
    }
    auto compress = [&](int *lower_left, int *upper_right, int width) {
        vec<int> result;
        range(i, 0, n) range(d, -1, 2) {
            int ll = lower_left[i] + d, ur = upper_right[i] + d;
            if (0 <= ll and ll < width)
                result.emplace_back(ll);
            if (0 <= ur and ur < width)
                result.emplace_back(ur);
        }
        sort(result.begin(), result.end());
        result.erase(unique(result.begin(), result.end()), result.end());
        range(i, 0, n) {
            lower_left[i] = lower_bound(result.begin(), result.end(), lower_left[i]) - result.begin();
            upper_right[i] = lower_bound(result.begin(), result.end(), upper_right[i]) - result.begin();
        }
        return result.size();
    };
    int MAX_X = compress(lower_left_x, upper_right_x, w);
    int MAX_Y = compress(lower_left_y, upper_right_y, h);
    // lint MAX_X = x_list.size(), MAX_Y = y_list.size();
    // vec<vec<int>> is_sealed(MAX_X, vec<int>(MAX_Y, 0));
    vec<vec<int>> is_sealed(MAX_X, vec<int>(MAX_Y, 0));
    // memset(is_sealed, 0, sizeof(is_sealed));
    range(k, 0, n) {
        int ll_x = lower_left_x[k], ur_x = upper_right_x[k];
        range(j, lower_left_y[k], upper_right_y[k] + 1) is_sealed[ll_x][j] += 1;
        if (ur_x + 1 < MAX_X) 
            range(j, lower_left_y[k], upper_right_y[k] + 1) is_sealed[ur_x + 1][j] -= 1;
    }
    range(j, 0, MAX_Y) range(i, 1, MAX_X)
        is_sealed[i][j] += is_sealed[i - 1][j];
    lint ans = 0;
    // vec<vec<bool>> is_visited(MAX_X, vec<bool>(MAX_Y, false));
    vec<lint> dx = {-1, 1, 0, 0}, dy = {0, 0, -1, 1};
    range(i, 0, MAX_X) range(j, 0, MAX_Y) {
        if (is_sealed[i][j]) continue;
        ans += 1;
        queue<pint> que;
        que.emplace(i, j);
        while (!que.empty()) {
            int x, y;
            tie(x, y) = que.front();
            que.pop();
            range(k, 0, 4) {
                int nx = x + dx.at(k), ny = y + dy.at(k);
                if (nx < 0 or nx >= MAX_X or ny < 0 or ny >= MAX_Y) continue;
                else if (is_sealed[nx][ny]) continue;
                que.emplace(nx, ny);
                is_sealed[nx][ny] = true;
            }
        }
    }
    cout << ans << '\n';
}