#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int d, k, n;
    std::cin >> d >> k >> n;
        
    int times = (n - 1) / d;
    std::cout << times * (d + k) + n - times * d << "\n";
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