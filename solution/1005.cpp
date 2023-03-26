#include <bits/stdc++.h>

using i64 = long long;

struct Min {
    i64 v;
    Min(i64 v = 1E18) : v(v) {}
    
    friend Min operator+(const Min &x, const Min &y) {
        return std::min(x.v, y.v);
    }
    void apply(int y) {
        this->v += y;
    }
};

void apply(int &x, int y) {
    x += y;
}

template<typename T, typename U>
struct LazySegmentTree {
    const int n;
    std::vector<T> a;
    std::vector<U> g;
    LazySegmentTree(int n) : n(n), a(4 * n, Min()), g(4 * n) {}
    LazySegmentTree(const std::vector<T> &b) : LazySegmentTree(int(b.size())) {
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (l == r) {
                a[p] = b[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m + 1, r);
            pull(p);
        };
        build(1, 0, n - 1);
    }
    void pull(int p) {
        a[p] = a[2 * p] + a[2 * p + 1];
    }
    void push(int p) {
        apply(2 * p, g[p]);
        apply(2 * p + 1, g[p]);
        g[p] = U();
    }
    void apply(int p, const U &v) {
        a[p].apply(v);
        ::apply(g[p], v);
    }
    void rangeApply(int p, int l, int r, int x, int y, const U &v) {
        if (x <= l && r <= y) {
            apply(p, v);
            return;
        }
        push(p);
        int m = (l + r) / 2;
        if (m >= x) rangeApply(2 * p, l, m, x, y, v); 
        if (m < y) rangeApply(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }
    void rangeApply(int x, int y, const U &v) {
        rangeApply(1, 0, n - 1, x, y, v);
    }
    T rangeQuery(int p, int l, int r, int x, int y) {
        if (x > r || y < l) {
            return T();
        }  
        if (x <= l && r <= y) {
            return a[p];
        }
        push(p);
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m + 1, r, x, y);
    }
    T rangeQuery(int x, int y) {  
        return rangeQuery(1, 0, n - 1, x, y);
    }
    void modify(int p, int l, int r, int x, const T &v) {
        if (l == r) {
            a[p] = v;
            return;
        }
        push(p);
        int m = (l + r) / 2;
        if (x <= m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m + 1, r, x, v);
        }
        pull(p);
    }
    void modify(int x, const T &v) {
        modify(1, 0, n - 1, x, v);
    }
};

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    LazySegmentTree<Min, int> seg(n + 1);
    std::vector<i64> dp(n + 1);
    std::vector<int> stk;
    for (int i = 1; i <= n; i++) {
        while (!stk.empty() && a[stk.back()] <= a[i]) {
            int x = stk.size() == 1 ? 1 : stk[int(stk.size()) - 2] + 1;
            seg.rangeApply(x, stk.back(), a[i] - a[stk.back()]);
            stk.pop_back();
        }
        stk.push_back(i);
        seg.modify(i, dp[i - 1] + a[i]);
        dp[i] = seg.rangeQuery(std::max(1, i - k + 1), i).v;
    }

    std::cout << dp[n] << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }   

    return 0;
}