import java.util.*;
import java.math.*;

class Fraction {
    BigInteger fz, fm;
    Fraction(BigInteger x, BigInteger y) {
        fz = x;
        fm = y;
    }
    Fraction(String buf) {
        fz = BigInteger.ZERO;
        fm = BigInteger.ONE;
        for(int i = 0, j = 0; i < buf.length(); ++i) {
            char cur = buf.charAt(i);
            if(cur == '.') {
                j = 1;
            } else {
                fz = fz.multiply(BigInteger.TEN).add(BigInteger.valueOf(cur - '0'));
                if(j == 1)
                    fm = fm.multiply(BigInteger.TEN);
            }
        }
    }
    BigInteger toBigInteger() {
        return fz.divide(fm);
    }
    Fraction substract(BigInteger x) {
        return new Fraction(fz.subtract(fm.multiply(x)), fm);
    }
    public int compareTo(int x) {
        return fz.compareTo(fm.multiply(BigInteger.valueOf(x)));
    }
}

public class Main {
    static Fraction divide(BigInteger a, Fraction b) {
        return new Fraction(a.multiply(b.fm), b.fz);
    }
    static BigInteger solve(Fraction L, Fraction R) {
        BigInteger d = L.toBigInteger();
        L = L.substract(d);
        R = R.substract(d);
        if(L.compareTo(0) == 0 || R.compareTo(1) > 0)
            return divide(BigInteger.ONE, R).toBigInteger().add(BigInteger.ONE);
        return divide(solve(divide(BigInteger.ONE, R), divide(BigInteger.ONE, L)), R).toBigInteger().add(BigInteger.ONE);
    }
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        int t = cin.nextInt();
        for(int tt = 0; tt < t; ++tt) {
            String L = cin.next(), R = cin.next();
            System.out.println(solve(new Fraction(L), new Fraction(R)));
        }
        cin.close();
    }
}