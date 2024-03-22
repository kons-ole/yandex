def min_moves_to_align_ships(N, ships):
    min_moves = float('inf')
    current_row_moves = 0
    for col in range(1, N + 1):
        current_moves = 0
        min_row_moves = N + 1
        min_row = N + 1
        i_reminder = -1
        for i, (row, ship_col) in enumerate(ships):
            current_moves += abs(ship_col - col)
            if min_row_moves >= abs(row - col) and row <= min_row:
                min_row_moves = abs(row - col)
                min_row = row
                i_reminder = i
        ships[i_reminder] = (N + 2, ships[i_reminder][1])
        current_row_moves += min_row_moves
        min_moves = min(min_moves, current_moves)

    return min_moves + current_row_moves

# Testing the function with the provided test case
N = 10
ships = [(3, 7), (7, 10), (4, 9), (2, 2), (5, 9), (8, 2), (5, 5), (10, 4), (2, 10), (6, 5)]
print(min_moves_to_align_ships(N, ships))
