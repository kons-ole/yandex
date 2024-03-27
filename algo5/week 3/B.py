def is_anagram(str1, str2):
    return sorted(str1) == sorted(str2)

string1 = input()
string2 = input()

result = is_anagram(string1, string2)
if result:
    print("YES")
else:
    print("NO")