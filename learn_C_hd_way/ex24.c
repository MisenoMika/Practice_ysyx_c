#include <stdio.h>
#include "ex20/dbg.h"
#include <stdlib.h>

#define MAX_DATA 100068

typedef enum EyeColor {
    BLUE_EYES, GREEN_EYES, BROWN_EYES,
    BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
    "Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
} Person;

int file_scanf(const char *filename, char *buf, int size) {
    if (size <= 0) return 0;

    FILE *fp = freopen(filename, "r", stdin);
    check(fp != NULL, "Failed to open %s.", filename);

    int i = 0;
    char ch;
    while (i < size - 1 && scanf("%c", &ch) == 1) {
        buf[i++] = ch;
    }
    buf[i] = '\0'; 
    fclose(fp);
    return 1;
error:
    return 0;
}

int main(int argc, char *argv[])
{   
    int rc = 0;
    Person you = {.age = 0};
    int i = 0;
    char *in = NULL;
    char file_name[] = "ex23.c";
    char buf[MAX_DATA];
    rc = file_scanf(file_name, buf, MAX_DATA);
    fflush(stdout);
    check(rc == 1, "Failed to read file.");
    printf("File contents:\n%s\n", buf);
    fflush(stdout);

    freopen("/dev/tty", "r", stdin);
    printf("What's your First Name? ");
    in = fgets(you.first_name, MAX_DATA-1, stdin);
    check(in != NULL, "Failed to read first name.");

    printf("What's your Last Name? ");
    in = fgets(you.last_name, MAX_DATA-1, stdin);
    check(in != NULL, "Failed to read last name.");

    printf("How old are you? ");
    //int rc = fscanf(stdin, "%d", &you.age);
    rc = scanf("%d", &you.age);
    check(rc > 0, "You have to enter a number.");

    printf("What color are your eyes:\n");
    for(i = 0; i <= OTHER_EYES; i++) {
        printf("%d) %s\n", i+1, EYE_COLOR_NAMES[i]);
    }
    printf("> ");

    int eyes = -1;
    rc = fscanf(stdin, "%d", &eyes);
    check(rc > 0, "You have to enter a number.");

    you.eyes = eyes - 1;
    check(you.eyes <= OTHER_EYES && you.eyes >= 0, "Do it right, that's not an option.");

    printf("How much do you make an hour? ");
    rc = fscanf(stdin, "%f", &you.income);
    check(rc > 0, "Enter a floating point number.");

    printf("----- RESULTS -----\n");

    printf("First Name: %s", you.first_name);
    printf("Last Name: %s", you.last_name);
    printf("Age: %d\n", you.age);
    printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
    printf("Income: %f\n", you.income);
    return 0;
error:

    return -1;
}