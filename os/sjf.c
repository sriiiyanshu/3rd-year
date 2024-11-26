#include<stdio.h>

typedef struct{
    int id;
    int at;
    int bt;
    int ct;
}process;

int main()
{
    int n=5;
    process p[n],q[n];


    for(int i = 0; i < n; i++)
    {
        p[i].id = i+1;
        printf("Enter arrival time and burst time for process P%d",i+1);
        scanf("%d %d",&p[i].at,&p[i].bt);
    }

      //sort according to arrival time
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if(p[j].at > p[j+1].at)
            {
                process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int front=0, rear=1; 
    int time = p[0].at;
    q[front]=p[0];
    int i=1;

    while(i<n || front!=rear)
    {
        time += q[front].bt;
        for(int k=0;k<n;k++)
            {
                if(p[k].id == q[front].id)
                {
                    p[k].ct = time;
                    break;
                }
            }

        while(i<n && p[i].at <=time)
            {
                q[rear] = p[i];
                rear++;
                i++;
            }

        
    
        front++;

        for(int j=front+1; j<rear; j++)
        {
            if(q[front].bt>q[j].bt)
            {
                process temp = q[front];
                q[front] = q[j];
                q[j] = temp;
            }   
        }
    }

    //arrange p according to id
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if(p[j].id > p[j+1].id)
            {
                process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    printf("P\tAT\tBT\tCT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].ct);
    }

    return 0;
}