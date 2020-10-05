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
    lint N; cin >> N;
    vec<lint> A_list(N);
    range(i, 0, N) cin >> A_list.at(i);
    range(i, 0, N) A_list.emplace_back(A_list.at(i));
    lint sum = 0;
    range(i, 0, N) sum += A_list.at(i);
    // [lo, hi)
    lint lo = 0, hi = 1e14 + 1;
    while (hi - lo > 1) {
        // cout << lo << " " << hi << "\n";
        bool impossible = true;
        lint mid = (lo + hi) / 2;
        lint j = 0, k = 0;
        lint p1 = 0, p2 = 0, p3 = 0;
        while (p1 < mid && j < N - 1) {
            p1 += A_list.at(j);
            j += 1;
            k += 1;
        }
        while (p2 < mid and k < N - 1) {
            p2 += A_list.at(k);
            k += 1;
        }
        range(i, k, N) p3 += A_list.at(i);
        assert(p1 + p2 + p3 == sum);
        if (p1 >= mid and p2 >= mid and p3 >= mid) {
            // possible
            lo = mid;
            continue;
        }
        range(i, 1, N) {
            lint end = N - 1 + i;
            p1 -= A_list.at(i - 1);
            p3 += A_list.at(i - 1);
            while (p1 < mid && j < k) {
                p1 += A_list.at(j);
                p2 -= A_list.at(j);
                j += 1;
            }
            while (p2 < mid && k < end) {
                p2 += A_list.at(k);
                p3 -= A_list.at(k);
                k += 1;
            }
            assert(p1 + p2 + p3 == sum);
            if (p1 >= mid and p2 >= mid and p3 >= mid) {
                lo = mid;
                impossible = false;
                break;
            }
        }
        if (impossible) hi = mid;
    }
    cout << lo << "\n";
}