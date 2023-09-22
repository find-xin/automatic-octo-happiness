#include<bits/stdc++.h>
using namespace std;
int n;
int a[11],b[11],c[11];
bool flag1[11];//flag1 refer to the people who need to get in the elevator
bool flag2[11];//flag2 refer to the people who haven't achieved their purposes
int path[1000],path1[1000];//record the path
int ele[5];//record who are in the elevator, 0 stands for none
int minn=100000000,stp;
int step,sum1,sum2;
int f1[11],f2[11];
int t,tim,m;
void prograss(int lo,int purpose)//to get the person who call the elevator,the extra things may happen
{
	while(true)
	{
		++t;
		if(purpose<lo) --lo;//elevator slowly moves to the floor
		if(purpose>lo) ++lo;
		if(sum1<n)
			for(int j=1;j<=n;++j)
				if(flag1[j]&&c[j]<t) ++tim;//count the waiting time
		for(int j=1;j<=4;++j)
		    if(b[ele[j]]==lo)
		    {
		    	flag2[ele[j]]=false;
		    	++sum2;++step;--m;
		    	f2[sum2]=ele[j];path1[step]=lo;
		    	ele[j]=0;
		    }//the people who want to get off
		if(purpose==lo) {++m;break;}//reach the floor
		for(int j=1;j<=n;++j)
			if(a[j]==lo&&flag1[j]&&t>=c[j]&&m<4)
			{
				for(int k=1;k<=4;++k)
					if(ele[k]==0)
					{
						ele[k]=j;
						break;
					}//people get in the elevator
				flag1[j]=false;
				++sum1;++step;++m;
				f1[sum1]=j;path1[step]=lo;
			}
	}
}
void search(int lo)
{
	int m1=m,t1=t,tim1=tim,sum11=sum1,sum22=sum2,step1=step;
	path1[step]=lo;
	if(sum2==n&&tim<minn)
	{
		stp=step;
		minn=tim;
		for(int i=1;i<=step;++i) path[i]=path1[i];
		return; 
	}
	 for(int i=1;i<=n;++i)
	 	if(flag1[i]&&t>=c[i])
	 	{
	 		prograss(lo,a[i]);
	 		if(m<=4)
	 	    {
	 	    	search(a[i]);
				 //reverse:
	 		    for(int j=sum11;j<=sum1;++j) {flag1[f1[j]]=true;f1[j]=0;}
	 		    for(int j=sum22;j<=sum2;++j) {flag2[f2[j]]=true;f2[j]=0;}//to some extent,f1 and flag1,f2 and flag2 are the same,but for the historical reasons,still use them 
	 		    t=t1;tim=tim1;step=step1;sum1=sum11;sum2=sum22;
	 	    }
	 	    m=m1;//reverse
	 	}
	for(int i=1;i<=4;++i)
		if(ele[i]!=0)
		{
			prograss(lo,b[i]);
			search(b[i]);
			//reverse:
			for(int j=sum11;j<=sum1;++j) {flag1[f1[j]]=true;f1[j]=0;}
			for(int j=sum22;j<=sum2;++j) {flag2[f2[j]]=true;f2[j]=0;}
			t=t1;tim=tim1;step=step1;sum1=sum11;sum2=sum22;
			m=m1;
		}
	return;  
}
int main()
{
	int lo;
	//scanf("%d",&lo);
	cin>>lo;
	while(true)
	{
		++n;
		scanf("%d",&a[n]);
		if(a[n]==-1) break;
		//scanf("%d%d",&b[n],&c[n]);
		cin>>b[n]>>c[n];
		flag1[n]=true;
		flag2[n]=true;
	}
	--n;
	path[1]=lo;
	search(lo);//refer to location
	for(int i=1;i<=stp;++i)
	{
		if(path[i]==path[i+1]) ++i;
	    printf("%d",path[i]);
		printf("->");
	}
}