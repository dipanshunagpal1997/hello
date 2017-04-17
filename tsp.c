#include<stdio.h>
#include<math.h>
#define MAX 10
#define INF 999

int adjmat[MAX][MAX],path[MAX],n;
struct Bmat
{
	int B[MAX][MAX];
	int cost;
};
void printmat(int mat[MAX][MAX])
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			//printf("[%d][%d]=",i,j);
			printf("%d\t",mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
int searchmin(int i,int j,int flag,int mat[MAX][MAX])
{
	int x,y,z,min;
	//printmat(mat);
	if(flag==1)//row
	{
		min=mat[j][0];
		//printf("\nin if min%d\n",min);
		for(x=0;x<i;x++)
		{
			if(min>mat[j][x])
			min=mat[j][x];
		}
		//printf("\n%d\n",min);
		return min;
	}
	else//col
	{
		min=mat[0][j];
		//printf("\nin else min%d\n",min);
		for(x=0;x<i;x++)
		{
			if(min>mat[x][j])
			min=mat[x][j];
		}
		//printf("\nmin%d\n",min);
		return min;
	}
	
	
}


int perred(int row[10], int col[10],int mat[MAX][MAX],int flag)
{
	int i,j,k,redrow[10],redcol[10],sum=0;
	//printf("\nin pered");
	for(i=0;i<n;i++)
	{
		redrow[i]=0;
		redcol[i]=0;
		//printf("\nrow - %d", row[i]);
		//printf("\ncol- %d", col[i]);
	}
	for(i=0;i<n;i++)
	{
		if(row[i]!=0&&flag==1)
		{
			
			redrow[i]=searchmin(n,i,flag,mat);
			//printf("\nredrow=%d",redrow[i]);
			for(j=0;j<n;j++)
			{
				if(mat[i][j]!=999)
				mat[i][j]=mat[i][j]-redrow[i];
			}
			if(redrow[i]!=999)
			sum=sum+redrow[i];
		}	
		if(col[i]!=0&&flag==0)
		{
			
			redcol[i]=searchmin(n,i,flag,mat);
			//printf("\nredcol=%d",redcol[i]);
			for(j=0;j<n;j++)
			{
				if(mat[j][i]!=999)
				mat[j][i]=mat[j][i]-redcol[i];
			}
			if(redcol[i]!=999)
			sum=sum+redcol[i];
		}
		
	}
	
	return sum;
	
}
int checkred(int mat[MAX][MAX])
{
	int i,j,row[10],col[10],sum=0,k;
	for(i=0;i<n;i++)
	{
		row[i]=-1;
		col[i]=-1;
	}
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(mat[i][j]==0)	
			{
				row[i]=0;
				
			}
		}
	}
	k=1;
	for(i=0;i<n;i++)
	{
		if(row[i]!=0)
		{
			sum=perred(row,col,mat,k);
			break;
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(mat[i][j]==0)	
			{
				col[j]=0;
				
			}
		}
	}
	k=0;
	for(i=0;i<n;i++)
	{
		if(col[i]!=0)
		{
			sum+=perred(row,col,mat,k);
			break;
		}
	}
	
	printf("\nreduced matrix is:\n");
	printmat(mat);
	return sum;
}
 
int checknode(int p,int v)
{
	int i;
	for(i=0;i<v;i++)
	{
		if(p==path[i])
		return 0;
	}
	return 1;
}
int makemat(int src[MAX][MAX],int dest[MAX][MAX],int nv,int v)
{
	int i,j,k=0;
	for(i=0;i<n;i++)
	//printf("path=%d",path[i]);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			
			dest[i][j]=src[i][j];
		}
	}
	while(k<v)
	{
		i=path[k];
		//printf("\n in makemet while i=%d",i);
		for(j=0;j<n;j++)
		{
			dest[i][j]=999;
			//printf("dest[%d][%d]=%d",i,j,dest[i][j]);
			if(path[k+1]!=-1)
			dest[j][path[k+1]]=999;
			dest[j][nv]=999;
			dest[i][0]=999;
			dest[nv][0]=999;
		}
		k++;
	}
	//printf("\nin makemat\n");
	//printmat(dest);
	//printf("\n");
}
struct Bmat interm(int v,int snm[MAX][MAX],int cr)
{
	int i,j=0,min,k,cost[MAX][2],r,c;
	struct Bmat inm[MAX];
	int nv[MAX];
	for(i=0;i<n;i++)
	{
		if(checknode(i,v))
		{
			nv[j]=i;
			j++;
		}
	}
	for(i=0;i<n-v;i++)
	{
		r=0;
		if(v==1)
		makemat(adjmat,inm[nv[i]].B,nv[i],v);
		else
		makemat(snm,inm[nv[i]].B,nv[i],v);
		r=checkred(inm[nv[i]].B);
		cost[i][0]=cr + adjmat[path[v-1]][nv[i]]+r; 
		//printf("%d+%d+%d",cr , adjmat[v-1][nv[i]],r);
		cost[i][1]=nv[i];
	}
	min=cost[0][0];
	k=cost[0][1];
	for(i=1;i<n-v;i++)
	{
		if(min>cost[i][0])
		{
			min=cost[i][0];
			
			k=cost[i][1];
		}
		
	}
	for(i=0;i<n-v;i++)
	{
		printf("cost %d node %d\t",cost[i][0],cost[i][1]);
	}
	for(i=0;i<n-v;i++)
	{
		if(min==cost[i][0])
		c=cost[i][1];
	}
	printf("\nthe min among node is %d and cost is %d",c,min);
	printf("\nso we expand node %d:\n",c);
	printf("\n");
	inm[k].cost=min;
	path[v]=k;
	return inm[k];
	
	
}

int tsp()
{
	int i,cr;
	struct Bmat snm;
	cr=checkred(adjmat);
	printf("Initial cost is :%d\n",cr);
	//printmat(adjmat);
	path[0]=0;
	for(i=1;i<n;i++)
	{
		path[i]=-1;
		
	}
	for(i=1;i<n;i++)
	{
		snm=interm(i,snm.B,cr);
		cr=snm.cost;
		
	}
	
	path[n]=0;
	for(i=0;i<=n;i++)
	printf("%d->",path[i]); 
	printf("\n");
}
void main()
{
	int i,j,k;
	
	printf("enter the no of nodes in graph\n");
	scanf("%d",&n);
	printf("enter the Cost matrix enter 999 if no edge is present\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			//printf("[%d][%d]",i,j);
			scanf("%d",&adjmat[i][j]);
		}
	}
	tsp();
	
}

// Output //
/*
nandlal@nandlal-desktop:~$ cd Desktop
nandlal@nandlal-desktop:~/Desktop$ gcc tsp.c
tsp.c: In function ‘main’:
tsp.c:283: warning: return type of ‘main’ is not ‘int’
nandlal@nandlal-desktop:~/Desktop$ ./a.out
enter the no of nodes in graph
5
enter the Cost matrix enter 999 if no edge is present
999 20 30 10 11
15 999 16 4 2
3 5 999 2 4
19 6 18 999 3
16 4 7 16 999

reduced matrix is:
999	10	17	0	1	
12	999	11	2	0	
0	3	999	0	2	
15	3	12	999	0	
11	0	0	12	999	

Initial cost is :25

reduced matrix is:
999	999	999	999	999	
999	999	11	2	0	
0	999	999	0	2	
15	999	12	999	0	
11	999	0	12	999	


reduced matrix is:
999	999	999	999	999	
1	999	999	2	0	
999	3	999	0	2	
4	3	999	999	0	
0	0	999	12	999	


reduced matrix is:
999	999	999	999	999	
12	999	11	999	0	
0	3	999	999	2	
999	3	12	999	0	
11	0	0	999	999	


reduced matrix is:
999	999	999	999	999	
10	999	9	0	999	
0	3	999	0	999	
12	0	9	999	999	
999	0	0	12	999	

cost 35 node 1	cost 53 node 2	cost 25 node 3	cost 31 node 4	
the min among node is 3 and cost is 25
so we expand node 3:


reduced matrix is:
999	999	999	999	999	
999	999	11	999	0	
0	999	999	999	2	
999	999	999	999	999	
11	999	0	999	999	


reduced matrix is:
999	999	999	999	999	
1	999	999	999	0	
999	1	999	999	0	
999	999	999	999	999	
0	0	999	999	999	


reduced matrix is:
999	999	999	999	999	
1	999	0	999	999	
0	3	999	999	999	
999	999	999	999	999	
999	0	0	999	999	

cost 28 node 1	cost 50 node 2	cost 36 node 4	
the min among node is 1 and cost is 28
so we expand node 1:


reduced matrix is:
999	999	999	999	999	
999	999	999	999	999	
999	999	999	999	0	
999	999	999	999	999	
0	999	999	999	999	


reduced matrix is:
999	999	999	999	999	
999	999	999	999	999	
0	999	999	999	999	
999	999	999	999	999	
999	999	0	999	999	

cost 52 node 2	cost 28 node 4	
the min among node is 4 and cost is 28
so we expand node 4:


reduced matrix is:
999	999	999	999	999	
999	999	999	999	999	
999	999	999	999	999	
999	999	999	999	999	
999	999	999	999	999	

cost 28 node 2	
the min among node is 2 and cost is 28
so we expand node 2:

0->3->1->4->2->0->
nandlal@nandlal-desktop:~/Desktop$ 


*/
