def shorten_text(text, shortening_dict):
    words = text.split()
    sorted_dict = sorted(shortening_dict, key=len)
    shortened_words = []
    for word in words:
        shortest = word
        for short_word in sorted_dict:
            if word.startswith(short_word):
                shortest = short_word
                break
        shortened_words.append(shortest)

    return ' '.join(shortened_words)


shortening_dict = list(input().split())
text = input()
shortened_text = shorten_text(text, shortening_dict)
print(shortened_text)
