#include <stdio.h>
#define MAX 5

int available[MAX], max[MAX][MAX], allocation[MAX][MAX], need[MAX][MAX], n, m;

void calculateNeed()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];
}

int checkSafeState()
{
    int work[MAX], finish[MAX] = {0}, safeSequence[MAX], count = 0;
    for (int i = 0; i < m; i++)
        work[i] = available[i];

    while (count < n)
    {
        int found = 0;
        for (int i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int j;
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j])
                        break;

                if (j == m)
                {
                    for (int k = 0; k < m; k++)
                        work[k] += allocation[i][k];
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0)
        {
            printf("\nSystem is not in a safe state.\n");
            return 0;
        }
    }

    printf("\nSystem is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");
    return 1;
}

int main()
{
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    printf("\nEnter available resources: \n");
    for (int i = 0; i < m; i++)
    {
        printf("Resource %d: ", i + 1);
        scanf("%d", &available[i]);
    }

    printf("\nEnter maximum resources for each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Enter maximum resources for process %d: ", i + 1);
        for (int j = 0; j < m; j++)
        {

            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter allocated resources for each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Enter allocated resources for process %d: ", i + 1);
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }
    calculateNeed();
    checkSafeState();

    return 0;
}
