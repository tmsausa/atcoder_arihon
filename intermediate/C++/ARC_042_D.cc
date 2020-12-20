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
    lint X, P, A, B; cin >> X >> P >> A >> B;
    if (X == 1) {
        cout << 1 << "\n";
        return 0;
    }
    lint m = (lint)ceil(sqrt(P));
    unordered_map<lint, lint> remnant_to_power;
    remnant_to_power.emplace(1, 0);
    lint cur_mul = 1;
    range(i, 0, m) {
        cur_mul = cur_mul * X % P;
        remnant_to_power.emplace(cur_mul, i + 1);
    }
    // cout << m << "\n";
    // cout << remnant_to_power << "\n";
    lint R = pow(cur_mul % P, P - 2, P);
    assert(R * cur_mul % P == 1);

    auto exists = [&](lint Y) {
        if (remnant_to_power.find(Y) != remnant_to_power.end() and remnant_to_power.at(Y) >= A and remnant_to_power.at(Y) <= B) return true;
        range(a, 1, m + 1) {
            Y = Y * R % P;
            if (remnant_to_power.find(Y) != remnant_to_power.end() and remnant_to_power.at(Y) + m * a >= A and remnant_to_power.at(Y) + m * a <= B) {
                return true;
            }
        }
        return false;
    };

    const lint threshold = 2e8;
    if (B - A + 1 <= threshold) {
        lint ans = P - 1;
        lint cur_num = pow(X, A, P);
        range(_, A, B + 1) {
            ans = min(cur_num, ans);
            cur_num = cur_num * X % P;
        }
        cout << ans << "\n";
    } else {
        range(Y, 0, P) if (exists(Y)) {
            cout << Y << "\n";
            return 0;
        }
    }
}