//整个程序是按照LOOK和SCAN算法结合设计的，并且掺入了一丢丢个人想法
//为减少乘客的等待电梯时间，在电梯未满客的情况下，优先去接人而非送人到目的地
//接人时优先呼叫时间最早的，然后是方向一致的
//送人时优先方向一致的(进电梯后就是一家人了，不分彼此），然后是最近的（狗头）
//当然在执行这些命令时，会出现突然间有人刚好在要运行的楼层呼叫 ——————————怎么办？堵门！！！（自然是不行的）————————先生请上
//突发情况可能会导致电梯满员，而无法按预期抵达呼叫人的楼层，此时会紧急处理——————只能请先生稍等了（微笑）————————先去送人
#include<stdio.h>
int n;//乘客总人数
int a[1000],b[1000],c[1000];//a[]呼叫人所在楼层,b[]乘客要去往的彼岸（），c[]呼叫的时间
int path[1000],step;//记录关键楼层
int m,ele[5],number[1000];//m表示电梯里的人数，ele[]中记录的是电梯里的人的编号（已经过排序后的编号）,number[]记录电梯中的人数
int flag[1000];//判断该人是否已经接过（不一定在电梯里，可能已经送到了）
int direct=1;//o(*￣▽￣*)o，1表示上楼，0表示下楼
int sum1,sum2;//sum1表示接过的人数，sum2表示已经送到的人数
int t;//表示已经过去的时间
int time[1000];
int lo;//电梯当前的位置
int abs(int p)
{
	if(p>0) return p;
	else return -p;
}
void swap(int i,int j)
{
	int temp1=a[j],temp2=b[j],temp3=c[j];
	a[j]=a[i];a[i]=temp1;
	b[j]=b[i];b[i]=temp2;
	c[j]=c[i];c[i]=temp3;
}//交换一下呼叫人的信息
void qsort(int l,int r)
{
	int i=l,j=r;
	int mid=(l+r)>>1;
	while(i<=j)
	{
		while(c[i]<c[mid]) ++i;
		while(c[j]>c[mid]) --j;
		if(i<=j) {swap(i,j);++i;--j;}
	}
	if(l<j) qsort(l,j);
	if(r>i) qsort(i,r);
}//根据呼叫时间进行排序，方便后续接人

//prograss执行下达的指令————敬业的打工狗—————如遇突发情况无法完成指令，会请求总部重新下达指令
void prograss(int purpose,int k,int f1)//purpose 表示目的地，接人或者送人,k记录的是该目标乘客的编号,f1 1表示去接人，0表示送人
{ 
	while(1)
	{
		if(m>0)
		    for(int j=1;j<=4;++j)
		        if(b[ele[j]]==lo)
		        {
		    	    flag[ele[j]]=0;
		    	    ++sum2;++step;--m;
		    	    path[step]=lo;time[step]=t;number[step]=m;
		    	    ele[j]=0;//删除下电梯的人在ele[]中的编号
		        }//经过楼层时顺路下电梯
		if(purpose==lo) 
		{
		    if(f1) 
			{
				++m;
			    flag[k]=0;
				++sum1;
			    for(int j=1;j<=4;++j)
			        if(ele[j]==0)
			        {
			        	ele[j]=k;
			        	break;
			        }//寻找ele[]中的空位填上
				++step;
				path[step]=lo;time[step]=t;number[step]=m;
			}
			break;//到达目的地，下电梯和上电梯的目的都已经达成，跳出循环，去寻找下一个目的地
		}
		//下面是到达目的地之前遇到的突发情况
		for(int j=1;j<=n;++j)
		{
			if(m==4) break;//满员的情况下不能接人，接人终止
			if(a[j]==lo&&flag[j]&&t>=c[j])//接人的条件
			{
				for(int k=1;k<=4;++k)
					if(ele[k]==0)
					{
						ele[k]=j;
						break;
					}//填上空位
				flag[j]=0;//此人已被上过电梯
				++sum1;++step;++m;
				path[step]=lo;time[step]=t;number[step]=m;
			}
		}
		if(m==4&&f1) break;//本来想要接人，但满员了，只能中断指令，去送人
		//电梯前往下一个楼层
		++t;
		if(purpose<lo) --lo;
		if(purpose>lo) ++lo;
	}
}

//LOOKSCAN下达指令
void LOOKSCAN()
{
	int f=0;//f是用来判断在现在这个时刻电梯是否需要工作，首先判断是否有人呼叫，0表示没有，如果是0就继续判断是否有人要送
	int num;//记录谁是目前还没送走（），最先呼叫的人
	if(m<4&&sum1<n)
	{
		int i=1;
	    while(flag[i]==0) ++i;//寻找目前最先呼叫人
	    num=i;
	    if(c[i]<=t)
	    {
	    	f=1;//现在有人呼叫
	        int k=i;//k是用来寻找谁是最先呼叫人且方向一致的人
	        int flg=0;//记录是否存在该人
    	    while(c[k]==c[i])
	        {
	        	if(direct==(a[k]>lo))
		        {
		        	i=k;//记录一下该人
		        	flg=1;
					break;
		        }
		        ++k;
		    }//寻找中......
	        if(flg==0)//不存在该人，调头！！！ 					
			    if(direct==0) direct=1;
				else direct=0;
			prograss(a[i],i,1);//去接人咯
	    }
	}
	if((m==4||sum1==n||!f)&&m>=1)//满员，人接完了，没人呼叫且电梯中还有人——————加油，要下班了
	{
		int k;
		int flg=0;//判断电梯中的人是否有方向一致的，先送走
		int minn=100;
		for(int i=1;i<=4;++i)
			if(direct==(lo<b[ele[i]])&&ele[i]!=0)//寻找大道相同的人（）
			{
				f=1;//电梯需要工作
				flg=1;//有方向一致的
				if(minn>abs(lo-b[ele[i]]))
				{
					minn=abs(lo-b[ele[i]]);
					k=ele[i];
				}//记录方向一致的且最近的天选之子
			}
		if(flg==0) //没有方向一致的，寻找最近的
			for(int i=1;i<=4;++i)
				if(ele[i]!=0&&abs(lo-b[ele[i]])<minn)
				{
					f=1;//电梯需要工作
					k=ele[i];
					if(direct==0) direct=1;
					else direct=0;
					minn=abs(lo-b[ele[i]]);
				}
		prograss(b[k],k,0);//去送人咯
	}
	if(m==0&&f==0) t=c[num];//电梯不需要工作，偷懒至有人呼叫（）
} 
int main()
{
	scanf("%d",&lo);
	while(1)
	{
		++n;
		scanf("%d",&a[n]);
		if(a[n]==-1) {a[n]=0;--n;break;}
		scanf("%d%d",&b[n],&c[n]);
		flag[n]=1;
	}
	path[1]=lo;
	qsort(1,n);
	if(lo==10) direct=0;
	while(sum2<n) LOOKSCAN();
	for(int i=1;i<=step;++i)
	{
		while(path[i]==path[i+1]) ++i;//由于每次有人上或下电梯都会记录楼层，所以需要将一些同时进行的上下消除为一个
		printf("%d %d %d\n",path[i],time[i],number[i]);
	}
}