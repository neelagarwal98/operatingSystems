//Neel Agarwal 

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
int min2(int arr1[],int arr2[]);
int main()
{
	int i,p,l,j,k,t,temp_q,x;// loop iterators and temporary variable
	int a,b;// for tracking time indices
	int pID[4];
	int burst_time[4];
	int tq; // time quantum
	int rbt[4];//remaining burst time
	int arrival_time[4];
	int gantt_chart[50];
	int time_index[50];
	int ready_queue[50];
	int sum_burst;//to store the total of burst times of all processes
	int size_TI,size_RQ;//to store respective sizes of time index and ready queue
	int wt[4];//to store the respective waiting time of all processes
	int tat[4];//to store the respective turn around time of all processes
	double avg_wt,avg_tat;
	
	int arrived_process[50];//array for searching minimum rbt
	int min_value;
	for(i=0;i<4;i++)
	{
		pID[i] = i;
	}//assigning process ID as the index value
	
	printf("\nEnter the arrival time in sequence:\n");
	for(i=0;i<4;i++)
	{
		scanf("%d",&at[i]);
	}
	
	printf("\nEnter the burst time in sequence:\n");
	for(i=0;i<4;i++)
	{
		scanf("%d",&bt[i]);
		rbt[i] = bt[i]; //copying burst time in an extra array for remaining 
	}
	
	printf("\n The details as fed are as under:");
	printf("\nProcess ID\tArrival Time\tBurst Time\n");
	for(i=0;i<4;i++)
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
	tq = 3;//for first iteration the time quantum is kept 3
	a = min(at);
	gc[0] = rq[0] = indexOf(a,at);
	time_index[0]=a;
	
	while(1) //break from loop when time_index equals sum of all burst times
	{
		p = rq[j];
		gc[j] = p;
		temp_q = -1;
		
		if(j==1)//second iteration
		{
			tq = 6;
		}
		if(rbt[p]>=tq)
		{
			b = a+tq;
			rbt[p]-= tq;
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
		for(l=0;l<4;l++)//l is a counter to traverse the process id or index
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
		if(j==2)//as soon as third iteration is entered
		{
			break;
		}
	}//end of while loop for round robin type scheduling
	
	i=2;//all the ready queue formed by round robin is discarded after 0 and 1th positions
	x=0;
	for(l=0;l<4;l++){
	if(at[l]<=b) 
	{
		arrived_process[x] = l;
		x++;
	}}//end of loop
	min_value = min2(rbt,arrived_process);
	rq[i] = indexOf(min_value,rbt);
	
	//loop for Preamptive SJF
	while(1) //break from loop when time_index equals sum of all burst times
	{
		p = rq[j];
		gc[j] = p;
		
		if(rbt[p]>=1)
		{
			b = a+1;
			rbt[p]-= 1;
		}
		x = 0;
		for(l=0;l<4;l++)//l is a counter to traverse the process id or index
		{ 
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
				arrived_process[x] = l;
				x++;
			}//all the indices of arrived processes by b time will be in the array
		}//end of for loop
		//for updating the ready queue
		++i;
		min_value = min2(rbt,arrived_process);
		rq[i] = indexOf(min_value,rbt); // return the index of minimum value of rbt among the arrived processes
		
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
    for(i=0;i<4;i++)//i is used here as the process ID
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
	for(i=0;i<4;i++)
	{
		sum1 = sum1 + wt[i];
		sum2 = sum2 + tat[i];
	}
	avg_wt = ((double)sum1)/4;
	avg_tat = ((double)sum2)/4;
	
	printf("\nAverage Waiting Time: %f\n",avg_wt);
	
	printf("\nAverage Turn Around Time: %f\n",avg_tat);
	
	/*printf("\nReady Queue:\n");
	for(i=0;i<=size_RQ;i++) 
	{
		printf("%d ",rq[i]);
	}
	
	printf("\nTime indices:\n");
	for(i=0;i<=size_TI;i++)
	{
		printf("%d ",time_index[i]);	
	}*/
	
}//end of main()
int min(int arr[])//function to find minimum element in arrival time
{
	int m_value = arr[0];
	int j;
	for(j=1;j<4;j++)
	{
		if(arr[j]<m_value)
		{
			m_value = arr[j];
		}
	}
	return m_value;
}
int min2(int arr1[],int arr2[])//function to find minimum element in arr1 but only from indices present in arr2
{
	int i=arr2[0];
	
	int m_value = arr1[i];
	int j;
	int d;
	for(j=1;j<(sizeof(arr2)/sizeof(int));j++)
		{
			d = arr2[j];
			if(arr1[d]<m_value)
			{
				m_value = arr1[d];
			}
		}//end of loop
	return m_value;
}

int indexOf(int value, int arr[])//function to find the index of first occurence in a given array
{
	int j;
	for(j=0;j<4;j++)
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
	for(j=0;j<4;j++)
	{
		sum = sum + arr[j];
	}
	//printf("%d\t",sum);
	return sum;
}

