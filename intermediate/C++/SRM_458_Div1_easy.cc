// TODO: rewrite
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

struct BouncingBalls {
    double expectedBounces(vector<int> x, int t) {
        double ret = 0.0;
        int n = x.size();
        sort(x.begin(), x.end());
        range(bit, 0, (1 << n)) {//0:right,1:left
            range(i, 0, n - 1) {
                for (int j = i + 1; j < n; j++) {
                    if (!((1 << i) & bit) && ((1 << j) & bit)) {
                        if (x[j] - x[i] <= t * 2)ret += 1.0;
                    }
                }
            }
        }
        ret /= (1 << n);
        return ret;
    }
};
