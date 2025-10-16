# Flood Fill Algorithm

Author: [Prakash JC](https://prakash079513.github.io)

## **Problem Statement**

You are given a 2D grid `image` of integers where each integer represents a pixel color.

You are also given a starting pixel `(sr, sc)` and a color value `newColor`.

Perform a **Flood Fill** operation such that:

- Starting from `(sr, sc)`, replace the color of that pixel and all **4-directionally connected pixels** having the **same original color** with `newColor`.
- The connections extend recursively or iteratively until no more adjacent pixels of the original color remain.

---

## **Using Depth-First Search (DFS)**

### **Approach**

- Capture the **starting color** from `(sr, sc)`.
- If the starting color is already equal to `newColor`, no operation is needed.
- Apply DFS starting from `(sr, sc)`:
  - Change the color of the current pixel to `newColor`.
  - Recursively visit its **4-directional neighbors** (up, down, left, right).
  - Only recurse into pixels that are **within bounds** and **match the original color**.
- No visited array is required.
- Continue until all connected pixels of the same color are updated.

### **Code**

```cpp
void dfs(int row, int col, vector<vector<int>> &image, int newColor, int initColor) {
    int n = image.size();
    int m = image[0].size();
    image[row][col] = newColor;

    int delRow[] = {-1, 0, 1, 0};
    int delCol[] = {0, 1, 0, -1};

    for (int i = 0; i < 4; i++) {
        int r = row + delRow[i];
        int c = col + delCol[i];
        if (r >= 0 && r < n && c >= 0 && c < m && image[r][c] == initColor) {
            dfs(r, c, image, newColor, initColor);
        }
    }
}

vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor) {
    int initColor = image[sr][sc];
    if (initColor == newColor) return image;  // no need to fill

    dfs(sr, sc, image, newColor, initColor);
    return image;
}
```

### **Complexity Analysis**

**Time Complexity:** `O(n * m)` - Each pixel is visited at most once during the DFS traversal.

**Space Complexity:** `O(n * m)` - Due to recursive call stack (worst-case when all pixels are of the same color).

---

## **Using Breadth-First Search (BFS)**

### **Approach**

- Use an iterative **BFS** approach with a queue instead of recursion.
- Store the **starting color** and enqueue `(sr, sc)`.
- While the queue is not empty:
  - Dequeue the front pixel `(r, c)` and color it with `newColor`.
  - Check its **4-directional neighbors**.
  - For each valid neighbor that matches the starting color, enqueue it and color it.
- Repeat until the queue is empty.

### **Code**

```cpp
vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor) {
    int initColor = image[sr][sc];
    if (initColor == newColor) return image;  // already filled

    int n = image.size();
    int m = image[0].size();
    queue<pair<int, int>> q;
    q.push({sr, sc});
    image[sr][sc] = newColor;

    int delRow[] = {-1, 0, 1, 0};
    int delCol[] = {0, 1, 0, -1};

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int rn = r + delRow[i];
            int cn = c + delCol[i];

            if (rn >= 0 && rn < n && cn >= 0 && cn < m && image[rn][cn] == initColor) {
                image[rn][cn] = newColor;
                q.push({rn, cn});
            }
        }
    }
    return image;
}
```

### **Complexity Analysis**

**Time Complexity:** `O(n * m)` - Each pixel is visited once and each neighbor is checked a constant number of times.

**Space Complexity:** `O(n * m)` - Due to the queue storing at most all pixels in the worst case.

---

THE END
