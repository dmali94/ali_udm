// project_Ali_udm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;
queue<double> modeList;
queue<double> outlier;
class ql
{
public:
	double q1,q2,q3;
}q;
double mean(double *a,int s,int n)
{
	double sum=0;
	for(int i=s;i<n;i++)
	{
		sum+=a[i];
	}

	return sum*(1.0)/n;
}
void print(queue<double> &s,int num)
{
      
	while (s.size()!=0)
	{
		 double x= s.front();
    s.pop();
    cout << x << " ";
	}
	//return;
}
void mode(double *a,int n)
{
   int m1=0,mcount=0,c=1;  /////mcount for count number of mode
  
   for(int i=0;i<n;i++)
   {
        if(a[i]==a[i+1])
			c++;
		else
		{
			
			if(c==m1)
			{
				modeList.push(a[i]);
					c=1;
			}
			else if(c>m1)
			{
				
				while (modeList.size()!=0)
				{
					modeList.pop();
				}
				modeList.push(a[i]);
				m1=c;
				
				
				c=1;
			}
			else
				c=1;

		}
   }
   
}
double medain(double *a,int n)
{
	double m=0;
	if(n%2!=0)
		return a[n/2]*(1.0);
	
		m=a[n/2]+a[(n/2)-1];
	return m/2.0;
	
}
double max(double *a,int n)
{
	return a[n-1];
}
double min(double *a,int n)
{
	return a[0];
}
double range(double *a,int n)
{
	return max(a,n)-min(a,n);
}
double midrange(double*a,int n)
{
	return (max(a,n)+min(a,n))/2.0;
}
ql quantile(double *a,int n)
{
	double * b=new double[n/2];
	int j=0;
	q.q2=medain(a,n);
	if(n%2==0)
	{
		q.q1=medain(a,n/2);
		for(int i=n/2;i<n;i++,j++)
			b[j]=a[i];
		q.q3=medain(b,n-n/2);
	}
	else
	{
		q.q1=medain(a,n/2);
		for(int i=n/2+1;i<n;i++,j++)
			b[j]=a[i];
		q.q3=medain(b,n-n/2-1);
	}
	return q;
}

double iqr(double*a,int n)
{
	ql as;
	as=quantile(a,n);
	return as.q3-as.q1;
 
}
void outliers(double*a,int n)
{
	ql as;
	double *b=a;
	double t=1.5*iqr(a,n);
	
	as=quantile(a,n);
	for(int i=0;i<n;i++)
	{
		if(b[i]>as.q3+t || b[i]<as.q1-t)
			outlier.push(b[i]);
	}

}
double sd (double*a,int n)     ///////    standard deviation 
{
	double mead=mean(a,0,n);
	double sum=0,t;
	
	for(int i=0;i<n;i++)
	{
		t=mead-a[i];
		sum+=pow(t,2.);
	}
	sum/=n;
	return sqrt(sum);
}

int _tmain(int argc, _TCHAR* argv[])
{
	ql a2;
    double *a;
	int n;
	
	     cout<<"Ex: enter size data:5\n    enter data: 5 52 2 2 1 \n\n";
		cout<<"enter your data size : ";
		cin>>n;
		cout<<"enter your data : \n";
		a=new double[n+1] ;
	
		
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	sort(a,a+n);
	double t=sd(a,n);
	cout<<t<<endl;
	cout<<"mean = "<<mean(a,0,n)<<"\n";
	cout<<"median = "<<medain(a,n)<<"\n";
    mode(a, n);
	cout<<"mode = ";print(modeList,n); cout<<endl;
	cout<<"max = "<<max(a,n)<<"   "<<"min = "<<min(a,n)<<endl;
	cout<<"midrange = "<<midrange(a,n)<<"\n";
	cout<<"rang = "<<range(a,n)<<endl;
	a2=quantile(a,n);
	cout<<"Q1 = "<<a2.q1<<"  "<<"Q2= "<<a2.q2<<"   "<<"Q3 = "<<a2.q3<<"  \n";
	cout<<"IQR="<<iqr(a,n)<<"  \n";
	cout<<"outliers = ";
	outliers(a,n);
	print(outlier,n);
	 cout<<endl;





	return 0;
}

