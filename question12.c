/*Ques. 12. Three students (a, b, c) are arriving in the mess at the same time. The id numbers of these students are 
taken time 2132, 2102, 2453 and the food from the mess table is 2, 4 and 8 minutes. If the two students have same remaining
time so it is broken by giving priority to the students with the lowest id number. Consider the longest remaining time first
(LRTF) scheduling algorithm and calculate the average turnaround time and waiting time.*/

#include<stdio.h>
#include<conio.h>
#include<unistd.h>

#define bt burst_time
#define gc gantt_chart
#define rq ready_queue
int indexOf(int value, int arr[]);
int findSum(int arr[]);
int max(int arr[]);
int main()
{
	int i,p,j,t;// loop iterators 
	int A,B;//for time indices response and completion respectively at each iteration for each process
	int pID[3];//array to store process IDs
	int burst_time[4];
	int rbt[3];//remaining burst time
	int gantt_chart[50];
	int time_index[50];
	int ready_queue[50];
	int sum_burst;//to store the total of burst times of all processes
	int size_TI,size_RQ;//to store respective sizes of time index and ready queue
	int wt[3];//to store the respective waiting time of all processes
	int tat[3];//to store the respective turn around time of all processes
	double avg_wt,avg_tat; //average waiting time and turn around time
	int a,b,c; //Names of processes
	
	printf("\nEnter the id numbers of students a,b,c respectively:\n");
	scanf("%d",&a);
	scanf("%d",&b);
	scanf("%d",&c);
	
	//code to assign Process IDs in sorted form in pID array
	if(a<b&&a<c)
	{
		pID[0] = a;
		if(b<c)
		{
			pID[1] = b;
			pID[2] = c;
		}
		else
	    {
	    	pID[1] = c;
	    	pID[2] = b;
		}
	}
	if(b<a&&b<c)
	{
		pID[0] = b;
		if(a<c)
		{
			pID[1] = a;
			pID[2] = c;
		}
		else
	    {
	    	pID[1] = c;
	    	pID[2] = a;
		}
	}
	if(c<a&&c<b)
	{
		pID[0] = c;
		if(a<b)
		{
			pID[1] = a;
			pID[2] = b;
		}
		else
	    {
	    	pID[1] = b;
	    	pID[2] = a;
		}
	}
	//since pID array contains process IDs in sorted form, we can use index in iterations
	printf("\nEnter the burst time in sequence:\n");
	for(i=0;i<3;i++)
	{
		scanf("%d",&bt[i]);
		rbt[i] = bt[i]; //copying burst time in an extra array for remaining 
	}
	
	printf("\n The details as fed are as under:");
	printf("\nProcess ID\tBurst Time\n");
	for(i=0;i<3;i++)
	{
		if(pID[i] == a) {printf("%d(a)\t\t%d\n",pID[i],bt[i]);}
		if(pID[i] == b) {printf("%d(b)\t\t%d\n",pID[i],bt[i]);}
		if(pID[i] == c) {printf("%d(c)\t\t%d\n",pID[i],bt[i]);}
		
	}
	
	//task of input over
	sum_burst = findSum(bt);
	//printf("\n%d",sum_burst);
	
	i=0;//counter for ready queue update
	p=0;//to refer to current position of traversal in ready queue
	j=0;//counter for gantt chart
	t=0;//counter for time index
	A=0;
	B=0;
	
	A = 0;
	gc[0] = rq[0] = indexOf(max(rbt),rbt);
	time_index[0] = A;
	
	while(1) //break from loop when time_index equals sum of all burst times
	{
		p = rq[j];
		gc[j] = p;
		
		if(rbt[p]>=1)
		{
			B = A+1;
			rbt[p]-= 1;
		}
		
		//for updating the ready queue
		++i;
		rq[i] = indexOf(max(rbt),rbt);
		
		//end of loop
		time_index[t+1] = B;
		A=B;
		t+=1;
		j+=1;
		
		//code to break from loop
		if(B == sum_burst)
		{
			size_RQ = i;
			size_TI = i+1;
			break;
		}
	}//end of while loop
    
    //calculating the waiting time and turn around time
    for(i=0;i<3;i++)//i is used here as the process ID
    {
    	int temp = 0;
    	//wt[i]=0;
    	//tat[i]=0;
    	int flag=0;//tracker for first occurence of process ID in gantt chart
    	for(j=0;j<=size_RQ;j++)
    	{
    		if(i == gc[j] && flag==0)
    		{
    			wt[i] = time_index[j] - 0; //response time - arrival time
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
	for(i=0;i<3;i++)
	{
		sum1 = sum1 + wt[i];
		sum2 = sum2 + tat[i];
	}
	avg_wt = ((double)sum1)/3;
	avg_tat = ((double)sum2)/3;
	
	printf("\nAverage Waiting Time: %f\n",avg_wt);
	
	printf("\nAverage Turn Around Time: %f\n",avg_tat);
	
	printf("\nGantt Chart:\n");
	for(i=0;i<size_RQ;i++) 
	{
		int d = rq[i];
		pID[d];
		if(pID[d] == a) {printf("a ");}
		if(pID[d] == b) {printf("b ");}
		if(pID[d] == c) {printf("c ");}
	}
	
	printf("\nTime indices:\n");
	for(i=0;i<size_TI;i++)
	{
		printf("%d ",time_index[i]);	
	}
	
}//end of main()
int max(int arr[])//function to find maximum element in any array
{
	int m_value = arr[0];
	int j;
	for(j=1;j<3;j++)
	{
		if(arr[j]>m_value)
		{
			m_value = arr[j];
		}
	}
	return m_value;
}

int indexOf(int value, int arr[])//function to find the index of first occurence in a given array
{
	int j;
	for(j=0;j<3;j++)
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
	for(j=0;j<3;j++)
	{
		sum = sum + arr[j];
	}
	//printf("%d\t",sum);
	return sum;
}

