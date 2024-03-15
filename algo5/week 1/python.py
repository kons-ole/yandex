n = int(input())
sum = 0
for i in range(n):
    a = int(input())
    sum += a // 4
    a %= 4
    if a == 3:
        sum+=2
    else :
        sum+=a

print(sum)