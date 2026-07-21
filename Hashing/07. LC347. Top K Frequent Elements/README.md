### **347. Top K Frequent Elements**

Author: Prakash JC

### Problem Statement

Given an integer array `nums` and an integer `k`, return the `k` most frequent elements.

You may return the answer in any order.

---

### Key Takeaway

- first count frequencies, then extract the top `k` elements using an efficient data structure.

---

### Brute Force Approach

#### Approach

- Traverse the array and count the frequency of every element using a hashmap.
- Repeatedly find the element with the highest remaining frequency.
- Add it to the answer.
- Remove it from the hashmap.
- Repeat until `k` elements are collected.

```cpp
 vector<int> f(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    vector<int> ans;

    for (int x : nums)
        freq[x]++;

    for (int i = 0; i < k; i++) {
        int maxi = 0;
        int num = 0;

        for (auto it : freq) {
            if (it.second > maxi) {
                maxi = it.second;
                num = it.first;
            }
        }

        ans.push_back(num);
        freq.erase(num);
    }

    return ans;
}
```

**Time Complexity:** `O(nk)`

**Space Complexity:** `O(n)`

---

### Better Approach – Sorting

#### Key Observation

- Once frequencies are known, sorting the elements by frequency allows us to pick the first `k` elements.

#### Approach

- Count the frequency of each element using a hashmap.
- Store each `(frequency, element)` pair in a vector.
- Sort the vector in descending order of frequency.
- Return the first `k` elements.

### Code

```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;

    for (int num : nums)
        freq[num]++;

    vector<pair<int, int>> v;

    for (auto it : freq)
        v.push_back({it.second, it.first});

    sort(v.begin(), v.end(), greater<pair<int, int>>());

    vector<int> ans;

    for (int i = 0; i < k; i++)
        ans.push_back(v[i].second);

    return ans;
}
```

**Time Complexity:** `O(n log n)`

**Space Complexity:** `O(n)`

---

### Min Heap

#### Key Observation

- We only need the top `k` frequent elements.
- A min heap of size `k` keeps only the `k` highest frequencies.
- Whenever heap size exceeds `k`, remove the smallest frequency.

#### Approach

- Count frequencies using a hashmap.
- Create a min heap storing `(frequency, element)`.
- Traverse the hashmap.
- Push every `(frequency, element)` into the heap.
- If heap size becomes greater than `k`, pop the top element.
- After processing all elements, extract all elements from the heap.

### Code

```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;

    for (int num : nums)
        freq[num]++;

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    for (auto it : freq) {
        pq.push({it.second, it.first});

        if (pq.size() > k)
            pq.pop();
    }

    vector<int> ans;

    while (!pq.empty()) {
        ans.push_back(pq.top().second);
        pq.pop();
    }

    return ans;
}
```

**Time Complexity:** `O(n log k)`

**Space Complexity:** `O(n)`

---

### Optimal Approach – Bucket Sort

#### Key Observation

- Frequency of any element can never exceed `n`.
- Create buckets where index represents the frequency.
- Store elements having the same frequency in the same bucket.
- Traverse buckets from highest frequency to lowest until `k` elements are collected.

#### Approach

- Count frequencies using a hashmap.
- Create `n + 1` buckets.
- Place every element into the bucket corresponding to its frequency.
- Traverse buckets from back to front.
- Collect elements until `k` elements are obtained.

### Code

```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;

    for (int num : nums)
        freq[num]++;

    vector<vector<int>> bucket(nums.size() + 1);

    for (auto it : freq)
        bucket[it.second].push_back(it.first);

    vector<int> ans;

    for (int i = bucket.size() - 1; i >= 0 && ans.size() < k; i--) {
        for (int num : bucket[i]) {
            ans.push_back(num);

            if (ans.size() == k)
                break;
        }
    }

    return ans;
}
```

**Time Complexity:** `O(n)`

**Space Complexity:** `O(n)`

---

### Quickselect (Hoare's Selection Algorithm)

#### Key Observation

- We only need the **top `k` frequent elements**, not the entire array sorted.
- Sorting all elements takes `O(n log n)`.
- Quickselect places one element in its **correct sorted position** without fully sorting the array.
- After partitioning:
  - All elements on the left have **lower frequency**.
  - All elements on the right have **higher or equal frequency**.
- We only recurse into the side that contains our answer, reducing the average time complexity to `O(n)`.

#### Approach

- Count the frequency of every element using a hashmap.
- Store all unique elements in a separate array `unique`.
- We want the element whose position would be `n - k` if the array were sorted by frequency.
- Perform Quickselect on the `unique` array.
- During each partition:
  - Choose a pivot.
  - Rearrange elements so that:
    - Lower frequency elements are placed on the left.
    - Higher frequency elements are placed on the right.
  - The pivot reaches its correct position.
- Compare the pivot's position with `n - k`.
  - If equal, the last `k` elements are the answer.
  - If the pivot lies before `n - k`, recurse on the right half.
  - Otherwise recurse on the left half.
- Once the pivot reaches position `n - k`, return the last `k` elements.

#### Partition (Lomuto Partition Scheme)

The partition step is exactly the same idea used in Quick Sort.

Steps:

- Choose a pivot element.
- Swap the pivot with the last element.
- Maintain a pointer `storeIndex` starting from the left.
- Traverse the array:
  - If an element has **smaller frequency** than the pivot,
    - Swap it with `storeIndex`.
    - Increment `storeIndex`.
- Finally, swap the pivot back to `storeIndex`.
- The pivot is now in its correct sorted position.
- Return `storeIndex`.

After partition:

```
Lower Frequency | Pivot | Higher / Equal Frequency
```

Only one side needs further processing.

#### Why is it Faster than Quick Sort?

Quick Sort recursively sorts **both** halves after every partition.

```
Left Half
     \
      Pivot
     /
Right Half

Process both halves
```

Quickselect only processes **one** half.

```
Left Half
     \
      Pivot
     /
Right Half

Only recurse into the half containing the answer.
```

Since half of the work is discarded after every partition on average, the expected running time becomes linear.

#### Code

```cpp
class Solution {
public:
    unordered_map<int, int> freq;

    int partition(vector<int>& unique, int left, int right, int pivotIndex) {
        int pivotFreq = freq[unique[pivotIndex]];

        swap(unique[pivotIndex], unique[right]);

        int storeIndex = left;

        for (int i = left; i < right; i++) {
            if (freq[unique[i]] < pivotFreq) {
                swap(unique[storeIndex], unique[i]);
                storeIndex++;
            }
        }

        swap(unique[storeIndex], unique[right]);

        return storeIndex;
    }

    void quickSelect(vector<int>& unique, int left, int right, int kSmallest) {
        if (left >= right)
            return;

        int pivotIndex = left + rand() % (right - left + 1);

        pivotIndex = partition(unique, left, right, pivotIndex);

        if (pivotIndex == kSmallest)
            return;

        if (pivotIndex < kSmallest)
            quickSelect(unique, pivotIndex + 1, right, kSmallest);
        else
            quickSelect(unique, left, pivotIndex - 1, kSmallest);
    }

    vector<int> topKFrequent(vector<int>& nums, int k) {

        for (int num : nums)
            freq[num]++;

        vector<int> unique;

        for (auto it : freq)
            unique.push_back(it.first);

        int n = unique.size();

        quickSelect(unique, 0, n - 1, n - k);

        return vector<int>(unique.begin() + (n - k), unique.end());
    }
};
```

**Time Complexity:** `O(n)` average, `O(n²)` worst case

**Space Complexity:** `O(n)`

---

THE END
