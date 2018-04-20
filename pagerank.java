import java.util.Scanner;


public class pagerank {
	double pagerank[] = new double[10];
	int path[][] = new int[10][10];
	
	public void calc(double n)
	{
		double temp[] = new double[10];
		double init_rank = 1/n;
		double df = 0.85;
		double outgoing;
		int i,k,inode,exnode;
		System.out.println("Init Page Rank: "+init_rank);
		System.out.println("Step 0 ");
		
		for(k=1;k<=n;k++)
		{
			this.pagerank[k] = init_rank;
			System.out.println("\nPage Rank of "+k+" : "+this.pagerank[k]);
		}

		for(i=1;i<=2;i++)
		{
			for(k=1;k<=n;k++)
			{
				temp[k] = this.pagerank[k];
				this.pagerank[k] = 0;
			}
		
			for(inode = 1;inode<=n;inode++)
			{
				for(exnode = 1;exnode<=n;exnode++)
				{
					if(this.path[exnode][inode]==1)
					{
						outgoing = 0;
						for(k=1;k<=n;k++)
						{
							if(this.path[exnode][k]==1)
								outgoing=outgoing+1;
						}
						this.pagerank[inode]+=temp[exnode]*(1/outgoing);
						
					}
				}
			}
			System.out.println("\nStep :"+i);
			for(k=1;k<=n;k++)
			{
				System.out.println("\nPage Rank of "+k+" : "+this.pagerank[k]);
			}
		}
		for(k=1;k<=n;k++)
		{
			this.pagerank[k] = (1 - df) + df*this.pagerank[k];
		}
		System.out.println("\n Final Page Rank");
		for(k=1;k<=n;k++)
		{
			System.out.println("\nPage Rank of "+k+" : "+this.pagerank[k]);
		}
		
	}
	
	public static void main(String[] args) {
		int i,j,n;
		Scanner s = new Scanner(System.in);
		System.out.println("Enter the no. of nodes: ");
		n = s.nextInt();
		pagerank p = new pagerank();
		System.out.println("Enter the adjacency matrix: ");
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
			{
				p.path[i][j] = s.nextInt();
				if(i==j)
					p.path[i][j]=0;
			}
		p.calc(n);
		s.close();
	}

}
