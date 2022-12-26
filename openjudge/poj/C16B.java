import java.io.BufferedInputStream;
import java.math.BigInteger;
import java.util.Scanner;

public class Main
{
	static final int maxn = 101;
	public static void main(String[] args) {
		// Scanner cin = new Scanner(System.in);
		Scanner cin = new Scanner(new BufferedInputStream(System.in));
		int t = cin.nextInt();
		while(t-- > 0) {
			BigInteger n = cin.nextBigInteger();
			System.out.println(3);
			System.out.println(n);
			System.out.println(n.multiply(BigInteger.valueOf(5)).add(BigInteger.valueOf(2)));
			System.out.println(n.multiply(BigInteger.valueOf(7)).add(BigInteger.valueOf(3)));
		}
		cin.close();
	}
}
