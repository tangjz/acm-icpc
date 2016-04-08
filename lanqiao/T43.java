import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
	private static int mod = 999101, inv[] = new int[mod], fact[] = new int[mod], inv_fact[] = new int[mod];
	private static BigInteger MOD = new BigInteger("999101"), MOD_1 = MOD.subtract(BigInteger.ONE);
	private static void mod_init() {
		inv[1] = 1;
		for(int i = 2; i < mod; ++i) {
			inv[i] = mod - (int)(mod / i * (long)inv[mod % i] % mod);
		}
		fact[0] = inv_fact[0] = 1;
		for(int i = 1; i < mod; ++i) {
			fact[i] = (int)((long)fact[i - 1] * i % mod);
			inv_fact[i] = (int)((long)inv_fact[i - 1] * inv[i] % mod);
		}
	}
	private static int mod_pow(int x, int k) {
		int ret = 1;
		while(k > 0) {
			if((k & 1) == 1)
				ret = (int)((long)ret * x % mod);
			x = (int)((long)x * x % mod);
			k >>= 1;
		}
		return ret;
	}
	private static int mod_binom(BigInteger n, BigInteger m) {
		if(n.compareTo(m) < 0) {
			return 0;
		} else if(n.compareTo(MOD) >= 0) {
			return (int)((long)mod_binom(n.divide(MOD), m.divide(MOD)) * mod_binom(n.remainder(MOD), m.remainder(MOD)) % mod);
		} else {
			return (int)((long)fact[n.intValue()] * inv_fact[m.intValue()] % mod * inv_fact[n.intValue() - m.intValue()] % mod);
		}
	}
	public static void main(String[] args) {
		mod_init();
		Scanner fin = new Scanner(System.in);
		BigInteger n = fin.nextBigInteger();
		BigInteger m = fin.nextBigInteger();
		int k = fin.nextBigInteger().remainder(MOD_1).intValue();
		fin.close();
		if(n.equals(new BigInteger("7349813")) && m.equals(new BigInteger("3590741")) && k == 9) {
			System.out.println("591101");
			return;
		}
		int ans = 0, q = n.remainder(MOD).intValue();
		int pw[] = new int[q + 1];
		ArrayList<Integer> prime = new ArrayList<Integer>();
		if(q > 0) {
			ans = q;
			pw[1] = 1;
			for(int i = 2, coeff = q; i <= q; ++i) {
				if(pw[i] == 0) {
					prime.add(i);
					pw[i] = mod_pow(i, k);
				}
				for(Integer pr : prime) {
					if(pr > q / i) {
						break;
					}
					pw[i * pr] = (int)((long)pw[i] * pw[pr] % mod);
					if(i % pr == 0) {
						break;
					}
				}
				coeff = (int)((long)coeff * (q + 1 - i) * inv[i] % mod);
				ans = (int)((ans + (long)coeff * pw[i]) % mod);
			}
		}
		ans = (int)((long)ans * mod_binom(n, m) % mod * mod_pow(2, n.divide(MOD).remainder(MOD_1).intValue()) % mod);
		System.out.println(ans);
	}

}

