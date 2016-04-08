import java.math.BigInteger;
import java.util.Scanner;
public class Main {
	public static void main(String[] args) {
		Scanner fin = new Scanner(System.in);
		BigInteger A = fin.nextBigInteger(), B = fin.nextBigInteger();
		fin.close();
		BigInteger[] ans = A.divideAndRemainder(B);
		System.out.println(ans[0]);
		System.out.println(ans[1]);
	}
}
