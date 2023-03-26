#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    std::vector<int> s(n + 1);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        s[i + 1] = s[i] ^ a[i];
    }

    int ans = 0;

    for (int i = 29; i >= 0; i--) {
        auto f = [&](int x) {
            return x >> i << i & (ans | 1 << i);
        };

        int now = f(s[0]), cnt = 0;
        for (int j = 1; j <= n && cnt < m - 1; j++) {
            int u = f(s[j]);
            if (u == (now ^ (ans | 1 << i))) {
                cnt++;
                now = u;
            }
        }
        int u = f(s[n]);
        if (cnt == m - 1 && u == (now ^ (ans | 1 << i))) {
            ans |= 1 << i;
        }
    }

    std::cout << ans << "\n";
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