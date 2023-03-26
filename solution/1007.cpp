#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<std::array<int, 2>> events(2 * n);
    for (int i = 0; i < n; i++) {
        int l, r;
        std::cin >> l >> r;
        events[2 * i] = {l, i + 1};
        events[2 * i + 1] = {r + 1, -(i + 1)};
    }

    std::sort(events.begin(), events.end());

    std::vector<int> dp(1 << k, -1), id(k, -1);
    dp[0] = 0;
    for (int i = 0; i < 2 * n; i++) {
        int len = i == 2 * n - 1 ? 0 : events[i + 1][0] - events[i][0];
        if (events[i][1] > 0) {
            int p = -1;
            for (int j = 0; j < k; j++) {
                if (id[j] == -1) {
                    id[j] = events[i][1];
                    p = j;
                    break;
                }
            }
            assert(p != -1);
            for (int mask = (1 << k) - 1; mask >= 0; mask--) {
                if (mask >> p & 1) {
                    if (dp[mask ^ 1 << p] != -1) {
                        dp[mask] = dp[mask ^ 1 << p] + len * __builtin_parity(mask);
                    }
                } else {
                    if (dp[mask] != -1) {
                        dp[mask] += len * __builtin_parity(mask);
                    }
                }
            }
        } else {
            int p = -1;
            for (int j = 0; j < k; j++) {
                if (id[j] == -events[i][1]) {
                    id[j] = -1;
                    p = j;
                    break;
                }
            }
            assert(p != -1);
            for (int mask = 0; mask < 1 << k; mask++) {
                if (mask >> p & 1) {
                    dp[mask] = -1;
                } else {
                    int v = -1;
                    if (dp[mask] != -1) {
                        v = dp[mask] + len * __builtin_parity(mask);
                    }
                    if (dp[mask ^ 1 << p] != -1) {
                        v = (dp[mask] == -1 ? dp[mask ^ 1 << p] : std::max(dp[mask], dp[mask ^ 1 << p])) + len * __builtin_parity(mask);
                    }
                    dp[mask] = v;
                }
            }
        }
    }

    std::cout << dp[0] << "\n";
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