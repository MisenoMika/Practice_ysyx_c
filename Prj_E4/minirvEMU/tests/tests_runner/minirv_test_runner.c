#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <include/minirvEMU.h>

typedef void (*test_fn_t)(void);
struct test_entry { const char *name; test_fn_t fn; };

void test1(void);
void test2(void);
void test3(void);
void test4(void);
void test5(void);
void test6(void);

static struct test_entry tests[] = {
    {"test1", test1},
    {"test2", test2},
    {"test3", test3},
    {"test4", test4},
    {"test5", test5},
    {"test6", test6}

};

static test_fn_t find_test(const char *name) {
    size_t n = sizeof(tests) / sizeof(tests[0]);
    for (size_t i = 0; i < n; i++) {
        if (strcmp(tests[i].name, name) == 0) {
            return tests[i].fn;
        }
    }
    return NULL;
}

int main(int argc, char **argv) {
    if (argc < 2 || argc > 4) {
        fprintf(stderr, "Usage: %s <test_name> [file.bin] [cycles]\n", argv[0]);
        return 1;
    }

    const char *test_name = argv[1];
    char *bin_file = (argc >= 3) ? argv[2] : NULL;
    int cycles = (argc >= 4) ? atoi(argv[3]) : 7000;
    if (cycles <= 0) {
        cycles = 7000;
    }

    test_fn_t selected = find_test(test_name);
    if (selected == NULL) {
        fprintf(stderr, "Unknown test in runner: %s\n", test_name);
        return 2;
    }

    memset(ROM, 0, sizeof(ROM));
    memset(RAM, 0, sizeof(RAM));
    memset(R, 0, sizeof(R));
    PC = 0;
    cnt = 0;
    stop = 0;

    if (bin_file != NULL && bin_file[0] != '\0') {
        load_bin(bin_file, ROM);
        load_bin(bin_file, RAM);
    } else {
        init_ROM(ROM);
    }

    for (int i = 0; i < cycles && !stop; i++) {
        /* Keep built-in test1 in inst_cycle from stopping early. */
        printf("\n--- PC: %#x ---\n", PC);
        selected();
        //cnt += 1;
        inst_cycle();
    }

    //cnt = 20;
    selected();
    return 0;
}
