//接人优先级：方向完全一致>方向不完全一致>最短距离
//送人优先级：方向一致>最短距离
#include<stdio.h>
int n;
int t;
int a[1000],b[1000],c[1000];
int flag[1000];
int ele1[5],ele2[5];
int path1[1000],path2[1000];
int step1,step2,time1[1000],time2[1000];
int number1[1000],number2[1000];
int lo1,lo2;
int direct1=1,direct2=1;
int m1,m2;
int purpose1,purpose2;
int sum1,sum2;
int flg1=1,flg2=1;
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
void prograss()
{
	while(1)
	{
		for(int i=1;i<=4;++i)
		{
			if(b[ele1[j]]==lo1)
			{
				++sum2;++step1;--m1;
				path1[step1]=lo1;time1[step1]=t;number1[step1]=m1;
				ele1[j]=0;
			}
			if(b[ele2[j]]==lo2)
			{
				flag[ele2[j]]==0;
				++sum2;++step2;--m2;
				path1[step2]=lo2;time2[step2]=t;number2[step2]=m2;
				ele2[j]=0;
			}
		}
		for(int j=1;j<=n;++j)
		{
			if(m1==4&&m2==4) break;//满员的情况下不能接人，接人终止
			if(a[j]==lo1&&flag[j]&&t>=c[j])//接人的条件
			{
				for(int k=1;k<=4;++k)
					if(ele1[k]==0)
					{
						ele1[k]=j;
						break;
					}//填上空位
				flag[j]=0;//此人已上过电梯
				++sum1;++step1;++m1;
				path1[step1]=lo1;time1[step1]=t;number1[step1]=m1;
			}
			if(a[j]==lo2&&flag[j]&&t>=c[j])//接人的条件
			{
				for(int k=1;k<=4;++k)
					if(ele2[k]==0)
					{
						ele2[k]=j;
						break;
					}//填上空位
				flag[j]=0;//此人已上过电梯
				++sum1;++step2;++m2;
				path2[step1]=lo2;time2[step2]=t;number2[step2]=m2;
			}
		}
		if(m1==4&&flg1) purpose1=0;
		if(m2==4&&flg2) purpose2=0;
		if(purpose1==lo1) purpose1=0;
		if(purpose2==lo2) purpose2=0;
		if(purpose1==0||purpose2==0) break;
		++t;
		if(purpose1<lo1) --lo1;
		if(purpose1>lo1) ++lo1;
		if(purpose2<lo2) --lo2;
		if(purpose2>lo2) ++lo2;
	}
}
void direction()
{
	int i=1;
	while(c[i]<=t) ++i;
	--i;
	int f11=0,f12=0,k1=0,k11=0,minn1=1000;
	int f21=0,f22=0,k2=0,k22=0,minn2=1000;
	int flg1=0,flg2=0;
	if((m1<4||m2<4)&&sum1!=0&&(purpose1==0||purpose2==0))
	{
		for(int j=1;j<=i;++j)
		{
			if(flag[j])
			{
				if(m1<4&&purpose1==0)
				{
					if((a[j]-lo1)*direct1>0&&direct1==(b[j]>a[j])&&(minn1>abs(a[j]-lo1)||f11==0)) {minn1=abs(a[j]-lo1);k11=k1;k1=j;f11=1;}
					if(f11==0&&(a[j]-lo1)*(b[j]-a[j])>0&&(minn1>abs(a[j]-lo1)||f12==0)) {minn1=abs(a[j]-lo1);k11=k1;k1=j;f12=1;}
					if(f11=0&&f12==0&&minn1<abs(a[j]-lo1)) {minn1=abs(a[j]-lo1);k11=k1;k1=j;}
				}
				if(m2<4&&purpose2==0)
				{
					if((a[j]-lo2)*direct2>0&&direct2==(b[j]>a[j])&&(minn2>abs(a[j]-lo2)||f21==0)) {minn2=abs(a[j]-lo2);k22=k2;k2=j;f21=1;}
				    if(f21==0&&(a[j]-lo2)*(b[j]-a[j])>0&&(minn2>abs(a[j]-lo2)||f22==0)) {minn2=abs(a[j]-lo2);k22=k2;k2=j;f22=1;}
	                if(f21==0&&f22==0&&minn2<abs(a[j]-lo2)) {minn2=abs(a[j]-lo2);k22=k2;k2=j;}
				}
			} 
		}
		if(k1==k2&&m1<4&&m2<4&&k1!=0)
		{
			if(direct1==direct2)
		    {
			    if(minn1<=minn2) {purpose1=a[k1];flg1=1;}
			    if(minn1>minn2) {purpose2=a[k2];flg2=1;}
		    }
		    else if(f11||(!f11&&!f21&&f12)||(!f11&&!f21&&!f12&&!f22&&minn1<=minn2)) {purpose1=a[k1];flg1=1;}
			     else {purpose2=a[k2];flg2=1;}
			if(purpose1==0&&k11!=0) {purpose1=a[k11];flg1=1;}
			if(purpose2==0) {purpose2=a[k22];flg2=1;}
		}
		else
		{
			if(m1<4&&k1!=0&&purpose1==0) purpose1=a[k1];
			if(m2<4&&k2!=0&&purpose2==0) purpose2=a[k2]; 
		}

	}
	minn1=1000;minn2=1000;
	if((sum1==0||m1==4||purpose1==0)&&m1>=1)
		for(int j=1;j<=4;++j)
			if(ele1[j]!=0&&minn1>abs(lo1-b[ele1[j]])) {purpose1=b[ele1[j]];minn1=abs(lo1-b[ele1[j]]);}
	if((sum1==0||m2==4||purpose2==0)&&m2>=1)
		for(int j=1;j<=4;++j)
			if(ele2[j]!=0&&minn2>abs(lo1-b[ele2[j]])) {purpose2=b[ele2[j]];minn2=abs(lo1-b[ele2[j]]);}
	prograss();
}
int main()
{
	scanf("%d%d",&lo1,&lo2);
	while(1)
	{
		++n;
		scanf("%d",&a[n]);
		if(a[n]==-1) {a[n]=0;--n;break;}
		scanf("%d%d",&b[n],&c[n]);
		flag[n]=1;
	}
	path1[1]=lo1;
	path2[1]=lo2;
	qsort(1,n);
	if(lo1==10) direct1=-1;
	if(lo2==10) direct2=-1;
	while(sum2<n) direction();
	for(int i=1;i<=step1;++i)
	{
		while(path1[i]==path1[i+1]) ++i;//由于每次有人上或下电梯都会记录楼层，所以需要将一些同时进行的上下消除为一个
		printf("%d %d %d\n",path1[i],time1[i],number1[i]);
	}
	for(int i=1;i<=step2;++i)
	{
		while(path2[i]==path2[i+1]) ++i;//由于每次有人上或下电梯都会记录楼层，所以需要将一些同时进行的上下消除为一个
		printf("%d %d %d\n",path2[i],time2[i],number2[i]);
	}
}