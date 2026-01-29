import subprocess
import sys

# Known solution counts for N=1 to N=12
SOLUTIONS_COUNT = {
    1: 1, 2: 0, 3: 0, 4: 2, 5: 10, 6: 4, 7: 40,
    8: 92, 9: 352, 10: 724, 11: 2680, 12: 14200
}

def verify_board(board):
    """
    Mathematically checks if a board (list of ints) is valid.
    Returns True if valid, False otherwise.
    """
    n = len(board)
    for i in range(n):
        for j in range(i + 1, n):
            # 1. Check Row collision (Values are same)
            if board[i] == board[j]:
                return False
            # 2. Check Diagonal collision
            # |col_1 - col_2| == |row_1 - row_2|
            if abs(i - j) == abs(board[i] - board[j]):
                return False
    return True

def run_test(n):
    print(f"Testing N={n}...", end=" ", flush=True)

    try:
        # Run the C program
        result = subprocess.run(
            ["./n_queens", str(n)],
            capture_output=True,
            text=True,
            timeout=5 # Timeout in seconds (prevent infinite loops)
        )
    except subprocess.TimeoutExpired:
        print("❌ TIMEOUT (Infinite Loop?)")
        return

    output_lines = result.stdout.strip().split('\n')

    # Handle N with 0 solutions (output might be empty string)
    if len(output_lines) == 1 and output_lines[0] == '':
        output_lines = []

    # 1. Check Count
    expected = SOLUTIONS_COUNT.get(n)
    actual = len(output_lines)

    if expected is not None:
        if actual != expected:
            print(f"❌ FAIL: Found {actual} solutions, expected {expected}")
            return

    # 2. Check Logic of Every Solution
    for line in output_lines:
        try:
            # Convert "0 2 1 4" string to [0, 2, 1, 4] list
            board = [int(x) for x in line.strip().split()]
            if not verify_board(board):
                print(f"\n❌ INVALID BOARD FOUND: {line}")
                return
        except ValueError:
            print(f"\n❌ FORMAT ERROR: Could not parse line: '{line}'")
            return

    print("✅ PASS")

def main():
    # Check if executable exists
    import os
    if not os.path.isfile("./n_queens"):
        print("Error: ./n_queens executable not found. Compile it first!")
        sys.exit(1)

    # Run tests from N=1 to N=10
    # (Going higher than 10 might be slow depending on your optimization)
    for i in range(1, 11):
        run_test(i)

if __name__ == "__main__":
    main()
