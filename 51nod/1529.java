import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class Main {
	static int n, m, mx;
	static int[] seq, que, bit;
	static BigInteger[] fct, prd;
	static int getIdx(int x) {
		int L = 1, R = m;
		while(L < R) {
			int M = (L + R) >> 1;
			if(que[M] < x)
				L = M + 1;
			else
				R = M;
		}
		return L;
	}
	static int segIdx(int L, int R) {
		return (L + R) | (L < R ? 1 : 0);
	}
	static int fctInit(int L, int R) {
		int rt = segIdx(L, R);
		if(L < R) {
			int M = (L + R) >> 1;
			fct[rt] = fct[fctInit(L, M)].multiply(fct[fctInit(M + 1, R)]);
		} else {
			fct[rt] = BigInteger.valueOf(n - L + 1);
		}
		return rt;
	}
	static void bit_add(int x, int v) {
		for( ; x <= m; x += x & -x)
			bit[x] += v;
	}
	static int bit_sum(int x) {
		int ret = 0;
		for( ; x > 0; x -= x & -x)
			ret += bit[x];
		return ret;
	}
	static int bit_kth(int k) {
		int ret = 0;
		for(int rem = mx, tmp; rem > 0; rem >>= 1)
			if((tmp = ret | rem) < m && bit[tmp] < k) {
				ret = tmp;
				k -= bit[tmp];
			}
		return ret + 1;
	}
	static BigInteger solve1(int L, int R) {
		int rt = segIdx(L, R);
		if(L == R) {
			bit_add(seq[L], 1);
			int les = bit_sum(seq[L] - 1);
			prd[rt] = BigInteger.valueOf(bit_sum(seq[L]) - les);
			return BigInteger.valueOf(les);
		}
		int M = (L + R) >> 1, lch = segIdx(L, M), rch = segIdx(M + 1, R);
		BigInteger rval = solve1(M + 1, R);
		BigInteger lval = solve1(L, M);
		prd[rt] = prd[lch].multiply(prd[rch]);
		return lval.multiply(fct[rch]).add(prd[lch].multiply(rval));
	}
	static BigInteger calcRank(int[] array) {
		for(int i = 1; i <= m; ++i)
			bit[i] = 0;
		seq = array;
		return solve1(1, n);
	}
	static BigInteger solve2(int L, int R, BigInteger val) {
		int rt = segIdx(L, R);
		if(L == R) {
			seq[L] = bit_kth(val.intValue() + 1);
			int les = bit_sum(seq[L] - 1);
			prd[rt] = BigInteger.valueOf(bit_sum(seq[L]) - les);
			bit_add(seq[L], -1);
			return BigInteger.valueOf(les);
		}
		int M = (L + R) >> 1, lch = segIdx(L, M), rch = segIdx(M + 1, R);
		BigInteger lval = solve2(L, M, val.divide(fct[rch]));
		BigInteger rval = solve2(M + 1, R, val.subtract(lval.multiply(fct[rch])).divide(prd[lch]));
		prd[rt] = prd[lch].multiply(prd[rch]);
		return lval.multiply(fct[rch]).add(prd[lch].multiply(rval));
	}
	public static void main(String[] args) throws IOException {
		BufferedReader cin = new BufferedReader(new InputStreamReader(System.in), 1 << 16);
        BufferedWriter cout = new BufferedWriter(new OutputStreamWriter(System.out), 1 << 16);
		n = Integer.parseInt(cin.readLine());
		int[] a = new int[n + 1], b = new int[n + 1];
		seq = new int[n];
		for(int i = 1; i <= n; ++i) {
			String[] buf = cin.readLine().split(" ");
			a[i] = Integer.parseInt(buf[0]);
			b[i] = Integer.parseInt(buf[1]);
			seq[i - 1] = a[i];
		}
		cin.close();
		Arrays.sort(seq);
		m = 0;
		que = new int[n + 1];
		for(int i = 0; i < n; ++i)
			if(m == 0 || que[m] < seq[i])
				que[++m] = seq[i];
		for(int i = 1; i <= n; ++i) {
			a[i] = getIdx(a[i]);
			b[i] = getIdx(b[i]);
		}
		bit = new int[m + 1];
		for(mx = 1; mx << 1 < m; mx <<= 1);
		fct = new BigInteger[n << 1 | 1];
		prd = new BigInteger[n << 1 | 1];
		fctInit(1, n);
		solve2(1, n, calcRank(a).add(calcRank(b)).mod(fct[segIdx(1, n)]));
		for(int i = 1; i <= n; ++i) {
			cout.write(Integer.toString(que[seq[i]]));
			cout.newLine();
		}
		cout.close();
	}
}
