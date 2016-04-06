#include <cstdio>
#include <algorithm>

using namespace std;

const double pi=acos(-1.0);
const double eps=1e-7;

int dcmp(double x)
{
	return (x>eps)-(x<-eps);
}
double add(double a,double b)
{
	if (abs(a+b)<eps*(abs(a)+abs(b))) return 0.0;
	else return a+b;
}

struct Point
{
	double x,y;
	Point() {}
	Point(double x,double y): x(x),y(y) {}
	Point operator +(Point p) {
		return Point(add(x,p.x),add(y,p.y));
	}
	Point operator -(Point p) {
		return Point(add(x,-p.x),add(y,-p.y));
	}
	Point operator *(double d) {
		return Point(x*d,y*d);
	}
	double dot(Point p) {
		return add(x*p.x,y*p.y);
	}
	double det(Point p) {
		return add(x*p.y,-y*p.x);
	}
	double mod()
	{
		return sqrt(dot(*this));
	}
	Point rot(double a)
	{
		return Point(add(x*cos(a),-y*sin(a)),add(x*sin(a),+y*cos(a)));
	}
};

int TT,n;
double k,R,S,T;
Point p[509],P,Q,A,B,M,O1,O2,O;

double dist(Point A,Point B)
{
	Point U=B-A,V=O-A;
	return abs(U.det(V))/U.mod();
}
Point proj(Point A,Point B)
{
	Point V=B-A;
	return A+V*(V.dot(O-A)/V.dot(V));
}
double sqr(double x)
{
	return x*x;
}

int main()
{
	while (scanf("%d%lf",&n,&k)==2)
	{
		for (int i=0;i<n;++i) scanf("%lf%lf",&p[i].x,&p[i].y);
		scanf("%lf%lf",&A.x,&A.y);
		scanf("%lf%lf",&B.x,&B.y);
		O1=(B-A*k)*(1/(1-k));
		O2=(B+A*k)*(1/(1+k));
		O=(O1+O2)*.5;
		R=(O1-O2).mod()*.5;
		for (int i=0;i<n;++i) p[i]=p[i]-O;
		p[n]=p[0];
		O=Point(0,0);
		S=.0;
		for (int i=0;i<n;++i)
		{
			P=p[i],Q=p[i+1];
			if (dcmp(P.mod()-R)<0)
			{
				if (dcmp(Q.mod()-R)<0)
				{
					T=abs(P.det(Q));
				}
				else
				{
					A=P,B=Q;
					for (int _=0;_<200;++_)
					{
						M=(A+B)*.5;
						if (dcmp(M.mod()-R)<0) A=M;
						else B=M;
					}
					T=abs(M.det(P));
					T+=sqr(R)*abs(acos(M.dot(Q)/M.mod()/Q.mod()));
				}
			}
			else
			{
				if (dcmp(Q.mod()-R)<0)
				{
					A=Q,B=P;
					for (int _=0;_<200;++_)
					{
						M=(A+B)*.5;
						if (dcmp(M.mod()-R)<0) A=M;
						else B=M;
					}
					T=abs(M.det(Q));
					T+=sqr(R)*abs(acos(M.dot(P)/M.mod()/P.mod()));
				}
				else
				{
					M=proj(P,Q);
					double d=dist(P,Q),l;
					if (dcmp(d-R)<0 && (P-M).dot(Q-M)<0)
					{
						l=sqrt(sqr(R)-sqr(d));
						Point E=(Q-P)*(l/(Q-P).mod());
						A=M-E;
						B=M+E;
						T=abs(A.det(B));
						T+=sqr(R)*abs(acos(A.dot(P)/A.mod()/P.mod()));
						T+=sqr(R)*abs(acos(B.dot(Q)/B.mod()/Q.mod()));
					}
					else
					{
						T=sqr(R)*abs(acos(P.dot(Q)/P.mod()/Q.mod()));
					}
				}
			}
			if (dcmp(P.det(Q))<0) S+=T;
			else S-=T;
		}
		printf("Case %d: %.7f\n",++TT,abs(S)*.5);
	}
	return 0;
}
