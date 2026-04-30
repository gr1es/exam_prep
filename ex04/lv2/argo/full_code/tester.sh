#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

cat << 'EOF' > mock_main.c
#include "argo.h"
#include <stdlib.h>

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
    if (argo(&root, f) == 1) {
        print_json(root);
        free_json_mock(root);
        fclose(f);
        return 0;
    }
    fclose(f);
    return 1;
}
EOF

echo "Compiling argo..."
cc -Wall -Wextra -Werror argo.c mock_main.c -o argo_test
if [ $? -ne 0 ]; then
    echo -e "${RED}Compilation failed!${NC}"
    rm -f mock_main.c
    exit 1
fi
echo -e "${GREEN}Compilation successful!${NC}\n"

TOTAL=0
PASSED=0

run_test() {
    local desc="$1"
    local input="$2"
    local expected_out="$3"
    local expected_code="$4"
    
    ((TOTAL++))
    
    echo -n "$input" > temp_input.txt
    
    ./argo_test temp_input.txt > temp_output.txt 2>&1
    local actual_code=$?
    
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

run_test "Basic integer" '1' '1' 0
run_test "Basic string" '"bonjour"' '"bonjour"' 0
run_test "String with valid escapes" '"escape! \" "' '"escape! \" "' 0
run_test "Basic map" '{"tomatoes":42,"potatoes":234}' '{"tomatoes":42,"potatoes":234}' 0
run_test "Deep recursion map" '{"recursion":{"recursion":{"recursion":{"recursion":"recursion"}}}}' '{"recursion":{"recursion":{"recursion":{"recursion":"recursion"}}}}' 0

run_test "Unfinished string" '"unfinished string' "unexpected end of input" 1
run_test "Unfinished string with trailing escape" '"unfinished string 2\"' "unexpected end of input" 1
run_test "Map missing value" '{"no value?":}' "unexpected token '}'" 1

run_test "Trailing garbage (int)" '123a' "unexpected token 'a'" 1
run_test "Trailing garbage (map)" '{"a":1}b' "unexpected token 'b'" 1
run_test "Invalid escape character" '"bad \n escape"' "unexpected token 'n'" 1
run_test "Spaces are invalid" '{"a": 1}' "unexpected token ' '" 1
run_test "Empty map" '{}' '{}' 0
run_test "Missing colon in map" '{"key"123}' "unexpected token '1'" 1
run_test "Negative integers" '-42' '-42' 0
run_test "Invalid map key type" '{123:456}' "unexpected token '1'" 1

echo -e "\n=== RESULTS: $PASSED / $TOTAL TESTS PASSED ==="

rm -f argo_test mock_main.c temp_input.txt temp_output.txt
