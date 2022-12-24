import java.math.*;
import java.util.*;

public class Main {
	public static void main(String[] args) {
		int maxn = 0, maxm = 0;
		ArrayList<Integer> data = new ArrayList<Integer>();
		Scanner cin = new Scanner(System.in);
		while(cin.hasNextInt()) {
			int n = cin.nextInt(), d = cin.nextInt();
			if(d < n) {
				maxn = Math.max(maxn, n);
				maxm = Math.max(maxm, d >> 1);
			}
			data.add(n);
			data.add(d);
		}
		cin.close();
		BigInteger[][] c = new BigInteger[maxn + 1][maxn + 1];
		BigInteger[][] f = new BigInteger[maxm + 1][maxn + 1];
		BigInteger[][] g = new BigInteger[maxm + 1][maxn + 1];
		for(int i = 0; i <= maxn; ++i) {
			c[i][0] = c[i][i] = BigInteger.ONE;
			for(int j = 1; j < i; ++j)
				c[i][j] = c[i - 1][j - 1].add(c[i - 1][j]);
		}
		f[0][1] = g[0][1] = BigInteger.ONE;
		for(int i = 2; i <= maxn; ++i)
			f[0][i] = g[0][i] = BigInteger.ZERO;
		for(int i = 1; i <= maxm; ++i) {
			f[i][1] = g[i][1] = BigInteger.ONE;
			for(int j = 2; j <= maxn; ++j) {
				f[i][j] = BigInteger.ZERO;
				for(int k = 1; k < j; ++k)
					f[i][j] = f[i][j].add(c[j][k].multiply(f[i - 1][k]).multiply(g[i][j - k]));
				g[i][j] = f[i][j].divide(BigInteger.valueOf(j - 1));
				f[i][j] = f[i][j].add(g[i][j]);
			}
		}
		for(int i = 1; i <= maxm; ++i) {
			for(int j = 1; j <= i; ++j)
				f[i][j] = BigInteger.ZERO;
			for(int j = i + 1; j <= maxn; ++j)
				f[i][j] = g[i][j].subtract(g[i - 1][j]);
		}
		for(int i = 0; i < data.size(); i += 2) {
			int n = data.get(i), d = data.get(i + 1), m = d >> 1;
			BigInteger ans;
			if(m + m == d) {
				ans = f[m][n];
				if(m > 0)
					for(int j = m; j < n; ++j)
						ans = ans.subtract(c[n][j].multiply(f[m - 1][j]).multiply(g[m - 1][n - j]));
			} else {
				ans = BigInteger.ZERO;
				for(int j = m + 1, k = n - j; j <= k; ++j, --k)
					ans = ans.add(c[j < k ? n : n - 1][j].multiply(f[m][j]).multiply(f[m][k]));
			}
			System.out.println(ans);
		}
	}
}