import java.math.*;
import java.util.*;

public class Main {
	static final int maxm = 261;
	static final int[] ans = new int[]{-1, 0, -1, -1, -1, -1, 9, 15, 22, 29};
	static final BigInteger MOD = BigInteger.valueOf((int)1e9 + 7);
	public static void main(String[] args) {
		int maxp = 2;
		BigInteger[][] f = new BigInteger[5][maxm];
		f[0][1] = f[1][1] = f[2][1] = f[3][1] = BigInteger.ONE;
		Scanner cin = new Scanner(System.in);
		int t = cin.nextInt();
		while((t--) > 0) {
			BigInteger n = cin.nextBigInteger();
			if(n.compareTo(BigInteger.TEN) < 0) {
				System.out.println(ans[n.intValue()]);
				continue;
			}
			for( ; n.compareTo(f[1][maxp - 1]) >= 0; ++maxp) {
				f[0][maxp] = f[1][maxp] = f[2][maxp] = f[3][maxp] = f[4][maxp - 1] = BigInteger.ZERO;
				if((maxp & 1) == 0)
					f[0][maxp] = f[2][maxp >> 1];
				for(int i = 1; i < maxp; ++i) {
					if((maxp - 1) % i == 0) {
						int j = (maxp - 1) / i;
						if((j & 1) == 1) {
							f[4][maxp - 1] = f[4][maxp - 1].add(f[3][i]);
						} else {
							f[4][maxp - 1] = f[4][maxp - 1].subtract(f[3][i]);
						}
					}
					f[0][maxp] = f[0][maxp].add(f[2][maxp - i].multiply(f[2][i]));
					f[2][maxp] = f[2][maxp].add(f[2][maxp - i].multiply(f[4][i]));
				}
				f[3][maxp] = f[2][maxp];
				f[2][maxp] = f[2][maxp].divide(BigInteger.valueOf(maxp - 1));
				f[3][maxp] = f[3][maxp].add(f[2][maxp]);
				f[0][maxp] = f[2][maxp].subtract(f[0][maxp].shiftRight(1));
				f[1][maxp] = f[1][maxp - 1].add(f[0][maxp].multiply(BigInteger.valueOf(maxp)));
				f[0][maxp] = f[0][maxp - 1].add(f[0][maxp]);
			}
			int L = 1, R = maxp - 1;
			while(L < R) {
				int M = (L + R) >> 1;
				if(n.compareTo(f[1][M]) < 0) {
					R = M;
				} else {
					L = M + 1;
				}
			}
			System.out.println(n.multiply(n.subtract(BigInteger.valueOf(3))).shiftRight(1).add(f[0][L - 1]).add(n.subtract(f[1][L - 1]).divide(BigInteger.valueOf(L))).mod(MOD).intValue());
		}
		cin.close();
	}
}
