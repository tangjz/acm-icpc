import java.math.*;
import java.util.*;

public class Main {
	static BigInteger choose(int n, int m) {
		assert n >= m && m >= 0;
		BigInteger fz = BigInteger.ONE, fm = BigInteger.ONE;
		m = Math.min(m, n - m);
		for(int i = 0; i < m; ++i) {
			fz = fz.multiply(BigInteger.valueOf(n - i));
			fm = fm.multiply(BigInteger.valueOf(i + 1));
		}
		return fz.divide(fm);
	}
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		while(cin.hasNext()) {
			int m = cin.nextInt(), n = cin.nextInt();
			BigInteger fz = BigInteger.ZERO, fm = choose(n - 1 + m, m);
			for(int i = 1; i <= m; ++i) {
				fz = fz.add(fm);
				for(int j = 0, k = 0; j <= n && k <= m; ++j, k += i) {
					BigInteger tp = choose(n, j).multiply(choose(n - 1 + m - k, m - k));
					if((j & 1) == 1) {
						fz = fz.add(tp);
					} else {
						fz = fz.subtract(tp);
					}
				}
			}
			String ans = "";
			BigInteger[] tmp = fz.divideAndRemainder(fm);
			ans += String.valueOf(tmp[0].intValue()) + ".";
			fz = tmp[1];
			for(int i = 0; i < 4; ++i) {
				tmp = fz.multiply(BigInteger.TEN).divideAndRemainder(fm);
				ans += String.valueOf(tmp[0].intValue());
				fz = tmp[1];
			}
			if(fz.compareTo(fm.subtract(fz)) >= 0) {
				char[] buf = ans.toCharArray();
				int len = buf.length;
				++buf[len - 1];
				for(int i = len - 1; i > 0; --i) {
					if(buf[i] == '.')
						continue;
					if(buf[i] > '9') {
						buf[i] -= 10;
						if(buf[i - 1] == '.')
							++buf[i - 2];
						else
							++buf[i - 1];
					}
				}
				if(buf[0] > '9') {
					buf[0] -= 10;
					ans = "1" + String.valueOf(buf);
				} else {
					ans = String.valueOf(buf);
				}
			}
			System.out.println(ans);
		}
		cin.close();
	}
}
