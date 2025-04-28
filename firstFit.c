// FirstFit.c
#include <stdio.h>

void FirstFit() {
    int b[10], p[10], bno, pno, alloc[10], i, j;
    printf("Enter number of blocks: ");
    scanf("%d", &bno);
    printf("Enter size of blocks:\n");
    for (i = 0; i < bno; i++)
        scanf("%d", &b[i]);

    printf("Enter number of processes: ");
    scanf("%d", &pno);
    printf("Enter size of processes:\n");
    for (i = 0; i < pno; i++)
        scanf("%d", &p[i]);

    for (i = 0; i < pno; i++) {
        alloc[i] = -1;
        for (j = 0; j < bno; j++) {
            if (b[j] >= p[i]) {
                alloc[i] = j;
                b[j] -= p[i];
                break;
            }
        }
    }

    printf("\nProcess\tSize\tBlock\n");
    for (i = 0; i < pno; i++) {
        printf("P[%d]\t%d\t", i+1, p[i]);
        if (alloc[i] != -1)
            printf("%d\n", alloc[i]+1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    FirstFit();
    return 0;
}
