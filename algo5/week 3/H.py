from itertools import combinations

def correct_and_sort_matches(matches):

    corrected_matches = []
    for x1, y1, x2, y2 in matches:
        if y1 > y2 or (y1 == y2 and x1 > x2):
        
            corrected_matches.append((x2, y2, x1, y1))
        else:
            corrected_matches.append((x1, y1, x2, y2))


    # sorted_matches = sorted(corrected_matches, key=lambda match: (match[1], match[0], match[3], match[2]))
    # return sorted_matches
    return corrected_matches

def read_input_from_file(file_path):
    with open(file_path, 'r') as file:
        input_data = file.read()

    lines = input_data.split('\n')
    n = int(lines[0])
    matches_a = [tuple(map(int, line.split())) for line in lines[1:n+1]]
    matches_b = [tuple(map(int, line.split())) for line in lines[n+1:2*n+1]]

    matches_a_sorted_by_y = correct_and_sort_matches(matches_a)
    matches_b_sorted_by_y = correct_and_sort_matches(matches_b)

    return n, matches_a_sorted_by_y, matches_b_sorted_by_y

def read_input(input_data):
    lines = input_data.split('\n')
    n = int(lines[0])
    matches_a = [tuple(map(int, line.split())) for line in lines[1:n+1]]
    matches_b = [tuple(map(int, line.split())) for line in lines[n+1:2*n+1]]

    matches_a_sorted_by_y = correct_and_sort_matches(matches_a)
    matches_b_sorted_by_y = correct_and_sort_matches(matches_b)

    return n, matches_a_sorted_by_y, matches_b_sorted_by_y

def calculate_min_transfers(n, matches_a, matches_b):

    def distance(match1, match2):
        return (match1[0] - match2[0], match1[1] - match2[1],
                match1[2] - match2[2], match1[3] - match2[3])
    
    def normalize_matches(match1, match2):

        x1, y1, x2, y2 = match1
        normalized_match1 = ((0, 0, x2 - x1, y2 - y1))
        x1, y1, x2, y2 = match2
        normalized_match2 = ((0, 0, x2 - x1, y2 - y1))
        return normalized_match1 == normalized_match2


    distance_freq = {}


    for match_a in matches_a:
        for match_b in matches_b:
            dist = distance(match_a, match_b)
            if normalize_matches(match_a, match_b):
                distance_freq[dist] = distance_freq.get(dist, 0) + 1
            else:
                distance_freq[dist] = distance_freq.get(dist, 0) + 0
            

    max_freq = max(distance_freq.values())


    return n - max_freq

n, matches_a, matches_b = read_input_from_file('input.txt')

min_transfers = calculate_min_transfers(n, matches_a, matches_b)
print(min_transfers)
