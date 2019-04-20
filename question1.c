/*Ques. 1. Considering 4 processes with the arrival time and the burst time requirement of the processes the scheduler 
schedules the processes by interrupting the processor after every 3 units of time and does consider the completion of the 
process in this iteration. The schedulers then checks for the number of processes waiting for the processor and allots the 
processor to the process but interrupting the processor after every 6 units of time and considers the completion of the
 process in this iteration. The scheduler after the second iteration checks for the number of processes waiting for the 
 processor and now provides the processor to the process with the least time requirement to go in the terminated state.
The inputs for the number of requirements, arrival time and burst time should be provided by the user.
*/
#include<stdio.h>
//#include<conio.h>
#include<unistd.h>
#define at arrival_time
#define bt burst_time
#define gc gantt_chart
#define rq ready_queue
int indexOf(int value, int arr[]);
int findSum(int arr[]);
int min(int arr[]);
int max(int arr[]);
int min2(int arr[]);
int checkSecond(int arr[],int len);
int main()
{
	int i,p,l,j,k,t,temp_q,a,b;// loop iterators and temporary variable
	int pID[4];
	int tq; //time quantum
	int burst_time[4];
	int rbt[4];//remaining burst time
	int arrival_time[4];
	int gantt_chart[150];
	int time_index[150];
	int ready_queue[150];
	int sum_burst;//to store the total of burst times of all processes
	int size_TI,size_GC;//to store respective sizes of time index and gantt chart
	int wt[4];//to store the respective waiting time of all processes
	int tat[4];//to store the respective turn around time of all processes
	double avg_wt,avg_tat;
	int flag2;//tracker for completion of first iteration and to put processIds of second iteration in another array
	int second_ite[100];//the other array
	int x;//loop iterators
	
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
	
	sum_burst = findSum(bt);//to the find the total of all burst times in order to set the boundary
	//printf("\n%d",sum_burst);
	
	i=0;//counter for ready queue update
	p=0;//to refer to current position of traversal in ready queue
	j=0;//counter for gantt chart
	t=0;//counter for time index
	temp_q=0; //temporary variable when the process still left with burst time has to wait for others to get added to queue
	a=0;
	b=0;
	
	flag2=0;
	x=0;//counter for second_ite[] 
	
	tq=3;//initially time quantum has to be 3
	a = min(at);
	gc[0] = rq[0] = indexOf(a,at);
	time_index[0]=a;
	
	while(1) //break from loop when condition for second iteration is also over
	{
		p = rq[j];
		gc[j] = p;
		temp_q = -1;
		
		if(!(p>=0&&p<=3))//to avoid the occurrence of segmentation fault
		{
			t=j+1;
			break;
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
				if(flag2==1)//means if this is the second iteration
				{
					second_ite[x] = rq[i];
					x++;
				}
				
			}
		}//end of loop
		if(temp_q>=0)//to add to end of ready queue, refer to #1 
		{
			i++;
			rq[i]= temp_q;
		}
		if(b>=max(at))//condition for end of 1st iteration
		{
			tq=6;
			flag2=1;
		}
		
		time_index[t+1] = b;
		a=b;
		t+=1;
		j+=1;
		
		int check = checkSecond(second_ite,x);
		if(check == 1)
		{
			t = j+1;
			break;
		}//i.e. if second iteration is over break from the loop of round robin
		//at this point the gantt chart is ready till j-1 position
		//so we drop the ready queue in between i and current position of j
		
	}//end of while loop
	while(1)//loop for non - preamptive SJF
	{
		
		if(time_index[t-1] == sum_burst)//code to break from loop
		{
			size_GC = j;
			size_TI = t;
			break;
		}
		
		p = indexOf(min2(rbt),rbt);//min2 is to calculate min burst time non-zero
		gc[j] = p;//updating gantt chart with id of minimum burst time 
		time_index[t] = time_index[t-1] + min2(rbt);
		rbt[p] = 0;//updating remaining burst time
		t+=1;
		j+=1;//updating counters
		
	}
	
    //calculating the waiting time and turn around time
    for(i=0;i<4;i++)//i is used here as the process ID
    {
    	int temp = 0;
    	//wt[i]=0;
    	//tat[i]=0;
    	int flag=0;//tracker for first occurence of process ID in gantt chart
    	for(j=0;j<size_GC;j++)
    	{
    		if(i == gc[j] && flag==0)
    		{
    			wt[i] = time_index[j] - arrival_time[i]; //response time - arrival time
    			temp = time_index[j+1]; //temporary variable to store completion time of previous occurrence
    			flag = 1;
    			continue;
			}
			if(i == gc[j] && flag==1)//if second or further occurence
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
	
	printf("\nGantt Chart:\n");
	for(i=0;i<size_GC;i++) //check again
	{
		printf("%d ",gc[i]);
	}
	
	printf("\nTime indices:\n");
	for(i=0;i<size_TI;i++)
	{
		printf("%d ",time_index[i]);	
	}
	
}//end of main()
int min(int arr[])//function to find minimum element in any array
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
int min2(int arr[])//function to find minimum element in rbt except for 0
{
	int n;
	int m_value;
	for(n=0;n<4;n++)
	{
		if(arr[n]!=0)
		{
			m_value=arr[n];
			break;
		}
	}//just to initiallise m_value with first non-zero element 
	
	int j;
	for(j=n;j<4;j++)
	{
		if(arr[j]<m_value && arr[j]!=0)
		{
			m_value = arr[j];
		}
	}
	return m_value;
}
int max(int arr[])//function to find maximum element in any array
{
	int m_value = arr[0];
	int j;
	for(j=1;j<4;j++)
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
int checkSecond(int arr[],int len)//function that checks if second iteration is over
{
	int a,b,c,d;
	a=b=c=d=0;
	
	int i;
	for(i=0;i<len;i++)
	{
		if(arr[i]==0)a++;
		if(arr[i]==1)b++;
		if(arr[i]==2)c++;
		if(arr[i]==3)d++;
	}
	if(a!=0 && b!=0 && c!=0 && d!=0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

