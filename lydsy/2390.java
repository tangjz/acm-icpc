import java.math.*;
import java.util.*;

public class Main {
	static BigInteger getLargest(int n, BigInteger upp) {
		BigInteger ret = BigInteger.ZERO;
		for(int i = n - 1, c = 0; i >= 0; --i) {
			BigInteger nxt = ret;
			if(c > 0)
				nxt = nxt.add(BigInteger.valueOf(c).shiftLeft(i));
			if(i > 0)
				nxt = nxt.add(BigInteger.valueOf(i).shiftLeft(i - 1));
			if(nxt.compareTo(upp) <= 0) {
				ret = nxt;
				++c;
			}
		}
		BigInteger nxt = ret.add(BigInteger.valueOf(n));
		if(nxt.compareTo(upp) <= 0)
			ret = nxt;
		return ret;
	}
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		int n = cin.nextInt(), m = cin.nextInt();
		cin.close();
		BigInteger all = BigInteger.valueOf(n).shiftLeft(n - 1);
		BigInteger low = all.divide(BigInteger.valueOf(m));
		int L = 0, R = n - 1;
		while(L < R) {
			int M = (L + R) >> 1;
			BigInteger sum = BigInteger.ZERO, adt = low.add(BigInteger.valueOf(M));
			for(int i = 1; i < m; ++i)
				sum = getLargest(n, sum.add(adt));
			if(all.compareTo(sum.add(adt)) <= 0) {
				R = M;
			} else {
				L = M + 1;
			}
		}
		System.out.println(low.add(BigInteger.valueOf(L)));
	}
}