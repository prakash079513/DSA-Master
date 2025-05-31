class Solution:
    def countPairs(self, mat1, mat2, x):
        n = len(mat1)
        elements = set()
        count = 0

        for i in range(n):
            for j in range(n):
                elements.add(mat2[i][j])

        for i in range(n):
            for j in range(n):
                if x - mat1[i][j] in elements:
                    count += 1

        return count

# Example usage
if __name__ == "__main__":
    n = 3
    x = 21
    mat1 = [[1, 5, 6], [8, 10, 11], [15, 16, 18]]
    mat2 = [[2, 4, 7], [9, 10, 12], [13, 16, 20]]

    sol = Solution()
    result = sol.countPairs(mat1, mat2, x)
    print(result)
