import java.io.BufferedInputStream;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
	static final int delta = 80;
	public static void main(String[] args) {
		// Scanner cin = new Scanner(System.in);
		Scanner cin = new Scanner(new BufferedInputStream(System.in));
		int n = cin.nextInt();
		int[] x = new int[n], y = new int[n];
		for(int i = 0; i < n; ++i) {
			x[i] = cin.nextInt();
			y[i] = cin.nextInt();
		}
		cin.close();
		int low = x[0], high = x[0];
		for(int i = 1; i < n; ++i)
			if(x[i] < low)
				low = x[i];
			else if(high < x[i])
				high = x[i];
		low -= delta;
		ArrayList<BigInteger> fib = new ArrayList<BigInteger>(high - low + 1);
		fib.add(BigInteger.ZERO);
		fib.add(BigInteger.ONE);
		for(int i = 2; i <= high - low; ++i)
			fib.add(fib.get(i - 2).add(fib.get(i - 1)));
		BigInteger val = BigInteger.ZERO;
		for(int i = 0; i < n; ++i)
			val = val.add(fib.get(x[i] - low).multiply(BigInteger.valueOf(y[i])));
		for( ; fib.get(high - low).compareTo(val) < 0; ++high)
			fib.add(fib.get(high - low - 1).add(fib.get(high - low)));
		ArrayList<Integer> out = new ArrayList<Integer>(high - low + 1);
		for(int i = high - low; i > 0; --i) {
			BigInteger tmp = fib.get(i);
			if(tmp.compareTo(val) <= 0) {
				val = val.subtract(tmp);
				out.add(i + low);
			}
		}
		for(int i = out.size() - 1; i >= 0; --i)
			System.out.printf("%d ", out.get(i));
	}
}

