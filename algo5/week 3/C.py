def min_deletions_to_make_near_equal(a):
    a.sort()
    max_length = 0
    left = 0

    for right in range(len(a)):
        while a[right] - a[left] > 1:
            left += 1
        max_length = max(max_length, right - left + 1)

    return len(a) - max_length
input()
a = list(map(int, input().split()))
result = min_deletions_to_make_near_equal(a)
print(result)
