//1 fcfs
#include <stdio.h>

int main()
{
    double avgtat, avgwt;
    int at[] = {0,1,3,5};
    int et[] = {5,4,3,3};
    int ct[4], tat[4], wt[4];
    int i, stat=0,swt=0;
    ct[0] = at[0] + et[0] ;
    for(i=1;i<4;i++)
    {
        ct[i] = ct[i-1] + et[i];
    }
    for(i = 0; i<4; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - et[i];
    }
    for(i = 0; i<4; i++)
    {
        printf("%d      %d\n",tat[i],wt[i]);
        stat+=tat[i];
        swt+=wt[i];
    }
    avgtat=stat/4.0;
    avgwt=swt/4.0;
    printf("\n Avg tat=%f   Avg wt=%f",avgtat,avgwt);
    return 0;
}