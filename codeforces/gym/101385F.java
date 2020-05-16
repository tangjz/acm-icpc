import java.io.*;
import java.math.BigInteger;

public class Main {
	static final int MaxE = 200, ShiftLen = 500;
	static final BigInteger one = BigInteger.ONE.shiftLeft(ShiftLen);
	static BigInteger getExp(BigInteger value) {
		BigInteger ret = one, fz = one, fm = BigInteger.ONE;
		for(int i = 1; ; ++i) {
			fz = fz.multiply(value).shiftRight(ShiftLen);
			fm = fm.multiply(BigInteger.valueOf(i));
			BigInteger dt = fz.divide(fm);
			if(dt.equals(BigInteger.ZERO) && value.compareTo(BigInteger.valueOf(i).shiftLeft(ShiftLen)) < 0)
				break;
			ret = ret.add(dt);
		}
		return ret;
	}
	static final BigInteger exp = getExp(one);
	static BigInteger getLn(BigInteger value) {
		if(value.compareTo(BigInteger.ZERO) < 0)
			throw new RuntimeException("Logarithm negatively");
		int shift;
		for(shift = 0; value.compareTo(one.shiftLeft(1)) >= 0; ++shift)
			value = value.shiftLeft(ShiftLen).divide(exp);
		value = one.subtract(value);
		BigInteger ret = BigInteger.ZERO, tmp = one;
		for(int i = 1; ; ++i) {
			tmp = tmp.multiply(value).shiftRight(ShiftLen);
			BigInteger dt = tmp.divide(BigInteger.valueOf(i));
			if(dt.equals(BigInteger.ZERO))
				break;
			ret = ret.subtract(dt);
		}
		return ret.add(BigInteger.valueOf(shift).shiftLeft(ShiftLen));
	}
	static BigInteger solve(BigInteger mod, BigInteger mul, BigInteger low, BigInteger upp) {
		if(low.mod(mul).equals(BigInteger.ZERO))
			return low.divide(mul);
		if(!low.divide(mul).equals(upp.divide(mul)))
			return low.divide(mul).add(BigInteger.ONE);
		BigInteger g = mod.gcd(mul);
		if(!low.mod(g).equals(BigInteger.ZERO) && low.divide(g).equals(upp.divide(g)))
			throw new RuntimeException("No solution");
		BigInteger negLow = low.mod(mul), negUpp = upp.mod(mul);
		if(negLow.compareTo(BigInteger.ZERO) > 0)
			negLow = mul.subtract(negLow);
		if(negUpp.compareTo(BigInteger.ZERO) > 0)
			negUpp = mul.subtract(negUpp);
		BigInteger ret = solve(mul, mod.mod(mul), negUpp, negLow);
		return ret.multiply(mod).add(low).subtract(BigInteger.ONE).divide(mul).add(BigInteger.ONE);
	}
	static BigInteger solve(String prefix) {
		for(int ex = 0; ex < MaxE; ++ex)
			if(BigInteger.ONE.shiftLeft(ex).toString().startsWith(prefix))
				return BigInteger.valueOf(ex);
		BigInteger P = new BigInteger(prefix);
		BigInteger ln10 = getLn(BigInteger.TEN.shiftLeft(ShiftLen));
		BigInteger lg2 = getLn(BigInteger.ONE.shiftLeft(ShiftLen + 1)).shiftLeft(ShiftLen).divide(ln10);
		BigInteger lgP = getLn(P.shiftLeft(ShiftLen)).shiftLeft(ShiftLen).divide(ln10).mod(one);
		BigInteger lgP1 = getLn(P.add(BigInteger.ONE).shiftLeft(ShiftLen)).shiftLeft(ShiftLen).divide(ln10).mod(one);
		if(lgP.compareTo(lgP1) <= 0)
			return solve(one, lg2, lgP, lgP1);
		else
			return solve(one, lg2, BigInteger.ZERO, lgP).min(solve(one, lg2, lgP1, one.subtract(BigInteger.ONE)));
	}
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("power.in"));
		BufferedWriter fout = new BufferedWriter(new FileWriter("power.out"));
		fout.write(solve(fin.readLine()).toString() + "\n");
		fin.close();
		fout.close();
	}
}
