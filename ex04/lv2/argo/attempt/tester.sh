#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

# ==============================================================================
# 1. GENERATE THE MOCK MAIN
# ==============================================================================
# The exam provides a main.c to print your AST. We must recreate it here so 
# we can actually test if your parsing mapped the data correctly.

cat << 'EOF' > mock_main.c
#include "argo.h"
#include <stdlib.h>

// Forward declarations for freeing
void free_map_mock(map *m);
void free_json_mock(json val);

void print_json(json val) {
    if (val.type == INTEGER) 
        printf("%d", val.integer);
    else if (val.type == STRING) 
        printf("\"%s\"", val.string);
    else if (val.type == MAP) {
        printf("{");
        for (size_t i = 0; i < val.map->size; i++) {
            printf("\"%s\":", val.map->data[i].key);
            print_json(val.map->data[i].value);
            if (i < val.map->size - 1) printf(",");
        }
        printf("}");
    }
}

void free_json_mock(json val) {
    if (val.type == STRING) free(val.string);
    if (val.type == MAP) free_map_mock(val.map);
}

void free_map_mock(map *m) {
    if (!m) return;
    for (size_t i = 0; i < m->size; i++) {
        free(m->data[i].key);
        free_json_mock(m->data[i].value);
    }
    free(m->data);
    free(m);
}

int main(int argc, char **argv) {
    if (argc != 2) return 1;
    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;
    
    json root;
    // Call your argo function
    if (argo(&root, f) == 1) {
        print_json(root); // Prove the AST is correct
        free_json_mock(root);
        fclose(f);
        return 0; // Success exit code
    }
    fclose(f);
    return 1; // Failure exit code
}
EOF

# ==============================================================================
# 2. COMPILE
# ==============================================================================

echo "Compiling argo..."
cc -Wall -Wextra -Werror argo.c mock_main.c -o argo_test
if [ $? -ne 0 ]; then
    echo -e "${RED}Compilation failed!${NC}"
    rm -f mock_main.c
    exit 1
fi
echo -e "${GREEN}Compilation successful!${NC}\n"

# ==============================================================================
# 3. TEST RUNNER LOGIC
# ==============================================================================

TOTAL=0
PASSED=0

run_test() {
    local desc="$1"
    local input="$2"
    local expected_out="$3"
    local expected_code="$4"
    
    ((TOTAL++))
    
    # Write input to a temp file
    echo -n "$input" > temp_input.txt
    
    # Run the program cleanly. No subshells to mask the exit code.
    ./argo_test temp_input.txt > temp_output.txt 2>&1
    local actual_code=$?
    
    # Read the captured output
    local actual_out=$(cat temp_output.txt)
    
    if [ "$actual_out" == "$expected_out" ] && [ "$actual_code" -eq "$expected_code" ]; then
        echo -e "${GREEN}[OK]${NC} $desc"
        ((PASSED++))
    else
        echo -e "${RED}[KO]${NC} $desc"
        echo "   Input         : $input"
        echo "   Expected Out  : $expected_out"
        echo "   Actual Out    : $actual_out"
        echo "   Expected Code : $expected_code"
        echo "   Actual Code   : $actual_code"
    fi
}

echo "=== STARTING TESTS ==="

# --- 1. Valid Subject Examples ---
run_test "Basic integer" '1' '1' 0
run_test "Basic string" '"bonjour"' '"bonjour"' 0
run_test "String with valid escapes" '"escape! \" "' '"escape! \" "' 0
run_test "Basic map" '{"tomatoes":42,"potatoes":234}' '{"tomatoes":42,"potatoes":234}' 0
run_test "Deep recursion map" '{"recursion":{"recursion":{"recursion":{"recursion":"recursion"}}}}' '{"recursion":{"recursion":{"recursion":{"recursion":"recursion"}}}}' 0

# --- 2. Error Subject Examples ---
run_test "Unfinished string" '"unfinished string' "unexpected end of input" 1
run_test "Unfinished string with trailing escape" '"unfinished string 2\"' "unexpected end of input" 1
run_test "Map missing value" '{"no value?":}' "unexpected token '}'" 1

# --- 3. Custom Edge Cases (Crucial for passing Moulinette) ---
run_test "Trailing garbage (int)" '123a' "unexpected token 'a'" 1
run_test "Trailing garbage (map)" '{"a":1}b' "unexpected token 'b'" 1
run_test "Invalid escape character" '"bad \n escape"' "unexpected token 'n'" 1
run_test "Spaces are invalid" '{"a": 1}' "unexpected token ' '" 1
run_test "Empty map" '{}' '{}' 0
run_test "Missing colon in map" '{"key"123}' "unexpected token '1'" 1
run_test "Negative integers" '-42' '-42' 0
run_test "Invalid map key type" '{123:456}' "unexpected token '1'" 1

echo -e "\n=== RESULTS: $PASSED / $TOTAL TESTS PASSED ==="

# ==============================================================================
# 4. CLEANUP
# ==============================================================================
rm -f argo_test mock_main.c temp_input.txt temp_output.txt
