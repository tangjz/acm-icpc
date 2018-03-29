import java.util.*;
import java.math.*;

class Fraction {
	BigInteger fz, fm;
	Fraction(BigInteger x, BigInteger y) {
		fz = x;
		fm = y;
	}
	public String toString() {
		BigInteger com = fz.gcd(fm);
		return fz.divide(com) + "/" + fm.divide(com);
	}
	Fraction add(Fraction x) {
		return new Fraction(fz.multiply(x.fm).add(x.fz.multiply(fm)), fm.multiply(x.fm));
	}
	Fraction multiply(Fraction x) {
		return new Fraction(fz.multiply(x.fz), fm.multiply(x.fm));
	}
}

public class Main {
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		int fz = cin.nextInt(), fm = cin.nextInt();
		char[] buf = cin.next().toCharArray();
		cin.close();
		Fraction pH = new Fraction(BigInteger.valueOf(fm), BigInteger.valueOf(fz));
		Fraction pT = new Fraction(BigInteger.valueOf(fm), BigInteger.valueOf(fm - fz));
		int[] nxt = new int[buf.length + 1];
		for(int i = 1, j = 0; i < buf.length; ++i) {
			for( ; j > 0 && buf[i] != buf[j]; j = nxt[j]);
			nxt[i + 1] = buf[i] == buf[j] ? ++j : 0;
		}
		for(int i = buf.length, j = i; i > 0; --i)
			if(i == j) {
				j = nxt[i];
			} else {
				nxt[i] = -1;
			}
		Fraction ans = new Fraction(BigInteger.ZERO, BigInteger.ONE);
		Fraction prd = new Fraction(BigInteger.ONE, BigInteger.ONE);
		for(int i = 0; i < buf.length; ++i) {
			prd = prd.multiply(buf[i] == 'H' ? pH : pT);
			if(nxt[i + 1] >= 0)
				ans = ans.add(prd);
		}
		System.out.println(ans);
	}
}