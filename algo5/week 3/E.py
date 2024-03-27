input()
list1 = list(map(int, input().split()))
input()
list2 = list(map(int, input().split()))
input()
list3 = list(map(int, input().split()))

set1 = set(list1)
set2 = set(list2)
set3 = set(list3)

result = (set1 & set2) | (set2 & set3) | (set1 & set3)

print(*sorted(result))