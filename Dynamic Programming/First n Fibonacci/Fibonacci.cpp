#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> fibonacci(int n) {
        vector<int> fib(n);
        fib[0] = 0;
        if (n > 1) fib[1] = 1;
        for (int i = 2; i < n; ++i) {
            fib[i] = fib[i - 1] + fib[i - 2];
        }
        return fib;
    }
};

int main() {
    int n;
    cin >> n;
    Solution s1;
    vector<int> result = s1.fibonacci(n);
    for (int num : result) cout << num << " ";
    return 0;
}