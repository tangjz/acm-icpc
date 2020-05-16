import java.math.BigInteger;
import java.util.*;

public class Main {
	static final int maxt = 50;
	static Random rnd;
	static Scanner cin;
	static BigInteger n;
	static BigInteger getSqrt(BigInteger x) {
		System.out.println("sqrt " + x);
		System.out.flush();
		return cin.nextBigInteger();
	}
	static void printAnswer(ArrayList<BigInteger> res) {
		String buf = "! " + res.size();
		for(BigInteger p : res)
			buf += " " + p;
		System.out.println(buf);
		System.out.flush();
	}
	static boolean validate(ArrayList<BigInteger> primes) {
		for(BigInteger p : primes)
			if(!p.isProbablePrime(maxt))
				return false;
		return true;
	}
	static BigInteger getRandomProperFactor() {
		while(true) {
			BigInteger x = n, y, z;
			while(x.compareTo(n) == 0)
				x = new BigInteger(n.bitLength(), rnd);
			y = n.gcd(x);
			if(y.compareTo(BigInteger.ONE) > 0 && y.compareTo(n) < 0)
				return y;
			y = getSqrt(x.multiply(x).mod(n));
			z = n.gcd(x.add(y));
			if(z.compareTo(BigInteger.ONE) > 0 && z.compareTo(n) < 0)
				return z;
			z = n.gcd(x.subtract(y).abs());
			if(z.compareTo(BigInteger.ONE) > 0 && z.compareTo(n) < 0)
				return z;
		}
	}
	public static void main(String[] args) {
		rnd = new Random();
		cin = new Scanner(System.in);
		n = cin.nextBigInteger();
		ArrayList<BigInteger> factors = new ArrayList<BigInteger>();
		factors.add(n);
		while(!validate(factors)) {
			BigInteger x = getRandomProperFactor();
			boolean upd = true;
			while(upd) {
				upd = false;
				for(BigInteger p : factors) {
					BigInteger r = x.gcd(p);
					if(r.compareTo(BigInteger.ONE) > 0 && r.compareTo(p) < 0) {
						upd = true;
						factors.remove(p);
						factors.add(r);
						factors.add(p.divide(r));
						break;
					}
				}
			}
		}
		printAnswer(factors);
		cin.close();
	}
}