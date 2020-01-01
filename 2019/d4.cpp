#include "common.h"

const int N = 6;
array<int, N> next(array<int, N> x)
{
    int i = N - 1;
    for (; i >= 0;) {
        if (++x[i] <= 9) {
            FOR (j, i + 1, < N) {
                x[j] = max(x[j], x[i]);
            }
            break;
        }
        x[i] = 0;
        --i;
    }
    bool ok = false;
    FOR (i, 1, <= N - 1) {
        if (x[i] == x[i - 1]) {
            ok = true;
            break;
        }
    }
    if (ok) {
        return x;
    }
    if (x[N - 2] > x[N - 1]) {
        x[N - 1] = x[N - 2];
        return x;
    }
    x[N - 1] = 9;
    return next(x);
}

void print(array<int, N> x)
{
    for (auto i : x) {
        printf("%d", i);
    }
    printf("\n");
}
bool meets(int i)
{
    array<int, 6> a;
    FORBACK (j, N - 1, >= 0) {
        a[j] = i % 10;
        i /= 10;
    }
    bool ok = false;
    FOR (i, 1, < 6) {
        if (a[i] < a[i - 1]) {
            return false;
        }
        if (a[i] == a[i - 1]) {
            if ((i == 1 || a[i - 2] != a[i]) && (i == 5 || a[i] != a[i + 1])) {
                ok = true;
            }
        }
    }
    return ok;
}

int main()
{
    array<int, N> x = {2, 5, 5, 5, 5, 5};
    array<int, N> y = {7, 8, 9, 9, 9, 9};
    int counter = 0;
    for (;;) {
        print(x);
        ++counter;
        if (x == y) {
            break;
        }
        x = next(x);
    }
    printf("counter: %d\n", counter);

    int counter2 = 0;
    FOR (i, 254032, <= 789860) {
        if (meets(i)) {
            printf("%d\n", i);
            ++counter2;
        }
    }
    printf("counter2: %d\n", counter2);
    return 0;
}
