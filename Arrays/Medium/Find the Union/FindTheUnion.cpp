#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findUnion(vector<int>& arr1, vector<int>& arr2) {
        unordered_set<int> unionSet;

        // Insert all elements from arr1 into the set
        for (int num : arr1) {
            unionSet.insert(num);
        }

        // Insert all elements from arr2 into the set
        for (int num : arr2) {
            unionSet.insert(num);
        }

        // Convert set to vector
        vector<int> unionVec(unionSet.begin(), unionSet.end());
        return unionVec;
    }
};

int main() {
    // Example usage
    vector<int> arr1 = {1, 2, 3, 4, 5};
    vector<int> arr2 = {3, 4, 5, 6, 7};

    Solution s;
    vector<int> unionArray = s.findUnion(arr1, arr2);

    // Output the union array
    cout << "Union of arrays: ";
    for (int num : unionArray) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
