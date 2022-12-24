import java.util.*;
import java.math.*;

public class Main {
	static BigInteger factorial(int L, int R) {
		if(L == R)
			return BigInteger.valueOf(L);
		int M = (L + R) >> 1;
		return factorial(L, M).multiply(factorial(M + 1, R));
	}
	static BigInteger power(int x, int k) {
		if(x == 1 || k == 0)
			return BigInteger.ONE;
		BigInteger ret = BigInteger.ONE, tmp = BigInteger.valueOf(x);
		while(k > 0) {
			if((k & 1) > 0)
				ret = ret.multiply(tmp);
			if((k >>= 1) > 0)
				tmp = tmp.multiply(tmp);
		}
		return ret;
	}
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		int n = cin.nextInt(), k = cin.nextInt();
		System.out.println(factorial(1, k).multiply(power(k + 1, n - k).subtract(power(k, n - k))));
		cin.close();
	}
}