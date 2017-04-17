#include<stdio.h>
#include<math.h>
int x[20]={0};

int place(int k, int i)
{
	int j;
	for(j=1;j<k;j++)
		if(x[j]==i||(abs(x[j]-i)==abs(j-k)))
			return 0;
	return 1;
}

void nqueen(int k,int n)
{
	int i=1;
	for(i=1;i<=n;i++)
	{
		if(place(k,i))
		{
			x[k]=i;
			if(k==n)	
			{
				printf("\nSolution is : ");
				for(i=1;i<=n;i++)
					printf("\t%d",x[i]);
			}			
			else
				nqueen(k+1,n);
		}
	}
}

int main()
{
	int n;
	printf("Enter the no of Queen: ");
	scanf("%d",&n);
	nqueen(1,n);
	return 0;
}
