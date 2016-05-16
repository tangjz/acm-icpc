import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	private static final int maxn = 51;
	private static int deg, cur, nxt;
	private static BigInteger[] fact = new BigInteger[maxn], f[] = new BigInteger[2][maxn], pre = new BigInteger[maxn], suf = new BigInteger[maxn];
	private static BigInteger value(int x) {
		if(x < deg)
			return f[cur][x];
		pre[0] = BigInteger.valueOf(x);
		for(int i = 1; i < deg; ++i)
			pre[i] = pre[i - 1].multiply(BigInteger.valueOf(x - i));
		suf[deg - 1] = BigInteger.valueOf(x - deg + 1);
		for(int i = deg - 2; i >= 0; --i)
			suf[i] = suf[i + 1].multiply(BigInteger.valueOf(x - i));
		BigInteger ret = BigInteger.ZERO;
		for(int i = 0; i < deg; ++i) {
			BigInteger tmp = f[cur][i];
			if(i > 0)
				tmp = tmp.multiply(pre[i - 1]);
			if(i < deg - 1)
				tmp = tmp.multiply(suf[i + 1]);
			tmp = tmp.divide(fact[i]).divide(fact[deg - 1 - i]);
			if(((deg - 1 - i) & 1) == 1)
				ret = ret.subtract(tmp);
			else
				ret = ret.add(tmp);
		}
		return ret;
	}
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		int delta = cin.nextInt();
		BigInteger val = cin.nextBigInteger();
		cin.close();
		cur = 0;
		nxt = 1;
		deg = 1;
		f[cur][0] = BigInteger.ONE;
		fact[0] = BigInteger.ONE;
		while(val.compareTo(BigInteger.valueOf(delta)) >= 0) {
			BigInteger[] tmp = val.divideAndRemainder(BigInteger.valueOf(delta));
			for(int i = 0, pos = tmp[1].intValue(); i <= deg; ++i, pos += delta)
				f[nxt][i] = (i > 0 ? f[nxt][i - 1] : BigInteger.ZERO).add(value(pos));
			fact[deg] = fact[deg - 1].multiply(BigInteger.valueOf(deg));
			++deg;
			cur ^= 1;
			nxt ^= 1;
			val = tmp[0];
		}
		System.out.println(value(val.intValue()));
	}
}
