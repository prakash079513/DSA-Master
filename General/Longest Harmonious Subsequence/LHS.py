from collections import Counter

class Solution:
    def findLHS(self, nums):
        freq = Counter(nums)
        res = 0
        for key in freq:
            if key + 1 in freq:
                res = max(res, freq[key] + freq[key + 1])
        return res

# Example
if __name__ == "__main__":
    nums = [1, 3, 2, 2, 5, 2, 3, 7]
    s = Solution()
    print(s.findLHS(nums))  # Output: 5
