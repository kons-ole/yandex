def has_repeats_within_k(sequence, k):
    seen = set()
    for i, num in enumerate(sequence):
        if num in seen:
            return "YES"
        seen.add(num)
        if i >= k:
            seen.remove(sequence[i - k])
    return "NO"

n, k = list(map(int, input().split()))
sequence = list(map(int, input().split()))

print(has_repeats_within_k(sequence, k))