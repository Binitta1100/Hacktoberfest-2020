#include<stdio.h>
#include<stdlib.h>

void main()
{
    int n,i,j,l=0,f,m,p=1;
    float awt=0.0,att=0.0;
    printf("Enter the no.of processes:\n");
    scanf("%d",&n);
    int pid[100],bt[100],at[100],pr[100],bts[100][100];
    printf("Enter the processes-->\n");
    for(i=0; i<n; i++)
    {
        printf("Enter process id: ");
        scanf("%d",&pid[i]);
        printf("Enter arrival time: ");
        scanf("%d",&at[i]);
        printf("Enter burst time: ");
        scanf("%d",&bt[i]);
        printf("Enter priority:");
        scanf("%d",&pr[i]);
    }
    for(i=0; i<n-1; i++)
        for(j=0; j<n-i-1; j++)
            if(at[j]>at[j+1])
            {
                swap(&at[j],&at[j+1]);
                swap(&pid[j],&pid[j+1]);
                swap(&bt[j],&bt[j+1]);
                swap(&pr[j],&pr[j+1]);
            }
    bts[0][l]=pid[0];                                     //Pid row
    bts[1][l]=at[0];                                      //Arrival Time row
    bts[2][l]=bt[0];                                      //Burst Time row
    bts[3][l]=pr[0];                                      //Priority row
    bts[4][l]=0;                                          //Starting Time row
    bts[5][l++]=f=bt[0];                                  //Finish Time row
    i=1;
    j=i;
    for(; i<n; i++)
    {
        for(; j<n; j++)
        {
            if(at[j]<=f && l<n)
            {
                bts[0][l]=pid[j];
                bts[1][l]=at[j];
                bts[2][l]=bt[j];
                bts[3][l++]=pr[j];
            }
            else
                break;
        }
        for(m=p; m<l-1+p; m++)
            for(j=p; j<l-m-1+p; j++)
            {
                if(bts[3][j]>bts[3][j+1])
                {
                    swap(&bts[0][j],&bts[0][j+1]);
                    swap(&bts[1][j],&bts[1][j+1]);
                    swap(&bts[2][j],&bts[2][j+1]);
                    swap(&bts[3][j],&bts[3][j+1]);
                }
            }
        bts[4][i]=f;
        bts[5][i]=f+=bts[2][i];
        p=i+1;
        j=l;
    }
    for(i=0;i<n;i++)
    {
        bts[7][i]=bts[4][i]-bts[1][i];                             //Waiting Time row
        bts[6][i]=bts[2][i]+bts[7][i];                             //Turnaround Time row
    }
    printf("\nPId\tAT\tBT\tP\tTT\tWT\n");
    for(i=0;i<n;i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",bts[0][i],bts[1][i],bts[2][i],bts[3][i],bts[6][i],bts[7][i]);
    printf("\nGantt chart:\n");
    for(i=0;i<l;i++)
        printf("----------------");
    printf("\n");
    for(i=0; i<n; i++)
        printf("|\tP%d\t",bts[0][i]);
    printf("|\n");
    for(i=0;i<l;i++)
        printf("----------------");
    printf("\n");
    for(i=0;i<l;i++)
        printf("%d\t\t",bts[4][i]);
    printf("%d\n\n",bts[5][n-1]);
    for(i=0;i<n;i++)
    {
        awt+=bts[7][i];
        att+=bts[6][i];
    }
    awt/=n;
    att/=n;
    printf("Average turnaround time: %.2f\n", att);
    printf("Average waiting time: %.2f\n", awt);
}

void swap(int *x,int *y)
{
    int temp=*x;
    *x=*y;
    *y=temp;
}
