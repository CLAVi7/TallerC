#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

static void printArray(const int *a, int n) {
    printf("[");
    for (int i = 0; i < n; ++i) printf("%s%d", i ? ", " : "", a[i]);
    printf("]");
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int sumArray(const int *a, int n) {
    int result = 0;
    for (int i = 0; i < n; ++i) result += a[i];
    return result;
}

int minArray(const int *a, int n) {
    int result = a[0];
    for (int i = 1; i < n; ++i) if (a[i] < result) result = a[i];
    return result;
}

int maxArray(const int *a, int n) {
    int result = a[0];
    for (int i = 1; i < n; ++i) if (a[i] > result) result = a[i];
    return result;
}

int countNegatives(const int *a, int n) {
    int count = 0;
    for (int i = 0; i < n; ++i) if (a[i] < 0) ++count;
    return count;
}

void printReverse(const int *a, int n) {
    for (int i = n - 1; i >= 0; --i) printf("%s%d", i == n - 1 ? "" : " ", a[i]);
    printf("\n");
}

int *copyArray(const int *values, int size) {
    if (size <= 0 || (size_t)size > SIZE_MAX / sizeof(int)) return NULL;
    int *result = malloc((size_t)size * sizeof(*result));
    if (result == NULL) return NULL;
    for (int i = 0; i < size; ++i) result[i] = values[i];
    return result;
}

void sortAscending(int *values, int size) {
    for (int i = 1; i < size; ++i) {
        int current = values[i];
        int j = i - 1;
        while (j >= 0 && values[j] > current) {
            values[j + 1] = values[j];
            --j;
        }
        values[j + 1] = current;
    }
}

int findPair(const int *values, int size, int target) {
    int left = 0, right = size - 1;
    while (left < right) {
        long long sum = (long long)values[left] + values[right];
        if (sum == target) {
            printf("Par encontrado: (%d, %d)\n", values[left], values[right]);
            return 1;
        }
        if (sum < target) ++left;
        else --right;
    }
    printf("No existe un par valido.\n");
    return 0;
}

int threeSum(const int *values, int size) {
    if (size < 3) return 0;
    int *sorted = copyArray(values, size);
    if (sorted == NULL) return -1;
    sortAscending(sorted, size);
    int count = 0;
    for (int i = 0; i < size - 2; ++i) {
        if (i > 0 && sorted[i] == sorted[i - 1]) continue;
        int left = i + 1, right = size - 1;
        while (left < right) {
            long long sum = (long long)sorted[i] + sorted[left] + sorted[right];
            if (sum < 0) ++left;
            else if (sum > 0) --right;
            else {
                printf("  (%d, %d, %d)\n", sorted[i], sorted[left], sorted[right]);
                ++count;
                int leftValue = sorted[left], rightValue = sorted[right];
                do { ++left; } while (left < right && sorted[left] == leftValue);
                do { --right; } while (left < right && sorted[right] == rightValue);
            }
        }
    }
    free(sorted);
    return count;
}

void buildLeftMax(const int *height, int size, int *leftMax) {
    int best = height[0];
    for (int i = 0; i < size; ++i) {
        if (height[i] > best) best = height[i];
        leftMax[i] = best;
    }
}

void buildRightMax(const int *height, int size, int *rightMax) {
    int best = height[size - 1];
    for (int i = size - 1; i >= 0; --i) {
        if (height[i] > best) best = height[i];
        rightMax[i] = best;
    }
}

long long trappedWater(const int *height, int size) {
    if (size <= 0) return 0;
    if ((size_t)size > SIZE_MAX / sizeof(int)) return -1;
    int *leftMax = malloc((size_t)size * sizeof(*leftMax));
    if (leftMax == NULL) return -1;
    int *rightMax = malloc((size_t)size * sizeof(*rightMax));
    if (rightMax == NULL) {
        free(leftMax);
        return -1;
    }
    buildLeftMax(height, size, leftMax);
    buildRightMax(height, size, rightMax);
    long long total = 0;
    for (int i = 0; i < size; ++i) {
        int limit = leftMax[i] < rightMax[i] ? leftMax[i] : rightMax[i];
        total += (long long)(limit - height[i]);
    }
    free(leftMax);
    free(rightMax);
    return total;
}

static void heading(int n, const char *name) {
    printf("\nEJERCICIO %d: %s\n", n, name);
}

static void test3Sum(const int *a, int n, int expected) {
    printf("Entrada: "); printArray(a, n); printf("\n");
    int actual = threeSum(a, n);
    printf("Cantidad: %d | Esperado: %d | %s\n", actual, expected,
           actual == expected ? "OK" : "ERROR");
}

static void testWater(const int *a, int n, long long expected) {
    printf("Alturas: "); printArray(a, n);
    long long actual = trappedWater(a, n);
    printf(" | Agua: %lld | Esperado: %lld | %s\n", actual, expected,
           actual == expected ? "OK" : "ERROR");
}

static int showWaterDetail(const int *height, int size) {
    int *left = malloc((size_t)size * sizeof(*left));
    if (left == NULL) return 0;
    int *right = malloc((size_t)size * sizeof(*right));
    if (right == NULL) { free(left); return 0; }
    buildLeftMax(height, size, left);
    buildRightMax(height, size, right);
    printf("Detalle por posicion:\n");
    printf("Posicion | Altura | Max. izq. | Max. der. | Agua\n");
    for (int i = 0; i < size; ++i) {
        int limit = left[i] < right[i] ? left[i] : right[i];
        printf("%8d | %6d | %9d | %9d | %d\n", i, height[i], left[i], right[i], limit - height[i]);
    }
    free(right);
    free(left);
    return 1;
}

int main(void) {
    printf("========== TALLER DE C ==========\n");

    heading(1, "INTERCAMBIO");
    int a = 8, b = -3;
    printf("Antes: a = %d, b = %d\n", a, b);
    swap(&a, &b);
    printf("Despues: a = %d, b = %d\n", a, b);

    heading(2, "ESTADISTICAS");
    int values[] = {4, -2, 0, 7, -5};
    int n = (int)(sizeof(values) / sizeof(values[0]));
    printf("Entrada: "); printArray(values, n); printf("\n");
    printf("Suma: %d\nMinimo: %d\nMaximo: %d\nNegativos: %d\nInverso: ",
           sumArray(values, n), minArray(values, n), maxArray(values, n), countNegatives(values, n));
    printReverse(values, n);

    heading(3, "COPIA INDEPENDIENTE");
    int *copy = copyArray(values, n);
    if (copy == NULL) { fprintf(stderr, "Error al reservar copia.\n"); return EXIT_FAILURE; }
    copy[0] = 99;
    printf("Original: "); printArray(values, n);
    printf("\nCopia:    "); printArray(copy, n); printf("\n");
    free(copy);

    heading(4, "ORDENAMIENTO");
    copy = copyArray(values, n);
    if (copy == NULL) { fprintf(stderr, "Error al reservar copia.\n"); return EXIT_FAILURE; }
    sortAscending(copy, n);
    printf("Original: "); printArray(values, n);
    printf("\nOrdenado: "); printArray(copy, n); printf("\n");
    free(copy);

    heading(5, "BUSQUEDA DE PARES");
    int pairValues[] = {-4, -1, 0, 2, 5};
    int zeros[] = {0, 0};
    int single[] = {3};
    printf("Caso 1 (objetivo 1): "); (void)findPair(pairValues, 5, 1);
    printf("Caso 2 (objetivo 8): "); (void)findPair(pairValues, 5, 8);
    printf("Caso 3 (objetivo 0): "); (void)findPair(zeros, 2, 0);
    printf("Caso 4 (objetivo 6): "); (void)findPair(single, 1, 6);
    printf("Caso adicional (sin elementos): "); (void)findPair(single, 0, 6);

    heading(6, "3SUM");
    int t1[] = {-1, 0, 1, 2, -1, -4};
    int t2[] = {0, 1, 1};
    int t3[] = {0, 0, 0};
    int t4[] = {0, 0, 0, 0};
    int t5[] = {-2, 0, 0, 2, 2};
    test3Sum(t1, 6, 2);
    test3Sum(t2, 3, 0);
    test3Sum(t3, 3, 1);
    test3Sum(t4, 4, 1);
    test3Sum(t5, 5, 1);
    test3Sum(zeros, 2, 0);

    heading(7, "MAXIMOS ACUMULADOS");
    int height[] = {3, 0, 2, 0, 4};
    int leftMax[5], rightMax[5];
    buildLeftMax(height, 5, leftMax);
    buildRightMax(height, 5, rightMax);
    printf("Alturas:   "); printArray(height, 5);
    printf("\nMax. izq.: "); printArray(leftMax, 5);
    printf("\nMax. der.: "); printArray(rightMax, 5); printf("\n");

    heading(8, "TRAPPING RAIN WATER");
    int w1[] = {5};
    int w2[] = {0, 1, 2, 3};
    int w3[] = {3, 2, 1, 0};
    int w4[] = {2, 2, 2};
    int w5[] = {3, 0, 3};
    int w7[] = {4, 2, 0, 3, 2, 5};
    int w8[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    int own[] = {2, 0, 1, 0, 2}; /* 2 + 1 + 2 = 5 */
    testWater(w1, 1, 0);
    testWater(w2, 4, 0);
    testWater(w3, 4, 0);
    testWater(w4, 3, 0);
    testWater(w5, 3, 3);
    testWater(height, 5, 7);
    testWater(w7, 6, 9);
    testWater(w8, 12, 6);
    printf("Caso propio: "); testWater(own, 5, 5);
    if (!showWaterDetail(height, 5)) {
        fprintf(stderr, "Error al reservar memoria para detalle.\n");
        return EXIT_FAILURE;
    }
    printf("\n========== FIN DEL TALLER ==========\n");
    return EXIT_SUCCESS;
}
