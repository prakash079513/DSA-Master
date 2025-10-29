#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> ans;

    void dfs(string word, string &start, 
             unordered_map<string, vector<string>> &parent,
             vector<string> &path) {
        if (word == start) {
            reverse(path.begin(), path.end());
            ans.push_back(path);
            reverse(path.begin(), path.end());
            return;
        }
        for (auto &p : parent[word]) {
            path.push_back(p);
            dfs(p, start, parent, path);
            path.pop_back();
        }
    }

    vector<vector<string>> findLadders(string startWord, string targetWord, vector<string>& wordList) {
        unordered_set<string> st(wordList.begin(), wordList.end());
        vector<vector<string>> emptyRes;
        if (!st.count(targetWord)) return emptyRes;

        unordered_map<string, vector<string>> parent;
        queue<string> q;
        q.push(startWord);

        unordered_set<string> visited;
        visited.insert(startWord);

        bool found = false;

        while (!q.empty()) {
            int size = q.size();
            unordered_set<string> thisLevel;

            while (size--) {
                string word = q.front(); 
                q.pop();

                string original = word;

                for (int i = 0; i < word.size(); i++) {
                    char old = word[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        word[i] = c;

                        if (st.count(word)) {
                            if (!visited.count(word)) {
                                q.push(word);
                                thisLevel.insert(word);
                                parent[word].push_back(original);
                            }
                            else if (thisLevel.count(word)) {
                                parent[word].push_back(original);
                            }
                            if (word == targetWord) found = true;
                        }
                    }
                    word[i] = old;
                }
            }

            for (auto &w : thisLevel) visited.insert(w);
            if (found) break;
        }

        if (!found) return emptyRes;

        vector<string> path;
        path.push_back(targetWord);
        dfs(targetWord, startWord, parent, path);

        return ans;
    }
};

int main() {
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};
    string startWord = "hit", targetWord = "cog";
    Solution s1;
    auto res = s1.findLadders(startWord, targetWord, wordList);
    for (auto &v : res) {
        for (auto &s : v) cout << s << " ";
        cout << "\n";
    }
    return 0;
}
