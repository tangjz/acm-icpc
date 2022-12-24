import java.math.*;
import java.util.*;

public class Main {
	static class Fraction {
		int numerator, denominator;
		Fraction() {
			numerator = 0;
			denominator = 1;
		}
		Fraction(int numerator, int denominator) {
			int common = gcd(numerator, denominator);
			this.numerator = numerator / common;
			this.denominator = denominator / common;
		}
		static int gcd(int x, int y) {
			while(y != 0) {
				int r = x % y;
				x = y;
				y = r;
			}
			return x;
		}
		Fraction add(Fraction x) {
			return new Fraction(numerator * x.denominator + x.numerator * denominator, denominator * x.denominator);
		}
		Fraction divide(int x) {
			return new Fraction(numerator, denominator * x);
		}
	}

	static final int maxd = 11;
	static final Fraction[] coeff = prepare();
	static Fraction[] prepare() {
		Fraction[] c = new Fraction[maxd];
		int[] s = new int[maxd];
		s[0] = 1;
		for(int i = 1; i < maxd; ++i) {
			c[i] = new Fraction();
			for(int j = i; j > 0; --j) {
				s[j] = (i - 1) * s[j] + s[j - 1];
				c[i] = c[i].add(new Fraction(s[j] * j, (j + 1) * (j + 2)));
			}
			c[i] = c[i].divide(i + i);
			s[0] = 0;
		}
		return c;
	}
	
	static final int sftLen = 300;
	static final BigInteger pi = new BigInteger("6399537258350533155033943479672909410430835048980332607456213094006036735347581777115873280");
	static final BigInteger one = BigInteger.ONE.shiftLeft(sftLen);
	static final BigInteger e = exp(one);
	static BigInteger exp(BigInteger value) {
		if(value.compareTo(BigInteger.ZERO) == 0)
			return one;
		if(value.compareTo(one) > 0) {
			BigInteger[] rem = value.divideAndRemainder(one);
			BigInteger ret = exp(rem[1]), tmp = e;
			for(int k = rem[0].intValue(); k > 0; k >>= 1) {
				if((k & 1) == 1)
					ret = ret.multiply(tmp).shiftRight(sftLen);
				if(k > 1)
					tmp = tmp.multiply(tmp).shiftRight(sftLen);
			}
			return ret;
		}
		BigInteger ret = one, fz = one, fm = BigInteger.ONE;
		for(int i = 1; ; ++i) {
			fz = fz.multiply(value).shiftRight(sftLen);
			fm = fm.multiply(BigInteger.valueOf(i));
			if(fz.compareTo(fm) < 0)
				break;
			ret = ret.add(fz.divide(fm));
		}
		return ret;
	}
	static BigInteger ln(BigInteger value) {
		int sft;
		for(sft = 0; value.compareTo(one.shiftLeft(1)) >= 0; ++sft)
			value = value.shiftLeft(sftLen).divide(e);
		value = one.subtract(value);
		BigInteger ret = BigInteger.ZERO, tmp = one;
		for(int i = 1; ; ++i) {
			tmp = tmp.multiply(value).shiftRight(sftLen);
			BigInteger dt = BigInteger.valueOf(i);
			if(tmp.abs().compareTo(dt) < 0)
				break;
			ret = ret.subtract(tmp.divide(dt));
		}
		return ret.add(BigInteger.valueOf(sft).shiftLeft(sftLen));
	}

	static final BigInteger ln10 = ln(BigInteger.TEN.shiftLeft(sftLen));
	static final BigInteger adt = ln(pi.shiftLeft(1)).shiftRight(1);
	static BigInteger getHighDigits(int n, int m) {
		BigInteger val = BigInteger.valueOf(n + 1).shiftLeft(sftLen);
		val = ln(val).multiply(BigInteger.valueOf(n + n + 1)).shiftRight(1).subtract(val).add(adt);
		BigInteger prd = BigInteger.ONE;
		for(int i = 1; i < maxd; ++i) {
			prd = prd.multiply(BigInteger.valueOf(n + 1 + i));
			BigInteger fz = BigInteger.valueOf(coeff[i].numerator).shiftLeft(sftLen);
			BigInteger fm = prd.multiply(BigInteger.valueOf(coeff[i].denominator));
			if(fz.compareTo(fm) < 0)
				break;
			val = val.add(fz.divide(fm));
		}
		BigInteger[] rem = val.divideAndRemainder(ln10);
		if(rem[1].compareTo(BigInteger.ZERO) > 0)
			rem[0] = rem[0].add(BigInteger.ONE);
		rem[0] = rem[0].subtract(BigInteger.valueOf(m));
		val = val.subtract(rem[0].multiply(ln10));
		return exp(val).shiftRight(sftLen);
	}
	
	static final int lown = 101;
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		int t = cin.nextInt();
		for(int Case = 1; Case <= t; ++Case) {
			int n = cin.nextInt(), mH = cin.nextInt(), mL = cin.nextInt();
			if(n < lown) {
				BigInteger prd = BigInteger.ONE;
				for(int i = 2; i <= n; ++i)
					prd = prd.multiply(BigInteger.valueOf(i));
				String buf = prd.toString();
				System.out.println(buf.substring(0, Math.min(mH, buf.length())));
				System.out.println(buf.substring(Math.max(buf.length() - mL, 0)));
			} else {
				System.out.println(getHighDigits(n, mH));
				int cnt = 0;
				for(int tmp = n; tmp >= 5; tmp /= 5, cnt += tmp);
				String buf = "";
				if(cnt < mL) {
					BigInteger prd = BigInteger.ONE, mod = BigInteger.ONE;
					for(int i = 0; i < mL; ++i)
						mod = mod.multiply(BigInteger.TEN);
					for(int i = 2; i <= n; ++i)
						prd = prd.multiply(BigInteger.valueOf(i)).mod(mod);
					buf = prd.toString();
				}
				while(buf.length() < mL)
					buf = "0" + buf;
				System.out.println(buf);
			}
		}
		cin.close();
	}
}