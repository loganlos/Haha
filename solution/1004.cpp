#include <bits/stdc++.h>

using i64 = long long;

struct DSU {
    std::vector<int> f, max;
    DSU(std::vector<int> &h) : f(h.size()), max(h) {
        std::iota(f.begin(), f.end(), 0);
    }
    
    int find(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        max[x] = std::max(max[x], max[y]);
        f[y] = x;
        return true;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int maximum(int x) {
        return max[find(x)];
    }
};

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> h(n);
    for (int i = 0; i < n; i++) {
        std::cin >> h[i];
    }

    std::vector<std::array<int, 3>> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--, v--;
        edges[i] = {u, v, w};
    }

    std::sort(edges.begin(), edges.end(), [&](std::array<int, 3> x, std::array<int, 3> y) {
        return x[2] < y[2];
    });

    int q;
    std::cin >> q;

    std::vector<std::array<int, 2>> events(q);
    for (int i = 0; i < q; i++) {
        std::cin >> events[i][0] >> events[i][1];
        events[i][1]--;
    }

    std::vector<int> p(q);
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(), [&](int i, int j) {
        return events[i][0] < events[j][0];
    });

    DSU dsu(h);
    std::vector<int> ans(q);
    for (int i = 0, j = 0; i < q; i++) {
        int x = p[i];
        while (j < m && edges[j][2] <= events[x][0]) {
            dsu.merge(edges[j][0], edges[j][1]);
            j++;
        }
        ans[x] = dsu.maximum(events[x][1]);
    }

    for (auto x : ans) {
        std::cout << x << "\n";
    }
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