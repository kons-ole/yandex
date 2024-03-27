def find_min_points_for_square(points):
    def complete_square(point):
        x, y = point[0]
        return [(x + 1, y), (x, y + 1), (x + 1, y + 1)]

    if len(points) == 1:
        best_added_points = complete_square(points)
        min_added_points = 3
        return min_added_points, best_added_points

    points_set = set(points)
    min_added_points = float('inf')
    best_added_points = []

    def check_square(p1, p2):
        dx = p2[0] - p1[0]
        dy = p2[1] - p1[1]
        return (p1[0] + dy, p1[1] - dx), (p2[0] + dy, p2[1] - dx)

    for i in range(len(points)):
        for j in range(i + 1, len(points)):
            p1 = points[i]
            p2 = points[j]
            for _ in range(2):    
                p3, p4 = check_square(p1, p2)
                add_count = 0
                to_add = []

                if p3 not in points_set:
                    add_count += 1
                    to_add.append(p3)
                if p4 not in points_set:
                    add_count += 1
                    to_add.append(p4)
                if add_count < min_added_points:
                    min_added_points = add_count
                    best_added_points = to_add
                p1, p2 = p2, p1
    return min_added_points, best_added_points

# with open('input.txt', 'r') as file:
#     n = int(file.readline().strip())  # Считываем первую строку файла для значения n
#     points = [tuple(map(int, file.readline().strip().split())) for _ in range(n)]
n = int(input())
points = [tuple(map(int, input().split())) for _ in range(n)]
min_points, added_points = find_min_points_for_square(points)

print(min_points)
for x, y in added_points:
    print(x, y)



