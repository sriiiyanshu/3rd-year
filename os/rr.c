#include<stdio.h>

typedef struct{
    int id;
    int at;
    int bt;
    int ct;
}process;

int main()
{
    printf("Enter number of processes:");
    int n;
    scanf("%d", &n);
    process p[n],rq[64];
    int tq = 2;
    int front=0,rear=1;
    
    for (int i = 0; i < n; i++)
    {
        p[i].id = i+1;
        printf("Enter arrival time and burst time for P%d: ",i+1);
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

    rq[front] = p[0];
    int time = p[0].at;
    int i=1;
    while(i<n || front!=rear)
    {
        
        if(rq[front].bt > tq)
        {
            time += tq;
            rq[front].bt -= tq;
            while(i<n && p[i].at <=time)
            {
                rq[rear] = p[i];
                rear++;
                i++;
            }
            rq[rear++] = rq[front];
        }

        else
        {
            time += rq[front].bt;
            for(int k=0;k<n;k++)
            {
                if(p[k].id == rq[front].id)
                {
                    p[k].ct = time;
                    break;
                }
            }
        }

        front++;
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