#include<iostream>
#include<conio.h>
#include<cmath>

using namespace std;

//J(q0,q1) = (1/2m) [(sig i=0,m) (h(x[i]) - y[i])^2]			
//h(x) = q0 + q1x

//m and alpha as observed
//	
//	m		alpha
//	10		 0.06
//	9		 0.07	
//	8		 0.1
//	7		 0.1
//	6		 0.1
//	5		 0.2
//	4		 0.4
//	2		 0.6


double hfunc(double x, double q1, double q0 = 0)													//hypothesis function
{
	return q0 + q1*x ;
}

//double Jfunc(int m, double x[m], double y[m], double q1, double q0 = 0)							//Cost function : not required presently
//{
//	double J;
//	for(int i = 0; i<m; i++)
//		J+= pow(hfunc(x[i],q1,q0) - y[i], 2);
//	J/= (2*m);
//	return J;
//}

double dTerm(int m, double x[], double y[], double j, double q1, double q0 = 0)						//Differencial term for gradient descent
{
	double J = 0;											//J for returning differetial term
	
	if(j == 1)												//for theta 1
	{
		for(int i = 0; i<m; i++)
			J+= (hfunc(x[i],q1,q0) - y[i]) * x[i];
		J/= m;		
	}
	
	else													//for theta 0
	{
		for(int i = 0; i<m; i++)
			J+= (hfunc(x[i],q1,q0) - y[i]);
		J/= m;	
	}
	
//	cout<<"\nJ: "<<J;										//cout for debuging
	return J;
}

double * gradDescent(int m, double alpha, double x[], double y[], double q1, double q0 = 0)
{
	double temp0,temp1,q[2];
	
	while(((dTerm(m,x,y,0,q1,q0)) && (dTerm(m,x,y,1,q1,q0))) != 0)		//Repeat till slope is zero (minima) for theta 'j'
	{	
		temp0 = q0 - (alpha * dTerm(m,x,y,0,q1,q0));
		temp1 = q1 - (alpha * dTerm(m,x,y,1,q1,q0));
		q0 = temp0;
		q1 = temp1;
		
//		cout<<"\nq0: "<<q0<<"\nq1: "<<q1;					//cout for debuging
	}
		
	q[0] = q0;			
	q[1] = q1;
	
	return q;												//returning array having updated theta0 & theta1
}

int main()
{
	int m = 5;												//size of training data set
	double x[20],y[20];										//training data set arrays
	int q0,q1;												//the weights
	double alpha = 0.2;									 	//alpha - learning rate
	
//	random traning data set for testing
//	x[0] = 0;	y[0] = 78750;
//	x[1] = 1;	y[1] = 79500;
//	x[2] = 2;	y[2] = 80000;
//	x[3] = 3;	y[3] = 80250;
//	x[4] = 4;	y[4] = 81200;
//	x[5] = 5;	y[5] = 81500;
//	x[6] = 6;	y[6] = 81750;
	
	
	for(int i = 0;i < m;i++)								//assigning training data set values to function f(x) = x	
		x[i] = y[i] = i;	
	q0 = q1 = 0;											//initializing weights
	
	
	//predicting output starts here
	
	double a,b,*q,c1,c0;
	q = gradDescent(m,alpha,x,y,q1,q0);						//storing updated theta values in pointer
	c0 = *q;												//transfering theta0 to c0
	c1 = *(q+1);											//transfering theta1 to c1
	
	cout<<"\nEnter x: ";									// input x for predicting y
	cin>>a;
	b = hfunc(a,c1,c0);										//predicted y
	cout<<"y: "<<b;
	
	cout<<"\n\nq0: "<<(int)c0<<"\t\tq1: "<<c1;				//typecasting c0 to approximate
	
	return 0;
}

