#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    i64 ans = 0;
    int cnt = 0;
    for (auto x : s) {
        if (x == 'a') {
            cnt++;
        } else if (x == 'k') {
            ans += cnt;
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