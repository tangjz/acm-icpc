import java.math.*;
import java.util.*;

public class Main {
	
	static final int maxd = 33;
	static BigInteger[] fct;
	static BigInteger[][] bin;
	
	static class Poly {
		int sta, deg;
		BigInteger[] val;
		Poly(int sta, int deg) {
			this.sta = sta;
			this.deg = deg;
			val = new BigInteger[deg + 1];
		}
		BigInteger value(BigInteger pos) {
			pos = pos.subtract(BigInteger.valueOf(sta));
			if(pos.compareTo(BigInteger.ZERO) < 0)
				return BigInteger.ZERO;
			if(pos.compareTo(BigInteger.valueOf(deg)) <= 0)
				return val[pos.intValue()];
			BigInteger[] seq = new BigInteger[deg + 1];
			BigInteger[] suf = new BigInteger[deg + 1];
			seq[deg] = suf[deg] = pos.subtract(BigInteger.valueOf(deg));
			for(int i = deg - 1; i >= 0; --i) {
				seq[i] = seq[i + 1].add(BigInteger.ONE);
				suf[i] = suf[i + 1].multiply(seq[i]);
			}
			BigInteger pre = BigInteger.ONE, ret = BigInteger.ZERO;
			for(int i = 0; i <= deg; ++i) {
				BigInteger tmp = val[i].multiply(bin[deg][i]);
				if(i > 0)
					tmp = tmp.multiply(pre);
				if(i < deg)
					tmp = tmp.multiply(suf[i + 1]);
				pre = pre.multiply(seq[i]);
				if(((deg - i) & 1) == 0)
					ret = ret.add(tmp);
				else
					ret = ret.subtract(tmp);
			}
			return ret.divide(fct[deg]);
		}
	}
	
	static BigInteger getP(BigInteger n) {
		BigInteger m = n.add(BigInteger.ONE).shiftLeft(1);
		BigInteger x = BigInteger.ONE, x1 = x.add(BigInteger.ONE);
		while(x.multiply(x).compareTo(m) > 0 || x1.multiply(x1).compareTo(m) <= 0) {
			x = x.add(m.divide(x)).shiftRight(1);
			x1 = x.add(BigInteger.ONE);
		}
		x1 = x.subtract(BigInteger.ONE);
		while(x.multiply(x1).compareTo(m) >= 0) {
			x = x.subtract(BigInteger.ONE);
			x1 = x1.subtract(BigInteger.ONE);
		}
		while(x.multiply(x1).compareTo(m) < 0) {
			x = x.add(BigInteger.ONE);
			x1 = x1.add(BigInteger.ONE);
		}
		return x1.subtract(BigInteger.ONE);
	}
	static int getF(int n) {
		return n * (n + 1) / 2;
	}
	static Poly getSum1(Poly f) {
		Poly g = new Poly(f.sta + 1, f.deg + 1);
		while(true) {
			g.val[0] = f.value(BigInteger.valueOf(g.sta - 1));
			if(g.val[0].compareTo(BigInteger.ZERO) > 0)
				break;
			++g.sta;
		}
		for(int i = 1; i <= g.deg; ++i)
			g.val[i] = g.val[i - 1].add(f.value(BigInteger.valueOf(g.sta + i - 1)));
		return g;
	}
	static Poly getSum2(Poly g) {
		Poly h = new Poly(1, g.deg * 2);
		while(true) {
			h.val[0] = g.value(BigInteger.valueOf(getF(h.sta)));
			if(h.val[0].compareTo(BigInteger.ZERO) > 0)
				break;
			++h.sta;
		}
		for(int i = 1; i <= h.deg; ++i)
			h.val[i] = g.value(BigInteger.valueOf(getF(h.sta + i)));
		return h;
	}
	
	static final int maxc = 5, lown = 607;
	static int cnt;
	static int[] P, Q;
	static BigInteger[] que, ans;
	static Poly[] f, g;
	static BigInteger[][] h;
	
	public static void main(String[] args) {
		fct = new BigInteger[maxd];
		bin = new BigInteger[maxd][maxd];
		fct[0] = bin[0][0] = BigInteger.ONE;
		for(int i = 1; i < maxd; ++i) {
			fct[i] = fct[i - 1].multiply(BigInteger.valueOf(i));
			bin[i][0] = bin[i][i] = BigInteger.ONE;
			for(int j = 1; j < i; ++j)
				bin[i][j] = bin[i - 1][j - 1].add(bin[i - 1][j]);
		}
		P = new int[lown];
		for(int i = 1, j = 1; j < lown; ++i)
			for(int k = 0; j < lown && k <= i; ++j, ++k)
				P[j] = i;
		Q = new int[lown];
		Q[1] = 1;
		for(int i = 2; i < lown; ++i)
			Q[i] = Q[i - 1] + Q[P[i]];
		f = new Poly[maxc];
		g = new Poly[maxc];
		f[0] = new Poly(1, 0);
		f[0].val[0] = BigInteger.ONE;
		g[0] = getSum1(f[0]);
		for(int i = 1; i < maxc; ++i) {
			f[i] = getSum2(g[i - 1]);
			if(f[i].deg * 2 >= maxd)
				break;
			g[i] = getSum1(f[i]);
		}
		h = new BigInteger[maxc][lown];
		for(int i = 0; i < maxc; ++i) {
			h[i][0] = BigInteger.ZERO;
			for(int j = 1; j < lown; ++j)
				h[i][j] = h[i][j - 1].add(f[i].value(BigInteger.valueOf(j)).multiply(BigInteger.valueOf(Q[P[j]])));
		}
		que = new BigInteger[maxc];
		ans = new BigInteger[maxc];
		Scanner cin = new Scanner(System.in);
		int T = cin.nextInt();
		for(int Case = 1; Case <= T; ++Case) {
			BigInteger n = cin.nextBigInteger();
			if(n.compareTo(BigInteger.valueOf(lown)) < 0) {
				System.out.println(Q[n.intValue()]);
				continue;
			}
			cnt = 1;
			que[0] = n;
			while(cnt < maxc) {
				que[cnt] = getP(que[cnt - 1]);
				if(que[cnt].compareTo(BigInteger.valueOf(lown)) < 0)
					break;
				++cnt;
			}
			for(int i = 0; i <= cnt; ++i)
				ans[i] = h[i][que[cnt].intValue()];
			for(int i = cnt - 1; i >= 0; --i) {
				for(int j = 0; j <= i; ++j)
					ans[j + 1] = g[j].value(que[i].add(BigInteger.ONE)).multiply(ans[0]).subtract(ans[j + 1]);
				for(int j = 0; j <= i; ++j)
					ans[j] = ans[j + 1];
			}
			System.out.println(ans[0]);
		}
		cin.close();
	}
}