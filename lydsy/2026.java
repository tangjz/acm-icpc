import java.math.*;
import java.util.*;

public class Main {
	static final int BLEN = 120, maxm = 18, maxd = 480;
	static int[] getPrimes(int n) {
		ArrayList<Integer> res = new ArrayList<Integer>();
		for(int i = 2; i * i <= n; ++i)
			if(n % i == 0) {
				res.add(i);
				while(n % i == 0)
					n /= i;
			}
		if(n > 1)
			res.add(n);
		int[] ret = new int[res.size()];
		for(int i = 0; i < res.size(); ++i)
			ret[i] = res.get(i);
		return ret;
	}
	static int[] getFactors(int n) {
		ArrayList<Integer> res = new ArrayList<Integer>();
		for(int i = 1; i * i <= n; ++i)
			if(n % i == 0) {
				res.add(i);
				if(i * i < n)
					res.add(n / i);
			}
		int[] ret = new int[res.size()];
		for(int i = 0; i < res.size(); ++i)
			ret[i] = res.get(i);
		Arrays.sort(ret);
		return ret;
	}
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		int n = cin.nextInt();
		cin.close();
		BigInteger MOD = BigInteger.valueOf(n);
		for(int i = 0; i < BLEN; ++i)
			MOD = MOD.multiply(BigInteger.TEN);
		int[] pr = getPrimes(n), fct = getFactors(n);
		int plen = pr.length, slen = fct.length;
		int[] coeff = new int[maxm], phi = new int[slen];
		BigInteger[][] f = new BigInteger[slen][maxm];
		coeff[0] = -1;
		for(int i = 1; i < maxm; ++i)
			for(int j = i; j > 0; --j)
				coeff[j] -= coeff[j - 1];
		phi[0] = 1;
		for(int i = 0; i < maxm; ++i)
			f[0][i] = BigInteger.valueOf(i);
		for(int i = 1; i < slen; ++i) {
			int las = -1, pp = -1;
			for(int j = 0; j < plen; ++j)
				if(fct[i] % pr[j] == 0) {
					pp = pr[j];
					break;
				}
			for(int j = 0; j < slen; ++j)
				if(fct[j] * pp == fct[i]) {
					las = j;
					break;
				}
			if(fct[las] % pp == 0) {
				phi[i] = phi[las] * pp;
			} else {
				phi[i] = phi[las] * (pp - 1);
			}
			for(int j = 1; j < maxm; ++j) {
				f[i][j] = BigInteger.ONE;
				BigInteger tmp = f[las][j];
				for(int k = pp; k > 0; k >>= 1, tmp = tmp.multiply(tmp).mod(MOD))
					if((k & 1) == 1)
						f[i][j] = f[i][j].multiply(tmp).mod(MOD);
			}
		}
		BigInteger ans = BigInteger.ZERO;
		for(int i = 0; i < slen; ++i) {
			BigInteger tmp = BigInteger.ZERO;
			for(int j = 1; j < maxm; ++j)
				tmp = tmp.add(f[i][j].multiply(BigInteger.valueOf(coeff[j])));
			ans = ans.add(tmp.multiply(BigInteger.valueOf(phi[slen - 1 - i]))).mod(MOD);
		}
		String out = ans.divide(BigInteger.valueOf(n)).toString();
		while(out.length() < BLEN)
			out = "0" + out;
		System.out.println(out);
	}
}
