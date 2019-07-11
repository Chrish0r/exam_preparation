#include <stdio.h>

int ggT(int a, int b) {
    if(b == 0) {
        return a;
    }
    return ggT(b, a % b); // hier Rekursion
}

int main() {

   int a = 1071, b = 1029;

   printf("ggT(%d, %d) = %d\n", a, b, ggT(a, b));

    return 0;
}
