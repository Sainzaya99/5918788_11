#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEGREE 101

typedef struct {
    int degree;
    float coef[MAX_DEGREE];
} Polynomial;

void initPoly(Polynomial* p) {
    p->degree = 0;
    for (int i = 0; i < MAX_DEGREE; i++) p->coef[i] = 0;
}

void parseInput(char* input, Polynomial* p) {
    char* token = strtok(input, "+");
    while (token != NULL) {
        float c;
        int e;
        if (sscanf(token, "%fX^%d", &c, &e) == 2) {
            p->coef[e] = c;
            if (e > p->degree) p->degree = e;
        }
        token = strtok(NULL, "+");
    }
}

int main() {
    Polynomial p1, p2, result;
    initPoly(&p1);
    initPoly(&p2);
    initPoly(&result);

    char str1[200], str2[200];

    printf("Enter FIRST polynomial: ");
    scanf("%s", str1);
    parseInput(str1, &p1);

    printf("Enter SECOND polynomial: ");
    scanf("%s", str2);
    parseInput(str2, &p2);

    result.degree = p1.degree + p2.degree;
    if (result.degree >= MAX_DEGREE) {
        printf("Error: Degree exceeds MAX_DEGREE\n");
        return 1;
    }

    for (int i = 0; i <= p1.degree; i++) {
        if (p1.coef[i] == 0) continue;
        for (int j = 0; j <= p2.degree; j++) {
            if (p2.coef[j] == 0) continue;
            result.coef[i + j] += p1.coef[i] * p2.coef[j];
        }
    }

    printf("\nResulting Polynomial: ");
    int first = 1;
    for (int i = result.degree; i >= 0; i--) {
        if (result.coef[i] != 0) {
            if (!first) printf("+");
            printf("%.1fX^%d", result.coef[i], i);
            first = 0;
        }
    }
    printf("\n");

    return 0;
}