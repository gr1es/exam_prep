#!/bin/bash

# Colors for terminal output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Compile the program
echo "Compiling vbc..."
cc -Wall -Wextra -Werror *.c -o vbc
if [ $? -ne 0 ]; then
    echo -e "${RED}Compilation failed!${NC}"
    exit 1
fi
echo -e "${GREEN}Compilation successful!${NC}\n"

# Variables to track score
TOTAL=0
PASSED=0

# The testing function
# Arguments: $1=Description, $2=Input String, $3=Expected Output, $4=Expected Exit Code
run_test() {
    local desc="$1"
    local input="$2"
    local expected_out="$3"
    local expected_code="$4"
    
    ((TOTAL++))
    
# Run the program, capture output and exit code
    local actual_out
    actual_out=$(./vbc "$input" 2>&1)
    local actual_code=$?
    
    # Compare output and exit code
    if [ "$actual_out" == "$expected_out" ] && [ "$actual_code" -eq "$expected_code" ]; then
        echo -e "${GREEN}[OK]${NC} $desc"
        ((PASSED++))
    else
        echo -e "${RED}[KO]${NC} $desc"
        echo "   Input         : ./vbc '$input'"
        echo "   Expected Out  : $expected_out"
        echo "   Actual Out    : $actual_out"
        echo "   Expected Code : $expected_code"
        echo "   Actual Code   : $actual_code"
    fi
}

echo "=== STARTING TESTS ==="

# --- Basic Arithmetic ---
run_test "Single digit" "1" "1" 0
run_test "Simple addition" "2+3" "5" 0
run_test "Order of operations (mult first)" "3+4*5" "23" 0
run_test "Order of operations (mult after)" "3*4+5" "17" 0

# --- Parentheses ---
run_test "Single parentheses" "(1)" "1" 0
run_test "Deeply nested number" "(((((((3)))))))" "3" 0
run_test "Parentheses priority" "(1+2)*3" "9" 0
run_test "Subject nested example" "(((((2+2)*2+2)*2+2)*2+2)*2+2)*2" "188" 0

# --- Long Expressions ---
run_test "Long addition chain" "1+2+3+4+5" "15" 0
run_test "Massive subject string" "((6*6+7+5+8)*(1+0+4*8+7)+2)+4*(1+2)" "2254" 0

# --- Error Handling (Expected Code 1) ---
run_test "Trailing operator" "1+" "Unexpected end of input" 1
run_test "Mismatched closing parenthesis" "1+2)" "Unexpected token ')'" 1
run_test "Double digits (unsupported)" "((1+3)*12+(3*(2+6))" "Unexpected token '2'" 1
run_test "Invalid character (letter)" "2+a" "Unexpected token 'a'" 1

echo -e "\n=== RESULTS: $PASSED / $TOTAL TESTS PASSED ==="

# Clean up the compiled binary
rm -f vbc
