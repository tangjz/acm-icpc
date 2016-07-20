#include <cmath>
#include <cstdio>
const int maxd = 100;
const double pi = acos(-1.0), adj = 0.5 - 1e-3;
double t, T, Tmax, alpha, phi, lambda, delta;
double cos_alpha, sin_alpha, cos_phi, sin_phi, cos_delta;
double Tx, tau, vx, vy, vz, px, py, pz;
inline void locateVolcano(double tim)
{
	double cur_lambda = lambda + tim / T * pi * 2;
	vx = cos(cur_lambda) * cos_phi;
	vy = sin(cur_lambda) * cos_phi;
	vz = sin_phi;
}
inline void locateProbe(double tim)
{
	double cur_tau = tau + tim / t * pi * 2;
	px = cos(cur_tau);
	pz = sin(cur_tau);
	py = pz * cos_alpha;
	pz = pz * sin_alpha;
}
inline double calcDiff(double tim)
{
	locateVolcano(tim);
	locateProbe(tim);
	return cos_delta - (vx * px + vy * py + vz * pz);
}
int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%lf%lf%lf%lf%lf%lf%lf", &t, &T, &Tmax, &alpha, &phi, &lambda, &delta);
	if(Tmax < 2 * t)
	{
		puts("-1");
		return 0;
	}
	alpha *= pi / 180.0;
	phi *= pi / 180.0;
	lambda *= pi / 180.0;
	delta *= pi / 180.0;
	cos_alpha = cos(alpha);
	sin_alpha = sin(alpha);
	cos_phi = cos(phi);
	sin_phi = sin(phi);
	cos_delta = cos(delta);
	Tx = (T * t) / (T - t);
	locateVolcano(0);
	tau = acos(vx);
	if(phi < 0)
		tau = -tau;
	for(int idx = 1; ; ++idx)
	{
		double L = Tx * (idx - adj), R = Tx * (idx + adj);
		if(R < 2 * t)
			continue;
		else if(R > Tmax)
			R = Tmax;
		if(L < 2 * t)
			L = 2 * t;
		else if(L > Tmax)
		{
			puts("-1");
			break;
		}
		double pL = L;
		for(int i = 0; i < maxd; ++i)
		{
			double ML = L + (R - L) / 3;
			double MR = R - (R - L) / 3;
			if(calcDiff(ML) > calcDiff(MR))
				L = ML;
			else
				R = MR;
		}
		if(calcDiff(L) > 0)
			continue;
		double pR = L;
		for(int i = 0; i < maxd; ++i)
		{
			double pM = pL + (pR - pL) / 2;
			if(calcDiff(pM) > 0)
				pL = pM;
			else
				pR = pM;
		}
		printf("%.15f\n", pR);
		break;
	}
	return 0;
}
