def check_two_rectangles(m, n, grid):
    def is_rectangle(x1, y1, x2, y2):
        for i in range(x1, x2 + 1):
            for j in range(y1, y2 + 1):
                if grid[i][j] != '#':
                    return False
        return True

    # Find the coordinates of the black squares
    black_squares = [(i, j) for i in range(m) for j in range(n) if grid[i][j] == '#']
    
    if not black_squares:
        return "NO"  # No black squares, hence no rectangles

    # Try to split the black squares into two non-overlapping rectangles
    for i in range(len(black_squares)):
        for j in range(i + 1, len(black_squares)):
            x1, y1 = black_squares[i]
            x2, y2 = black_squares[j]
            # Check if (x1, y1) and (x2, y2) can form the opposite corners of a rectangle
            if x1 <= x2 and y1 <= y2 and is_rectangle(x1, y1, x2, y2):
                # Mark the first rectangle
                for x in range(x1, x2 + 1):
                    for y in range(y1, y2 + 1):
                        grid[x][y] = 'a'
                
                # Check if the remaining black squares form a rectangle
                remaining_black_squares = [(x, y) for x in range(m) for y in range(n) if grid[x][y] == '#']
                if not remaining_black_squares:
                    continue

                rx1, ry1 = remaining_black_squares[0]
                rx2, ry2 = remaining_black_squares[-1]

                if is_rectangle(rx1, ry1, rx2, ry2):
                    # Mark the second rectangle
                    for x in range(rx1, rx2 + 1):
                        for y in range(ry1, ry2 + 1):
                            grid[x][y] = 'b'

                    # Check if there are no remaining black squares
                    if all(grid[x][y] != '#' for x in range(m) for y in range(n)):
                        return "YES\n" + "\n".join("".join(row) for row in grid)

                # Reset the grid and try the next pair
                grid = [['#' if (x, y) in black_squares else '.' for y in range(n)] for x in range(m)]

    return "NO"

# Test cases from the provided examples
test1 = (2, 1, ["#", "."])
test2 = (2, 2, ["..", "##"])
test3 = (1, 3, ["###"])
test4 = (1, 5, ["####."])

for test in [test1, test2, test3, test4]:
    m, n, grid = test
    print(f"Input:\n{m} {n}\n" + "\n".join(grid))
    print(f"Output:\n{check_two_rectangles(m, n, [list(row) for row in grid])}\n")

