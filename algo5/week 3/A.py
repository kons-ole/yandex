from functools import reduce
n = int(input())
members = []
for _ in range(n):
    k = int(input())
    members.append(set(input().split()))

intersection_set = reduce(lambda a, b: a & b, members)

print(len(intersection_set))
print(*sorted(intersection_set))