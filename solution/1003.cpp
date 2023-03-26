#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    std::string s;
    std::cin >> s;

    if (std::count(s.begin(), s.end(), '0') == 0) {
        std::cout << "0\n";
        return;
    }

    int lo = 1, hi = n;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        int cnt = 0, end = -1;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0' && end < i) {
                cnt++;
                end = i + mid - 1;
            }
        }
        if (cnt <= k) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    std::cout << lo << "\n";
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