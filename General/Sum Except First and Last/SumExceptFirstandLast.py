class Solution:
    def sumExceptFirstAndLast(self, arr):
        return sum(arr[1:-1]) if len(arr) > 2 else 0

if __name__ == "__main__":
    arr = [5, 24, 39, 60, 15, 28, 27, 40, 50, 90]
    s1 = Solution()
    print(s1.sumExceptFirstAndLast(arr))