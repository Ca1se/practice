#include <bits/stdc++.h>
using namespace std;
int a, b, c;

inline double getfuncy(double x, double qa = a, double qb = b, double qc = c) {
	return x * x * qa + qb * x + qc;
}

inline double getfuncx(double qa = a, double qb = b, double qc = c, bool f = true) {
	if(f) return (double(-qb) - sqrt(qb * qb - 4 * qa * qc)) / (2 * qa);
	else return (double(-qb) + sqrt(qb * qb - 4 * qa * qc)) / (2 * qa);
}

int main() {
	int t, x0, x1, y0, y1, y2;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d%d%d%d%d%d", &a, &b, &c, &x0, &x1, &y0, &y1, &y2);
		double mid = ((double) (-b)) / (2 * a);
		double midv = getfuncy(mid);
		if(mid >= x1 || midv <= y0)  {
			printf("No\n");
			continue;
		}
		double xf = getfuncx(a, b, c - y0, false);
		if(xf >= x0 && xf <= x1) {
			printf("No\n");
			continue;
		}
		double xb = getfuncx(a, b, c - y0);
		if(xb > x0 && xb < x1) {
			printf("Yes\n");
			continue;
		}
		double py = getfuncy(x1);
		if(py <= y2 && py >= y1) {
			double r = 2 * x1 - mid;
			double ax = getfuncx(a, -2 * a * r, a * r * r + midv - y0, false);
			if(ax > x0 && ax < x1) {
				printf("Yes\n");
			}else {
				printf("No\n");
			}
		}else {
			printf("No\n");
		}
	}
	return 0;
}
