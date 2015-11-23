#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int *x;
int *expr,*clauses,array[3];
int e;
int result;
int n;
char *output;
clock_t start,stop,ticks;
double diff;


void printtemparr(int *);
void printclauses();
void  compute( int *);
int allsatisfied1(int*,int);

int checkpromising(int depth,int *x)
{
	int i,j,val,temp;
	int *temparr= (int *)malloc(array[1]*array[2]*sizeof(int));
	//printf("At Depth:%d\n",depth);
	/*for(i=0;i<array[0];i++)
	{
		printf("value of x[%d]:%d",i,*(x+i));
	}*/
	if(depth==0)
	{
		return 1;
	}
	for(i=0;i<array[1];i++)
	{
		for(j=0;j<array[2];j++)
		{
			val= *(expr+(i*array[2]+j));
			//printf("%d\n",val);
			if(j==0)
			{
				if(val<0)
				{
					val=val*(-1);
					if((val-1)>=depth)
					{
						*(temparr+(i*array[2]+j))=1;
					}
					else
					{
						*(temparr+(i*array[2]+j))=!x[val-1];

					}
				}
				else
				{
					if((val-1)>=depth)
					{
						*(temparr+(i*array[2]+j))=1;
					}
					else
					{
					*(temparr+(i*array[2]+j))=x[val-1];
					}
				}
			}
			else
			{
				if(val<0)
				{
					val=val*(-1);
					if((val-1)>=depth)
					{
						*(temparr+(i*array[2]+j))=1;
					}
					else
					{
						*(temparr+(i*array[2]+j))=!x[val-1];

					}
				}
				else
				{

					if((val-1)>=depth)
					{
						*(temparr+(i*array[2]+j))=1;
					}
					else
					{
                        *(temparr+(i*array[2]+j))=x[val-1];
					}

				}
			}
		}
	}
	compute(temparr);
	//printclauses();
	//printtemparr(temparr);
	if(allsatisfied())
		return 1;
	else
		return 0;
}

void compute(int  *temparr)
{
	int i,j,val,e;
	for(i=0;i<array[1];i++)
	{
		for(j=0;j<array[2];j++)
		{
           		 if(*(temparr+(i*array[2]+j))==1)
            		{   
				clauses[i]=1;
				break;
			}
            		else
                		clauses[i] = 0;

		}
	}

}

void printclauses()
{
	int i;
	printf("\n  values of clauses\n");
	for(i=0;i<array[1];i++)
	{
		printf(" %d",*(clauses+i));
	}
}


void writetofile(int *x, int depth)
{
	int i;
	FILE *f1;
	if(array[0]<=5)
	{
		f1=fopen(output ,"a");
		fprintf(f1,"The solution is :\n");
		for(i=0;i<depth;i++)
		{
			fprintf(f1,"x[%d]:%d\n",  i,  *(x+i));
		}
	}
	else if(array[0]>5 && array[1]>30)
	{
		f1=fopen(output ,"a");
		fprintf(f1,"There are satisfying assignments\n");
		time(&stop);
	diff= ((double)stop-(double)start)/(double)(CLOCKS_PER_SEC*1000);     // calculate the time taken by calculating the difference between start and end timings
    	fprintf(f1,"\n Running time is %0.4f ms \n ",difftime(stop,start));
	fclose(f1);
	exit(0);

	}
	else if(array[0]>5&&array[1]<=30)
	{
		f1=fopen(output ,"a");
		fprintf(f1,"There are satisfying assignments\n");
		fprintf(f1,"The solution is :\n");
		for(i=0;i<depth;i++)
		{
			fprintf(f1,"x[%d]:%d\n",  i,  *(x+i));
		}
		time(&stop);
	diff= ((double)stop-(double)start)/(double)(CLOCKS_PER_SEC*1000);     // calculate the time taken by calculating the difference between start and end timing
    	fprintf(f1,"\n Running time is %0.4f ms \n ",difftime(stop,start));
	fclose(f1);
	exit(0);
	}
	fclose(f1);

}
void printtemparr(int  *temparr)
{
	int i;
	printf("\n  values of temparr\n");
	for(i=0;i<(array[1]*array[2]);i++)
	{
		printf(" %d",*(temparr+i));
	}
}

int  allsatisfied()
{
	int i;
	for(i=0;i<array[1];i++)
	{
		if(clauses[i]==0)
		{
			return 0;
		}
	}
	return 1;
}

void dfscompute(int depth,int n, int *x)
{	
	int i;
	int flag;
	//printf("depth in dfs compute:%d",depth);
	if(allsatisfied1(x,depth))
	{
		writetofile(x,depth);
		return;
	}
	if(checkpromising(depth,x))
	{
	*(x+depth)=1;
	dfscompute(depth+1,n,x);
	*(x+depth)=0;
	dfscompute(depth+1,n,x);
	}
}


int allsatisfied1(int *x , int depth)
{

int c1[array[0]];
int d1[array[0]];
int i=depth;

for(i=0;i<depth;i++)
{
	c1[i]=x[i];
	d1[i]=x[i];
}
for(i=depth;i<array[0];i++)
{
    *(c1+i) =0;
    *(d1+i) =1;
}
int j,val;

int clauses1[array[1]];
int clauses2[array[1]];

for(i=0;i<array[1];i++)
    {
        for(j=0;j<array[2];j++)
        {
            val= *(expr+(i*array[2]+j));
            if(j==0)
            {
                if(val<0)
                {
                    val=val*-1;
                    e= !c1[val-1];
                }
                else
                {
                e=c1[val-1];
                //*(clauses+i)=e;
                }
            }
            else
            {
                if(val <0)
                {
                    val=val*-1;
                    e=e | !c1[val-1];
                    *(clauses1+i)=e;
                }
                else
                {
                    e=  e | c1[val-1];
                    *(clauses1+i)=e;
                    //printf("%d",*(clauses+i));
                    //printf("%d", *(exp+(i*array[2]+j)));
                }
            }

        }
    }
for(i=0;i<array[1];i++)
{
        for(j=0;j<array[2];j++)
        {
            val= *(expr+(i*array[2]+j));
            if(j==0)
            {
                if(val<0)
                {
                    val=val*-1;
                    e= !d1[val-1];
                }
                else
                {
                e=d1[val-1];
                //*(clauses+i)=e;
                }
            }
            else
            {
                if(val <0)
                {
                    val=val*-1;
                    e=e | !d1[val-1];
                    *(clauses2+i)=e;
                }
                else
                {
                    e=  e | d1[val-1];
                    *(clauses2+i)=e;
                }
            }

        }
    }

	
int s1=1,s2=1;
for(i=0;i<array[1];i++)
{
	if(clauses1[i]==0)
	{
			s1=0;
	}
}
	for(i=0;i<array[1];i++)
	{
		if(clauses2[i]==0)
		{
			s2=0;
		}
	}

	if(s1 && s2)
    		return 1;
	else
    		return 0;

}

int main(int argc, char **argv)
{
	FILE *fp;
	ticks=clock();
	char ch;
	int data,size;
	output= argv[2];
	int i=0,j=0,flag,t,val,temp;
	expr=(int*) calloc(array[1]*array[2],sizeof(int));
	fp=fopen(argv[1],"r");
	time(&start);
	if(fp==NULL)
	{
		printf("\n Unable to open the file");
		return;
	}
	while(1)
	{
		if(feof(fp))
			break;	
		if(i==0||i==1||i==2)
		{
			fscanf(fp,"%d",&data);
			array[i]=data;
			i++;
		}
		else
		{
		
		fscanf(fp,"%d",&data);
		expr[j]=data;
		j++;
		}
	}
	/*for(i=0;i<3;i++)
	{
		printf("%d\n",array[i]);
	}
	for(i=0;i<array[1]*array[2];i++)
	{
		printf("%d",expr[i]);
	}
	*/
	n=array[0];  // no of variables
	x=(int *)calloc(array[0],sizeof(int));
	clauses=(int  *)calloc(array[1],sizeof(int));
	dfscompute(0,n,x);
	time(&stop);  // stop the clock
    	diff= ((double)stop-(double)start)/(double)(CLOCKS_PER_SEC*1000);     // calculate the time taken by calculating the difference between start and end timings
    	fp=fopen(output,"a");
	fseek(fp,0,SEEK_END);
	size=ftell(fp);
	if(size==0)
	{
	fprintf(fp,"\n No satisfying assignment\n");
	}
    	fprintf(fp,"\n Running time is %0.4f ms \n ",difftime(stop,start));
	fclose(fp);

	return 0;
}

