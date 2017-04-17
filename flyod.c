#include<stdio.h>

int main()	
{
	int n,a[10][10],i,j;
	void flyod(int a[10][10],int n);
	printf("Enter the no. of vertices in graph:");	
	scanf("%d",&n);
	printf("\nEnter the matrix(for inf enter 999):\n");	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&a[i][j]);

	printf("A0 matrix is:\n");		
	
	for(i=0;i<n;i++)
	{for(j=0;j<n;j++)
		{	printf("%d\t",a[i][j]);}
		printf("\n");
	}
	
	flyod(a,n);		
	return;
}

void flyod(int d[10][10],int n)
{
	int i,j,k,p[n][n];
	for(i=0;i<n;i++)	
		for(j=0;j<n;j++)
			p[i][j] = -1;
	for(k=0;k<n;k++)		
	{	for(i=0;i<n;i++)
		{	for(j=0;j<n;j++)
			{	if(d[i][j]>d[i][k]+d[k][j])
				{
					d[i][j] = d[i][k]+d[k][j];	 
					p[i][j] = k+1;
				}
			}
		}
		printf("matrix A%d is:\n",k+1);
		for(i=0;i<n;i++)					
		{	for(j=0;j<n;j++)
			{	printf("%d\t",d[i][j]);		
			}printf("\n");
		}
	}

	printf("Path from each vertex is:\n");		
	for(i=0;i<n;i++)
	{	for(j=0;j<n;j++)
		{	if(p[i][j]!=-1)
			printf("%d->%d->%d\n",i+1,p[i][j],j+1);
			else
			printf("%d->%d\n",i+1,j+1);
		}
	}
}

/*
	OUTPUT:
nandlal@nandlal-desktop:~$ cd Desktop
nandlal@nandlal-desktop:~/Desktop$ gcc flyod.c
nandlal@nandlal-desktop:~/Desktop$ ./a.out
Enter the no. of vertices in graph:4

Enter the matrix(for inf enter 999):
0 999 3 999
2 0 999 999
999 7 0 1
6 999 999 0
A0 matrix is:
0	999	3	999	
2	0	999	999	
999	7	0	1	
6	999	999	0	
matrix A1 is:
0	999	3	999	
2	0	5	999	
999	7	0	1	
6	999	9	0	
matrix A2 is:
0	999	3	999	
2	0	5	999	
9	7	0	1	
6	999	9	0	
matrix A3 is:
0	10	3	4	
2	0	5	6	
9	7	0	1	
6	16	9	0	
matrix A4 is:
0	10	3	4	
2	0	5	6	
7	7	0	1	
6	16	9	0	
Path from each vertex is:
1->1
1->3->2
1->3
1->3->4
2->1
2->2
2->1->3
2->3->4
3->4->1
3->2
3->3
3->4
4->1
4->3->2
4->1->3
4->4
nandlal@nandlal-desktop:~/Desktop$ 

*/
