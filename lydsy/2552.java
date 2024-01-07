import java.math.*;
import java.util.*;

public class Main {
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		while(true) {
			int n = cin.nextInt(), m = cin.nextInt();
			if(n == 0 && m == 0)
				break;
			BigInteger ans = BigInteger.ONE, prd = ans;
			for(int i = 1; i <= n * m; ++i)
				ans = ans.multiply(BigInteger.valueOf(i));
			for(int i = 1; i <= n; ++i)
				prd = prd.multiply(BigInteger.valueOf(i));
			for(int i = 1; i <= m; ++i) {
				ans = ans.divide(prd);
				prd = prd.multiply(BigInteger.valueOf(n + i)).divide(BigInteger.valueOf(i));
			}
			System.out.println(ans);
		}
		cin.close();
	}
}