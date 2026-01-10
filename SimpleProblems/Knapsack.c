#include<stdio.h>
void knapsack(int n, float weight[], float profit[], float capacity) {
    float x[20], tp = 0;
    int i;
    float u = capacity;

    for (i = 0; i < n; i++)
        x[i] = 0.0;

    for (i = 0; i < n; i++) {
        if (weight[i] <= u) {
            x[i] = 1.0;
            tp += profit[i];
            u -= weight[i];
        } else {
            x[i] = u / weight[i];
            tp += x[i] * profit[i];
            break;
        }
    }


    printf("\nThe result vector is:\n");
    for (i = 0; i < n; i++)
        printf("%.2f\t", x[i]);

    printf("\nMaximum profit is: %.2f\n", tp);
}

int main() {
    float weight[20], profit[20], capacity;
    int num, i, j;
    float ratio[20], temp;

    printf("\nEnter the number of objects: ");
    scanf("%d", &num);

    printf("\nEnter the weights and profits of each object:\n");
    for (i = 0; i < num; i++) {
        scanf("%f %f", &weight[i], &profit[i]);
    }

    printf("\nEnter the capacity of the knapsack: ");
    scanf("%f", &capacity);
    for (i = 0; i < num; i++) {
        ratio[i] = profit[i] / weight[i];
    }
    for (i = 0; i < num - 1; i++) {
        for (j = i + 1; j < num; j++) {
            if (ratio[i] < ratio[j]) {

                temp = ratio[i];
                ratio[i] = ratio[j];
                ratio[j] = temp;

                temp = weight[i];
                weight[i] = weight[j];
                weight[j] = temp;

                temp = profit[i];
                profit[i] = profit[j];
                profit[j] = temp;
            }
        }
    }

    knapsack(num, weight, profit, capacity);
    return 0;
}
