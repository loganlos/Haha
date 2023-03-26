#include <bits/stdc++.h>

using i64 = long long;

struct DSU {
    std::vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) {
        std::iota(f.begin(), f.end(), 0);
    }
    int find(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int size(int x) {
        return siz[find(x)];
    }
};

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> h(2 * n - 1);
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

    std::sort(edges.begin(), edges.end(), [&](auto x, auto y) {
        return x[2] < y[2];
    });

    DSU dsu(2 * n - 1);
    int tot = n;
    std::vector<int> weigh(2 * n - 1);
    std::vector parent(2 * n - 1, std::vector(18, -1));
    for (auto [u, v, w] : edges) {
        u = dsu.find(u), v = dsu.find(v);
        if (u != v) {
            dsu.merge(tot, u);
            dsu.merge(tot, v);
            weigh[tot] = w;
            parent[u][0] = parent[v][0] = tot;
            h[tot] = std::max(h[u], h[v]);
            tot++;
        }
    }

    for (int j = 1; j < 18; j++) {
        for (int i = 0; i < tot; i++) {
            if (parent[i][j - 1] != -1) {
                parent[i][j] = parent[parent[i][j - 1]][j - 1];
            }
        }
    }

    int q;
    std::cin >> q;

    while (q--) {
        int p, c;
        std::cin >> p >> c;
        c--;

        for (int i = 17; i >= 0; i--) {
            if (parent[c][i] != -1 && weigh[parent[c][i]] <= p) {
                c = parent[c][i];
            }
        }

        std::cout << h[c] << "\n";
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