class Solution:
    def equilibriumPoint(self, arr):
        total = sum(arr)
        prefSum = 0
        for i in range(len(arr)):
            suffSum = total - prefSum - arr[i]
            if prefSum == suffSum:
                return i
            prefSum += arr[i]
        return -1

arr = [1, 7, 3, 6, 5, 6]
s1 = Solution()
print(s1.equilibriumPoint(arr))