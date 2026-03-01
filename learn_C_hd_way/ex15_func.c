#include <stdio.h>

void print_by_index(char *names[], int ages[], int count)
{
    for(int i = 0; i < count; i++) {
        printf("%s has %d years alive.\n",
               names[i], ages[i]);
    }
}

void print_by_pointer_math(char **names, int *ages, int count)
{
    for(int i = 0; i < count; i++) {
        printf("%s is %d years old.\n",
               *(names + i), *(ages + i));
    }
}

void print_pointer_as_array(char **names, int *ages, int count)
{
    for(int i = 0; i < count; i++) {
        printf("%s is %d years old again.\n",
               names[i], ages[i]);
    }
}

void print_by_pointer_walk(char **names, int *ages, int count)
{
    char **cur_name = names;
    int *cur_age = ages;

    while ((cur_age - ages) < count) {
        printf("%s lived %d years so far.\n",
               *cur_name, *cur_age);
        cur_name++;
        cur_age++;
    }
}

int main(void)
{
    int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    int count = sizeof(ages) / sizeof(int);

    print_by_index(names, ages, count);
    printf("---\n");

    print_by_pointer_math(names, ages, count);
    printf("---\n");

    print_pointer_as_array(names, ages, count);
    printf("---\n");

    print_by_pointer_walk(names, ages, count);

    return 0;
}