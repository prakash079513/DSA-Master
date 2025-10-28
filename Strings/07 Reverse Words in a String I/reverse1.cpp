#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        // Step 1: Trim leading and trailing spaces
        int n = s.size();
        int start = 0, end = n - 1;
        while (start < n && s[start] == ' ') start++;
        while (end >= 0 && s[end] == ' ') end--;

        if (start > end) return "";  // if string is all spaces

        s = s.substr(start, end - start + 1);
        n = s.size();

        // Step 2: Reverse the whole string
        reverse(s.begin(), s.end());

        // Step 3: Remove extra spaces and normalize word spacing
        int write = 0;
        for (int read = 0; read < n; read++) {
            if (s[read] != ' ') {
                s[write++] = s[read];
            } else if (write > 0 && s[write - 1] != ' ') {
                s[write++] = ' ';
            }
        }
        s.resize(write);  // remove trailing space if any

        // Step 4: Reverse each individual word
        int wordStart = 0;
        for (int i = 0; i <= write; i++) {
            if (i == write || s[i] == ' ') {
                reverse(s.begin() + wordStart, s.begin() + i);
                wordStart = i + 1;
            }
        }

        return s;
    }
};

int main() {
    string s = "  i have    given       spaces  ";
    Solution sol;
    cout << sol.reverseWords(s);
    return 0;
}
