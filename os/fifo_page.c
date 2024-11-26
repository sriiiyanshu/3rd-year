#include<stdio.h>

int main()
{
    printf("Enter size of reference string");
    int n,m,i,j;
    scanf("%d",&n);
    int rs[n];
    for(i=0;i<n;i++)
    {
        scanf("%d",&rs[i]);
    }
    printf("Enter frame size");
    scanf("%d",&m);
    int f[m];
    for(i=0;i<m;i++)
    {
        f[i]= -1;
    }
    
    int faults=0;
    int flag=0,loc=0;

    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            if(f[j]==rs[i])
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            faults++;
            f[loc]=rs[i];
            loc++;
        }
        if(loc==m)
            loc=0;
        flag=0;
    }
    double hit_ratio=1.0*(n-faults)/n;
    
printf("Number of page faults: %d\n",faults);
printf("Number of hits= %d and hit ratio=%f\n",n-faults,hit_ratio);
return 0;
}