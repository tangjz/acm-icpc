import java.util.*;
import java.math.*;

class Fraction {
	BigInteger fz, fm;
	Fraction(BigInteger x, BigInteger y) {
		fz = x;
		fm = y;
	}
	BigInteger floor() {
		return fz.divide(fm);
	}
	BigInteger ceil() {
		BigInteger[] res = fz.divideAndRemainder(fm);
		if(res[1].compareTo(BigInteger.ZERO) > 0)
			res[0] = res[0].add(BigInteger.ONE);
		return res[0];
	}
	Fraction substract(BigInteger x) {
		return new Fraction(fz.subtract(fm.multiply(x)), fm);
	}
	public int compareTo(BigInteger x) {
		return fz.compareTo(fm.multiply(x));
	}
}

public class Main {
	static Fraction divide(BigInteger a, Fraction b) {
		return new Fraction(a.multiply(b.fm), b.fz);
	}
	static Fraction solve(Fraction L, Fraction R, Boolean rev) {
		BigInteger d = L.floor();
		L = L.substract(d);
		R = R.substract(d);
		if(L.compareTo(BigInteger.ZERO) == 0 || R.compareTo(BigInteger.ONE) >= (rev ? 0 : 1)) {
			d = BigInteger.ONE;
		} else {
			d = solve(divide(BigInteger.ONE, R), divide(BigInteger.ONE, L), !rev).fm;
		}
		return new Fraction(d, rev ? divide(d, R).ceil() : divide(d, R).floor().add(BigInteger.ONE));
	}
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		BigInteger fz = BigInteger.ZERO, fm = BigInteger.ONE;
		for(int cnt = cin.nextInt(); cnt > 0; --cnt) {
			fz = fz.multiply(BigInteger.TEN).add(BigInteger.valueOf(cin.nextInt()));
			fm = fm.multiply(BigInteger.TEN);
		}
		Fraction ans = solve(new Fraction(fz, fm), new Fraction(fz.add(BigInteger.ONE), fm), false);
		System.out.printf("%s%n%s%n", ans.fz, ans.fm);
		cin.close();
	}
}
