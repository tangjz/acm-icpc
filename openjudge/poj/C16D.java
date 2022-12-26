// import java.io.BufferedInputStream;
import java.math.BigInteger;
import java.util.Scanner;

public class Main
{
	static final int maxn = 201;
	static BigInteger[][] ans = new BigInteger[maxn][maxn];
	public static void main(String[] args) {
		ans[3][1] = BigInteger.valueOf(1);
		ans[3][2] = BigInteger.valueOf(2);
		ans[3][3] = BigInteger.valueOf(3);
		ans[4][1] = BigInteger.valueOf(1);
		ans[4][2] = BigInteger.valueOf(2);
		ans[4][3] = BigInteger.valueOf(6);
		ans[4][4] = BigInteger.valueOf(9);
		for(int i = 5; i < maxn; ++i) {
			for(int j = 1; j <= i - 2; ++j)
				ans[i][j] = ans[i - 2][j];
			ans[i][i - 1] = ans[i][i - 2].multiply(BigInteger.valueOf(4));
			ans[i][i] = ans[i][i - 2].multiply(BigInteger.valueOf(6));
		}
		Scanner cin = new Scanner(System.in);
		// Scanner cin = new Scanner(new BufferedInputStream(System.in));
		int t = cin.nextInt();
		while(t-- > 0) {
			int n = cin.nextInt();
			if(n == 2) {
				System.out.println("-1");
			} else {
				for(int i = 1; i <= n; ++i)
					System.out.println(ans[n][i]);
			}
		}
		cin.close();
	}
}
