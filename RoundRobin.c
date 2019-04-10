//Neel Agarwal program for Round Robin (Operating Systems) 8th April,2019

#include<stdio.h>
#include<conio.h>
#include<unistd.h>
#define at arrival_time
#define bt burst_time
#define gc gantt_chart
#define rq ready_queue
int indexOf(int value, int arr[]);
int findSum(int arr[]);
int min(int arr[]);
int main()
{
	int i,p,l,j,k,t,temp_q,a,b;// loop iterators and temporary variable
	int pID[6];
	int burst_time[6];
	int rbt[6];//remaining burst time
	int arrival_time[6];
	int gantt_chart[50];
	int time_index[50];
	int ready_queue[50];
	int sum_burst;//to store the total of burst times of all processes
	int size_TI,size_RQ;//to store respective sizes of time index and ready queue
	int wt[6];//to store the respective waiting time of all processes
	int tat[6];//to store the respective turn around time of all processes
	double avg_wt,avg_tat;
	
	for(i=0;i<6;i++)
	{
		pID[i] = i;
	}//assigning process ID as the index value
	
	printf("\nEnter the arrival time in sequence:\n");
	for(i=0;i<6;i++)
	{
		scanf("%d",&at[i]);
	}
	
	printf("\nEnter the burst time in sequence:\n");
	for(i=0;i<6;i++)
	{
		scanf("%d",&bt[i]);
		rbt[i] = bt[i]; //copying burst time in an extra array for remaining 
	}
	
	printf("\n The details as fed are as under:");
	printf("\nProcess ID\tArrival Time\tBurst Time\n");
	for(i=0;i<6;i++)
	{
		printf("%d\t\t%d\t\t%d\n",pID[i],at[i],bt[i]);
	}
	
	//task of input over
	sum_burst = findSum(bt);
	//printf("\n%d",sum_burst);
	
	i=0;//counter for ready queue update
	p=0;//to refer to current position of traversal in ready queue
	j=0;//counter for gantt chart
	t=0;//counter for time index
	temp_q=0;
	a=0;
	b=0;
	
	a = min(at);
	gc[0] = rq[0] = indexOf(a,at);
	time_index[0]=a;
	
	while(1) //break from loop when time_index equals sum of all burst times
	{
		p = rq[j];
		gc[j] = p;
		temp_q = -1;
		
		if(rbt[p]>=2)
		{
			b = a+2;
			rbt[p]-= 2;
		}
		else
		{
			
			b = a + rbt[p];
			rbt[p] = 0;
		}
		
		if(rbt[p]>0)
		{
			temp_q = gc[j];
		}//to maintain ready queue if still remaining time is > 0  #1
		
		//for updating the ready queue
		for(l=0;l<6;l++)//l is a counter to traverse the process id or index
		{
			//to avoid including processes in ready queue which have already arrived 
			int flag = 0;
			for(k=0;k<=i;k++)
			{
				if(l == rq[k])
				{
					flag=1;
				}
			}
			if(flag==1)
			{
				continue;
			}
			
			//to include all processes arrived by time b in the ready queue
			if(at[l]<=b)
			{
				i++;
				rq[i] = l;
			}
		}//end of loop
		if(temp_q>=0)//to add to end of ready queue, refer to #1 
		{
			i++;
			rq[i]= temp_q;
		}
		
		time_index[t+1] = b;
		a=b;
		t+=1;
		j+=1;
		
		//code to break from loop
		if(b == sum_burst)
		{
			size_RQ = i;
			size_TI = i+1;
			break;
		}
	}//end of while loop
    
    //calculating the waiting time and turn around time
    for(i=0;i<6;i++)//i is used here as the process ID
    {
    	int temp = 0;
    	//wt[i]=0;
    	//tat[i]=0;
    	int flag=0;//tracker for first occurence of process ID in gantt chart
    	for(j=0;j<=size_RQ;j++)
    	{
    		if(i == gc[j] && flag==0)
    		{
    			wt[i] = time_index[j] - arrival_time[i]; //response time - arrival time
    			temp = time_index[j+1]; //temporary variable to store completion time of previous occurrence
    			flag = 1;
    			continue;
			}
			if(i == gc[j])//if second or further occurence
			{
				wt[i] = wt[i] + (time_index[j] - temp);
				temp = time_index[j+1];
			}
		}
    	tat[i] = wt[i] + bt[i];
	}//calcution of individual WT and TAT ceased
	
	int sum1,sum2;
	sum1=sum2=0;
	for(i=0;i<6;i++)
	{
		sum1 = sum1 + wt[i];
		sum2 = sum2 + tat[i];
	}
	avg_wt = ((double)sum1)/6;
	avg_tat = ((double)sum2)/6;
	
	printf("\nAverage Waiting Time: %f\n",avg_wt);
	
	printf("\nAverage Turn Around Time: %f\n",avg_tat);
	
	printf("\nReady Queue:\n");
	for(i=0;i<=size_RQ;i++) //check again
	{
		printf("%d ",rq[i]);
	}
	
	printf("\nTime indices:\n");
	for(i=0;i<=size_TI;i++)
	{
		printf("%d ",time_index[i]);	
	}
	
}//end of main()
int min(int arr[])//function to find minimum element in any array
{
	int m_value = arr[0];
	int j;
	for(j=1;j<6;j++)
	{
		if(arr[j]<m_value)
		{
			m_value = arr[j];
		}
	}
	return m_value;
}

int indexOf(int value, int arr[])//function to find the index of first occurence in a given array
{
	int j;
	for(j=0;j<6;j++)
	{
		if(arr[j]==value)
		{
			return j;
		}
	}
	return -1;
}
int findSum(int arr[])// function to find sum of elements of an array
{
	int j;
	int sum=0;
	for(j=0;j<6;j++)
	{
		sum = sum + arr[j];
	}
	//printf("%d\t",sum);
	return sum;
}

