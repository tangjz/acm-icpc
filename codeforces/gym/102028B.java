import java.io.*;
import java.util.*;

public class Main {
	static int getLowestTime(int x) {
		long y = (long)Math.sqrt(x + x + 0.25);
		for( ; y > 0 && y * (y + 1) / 2 >= x; y -= 1);
		for( ; y * (y + 1) / 2 < x; y += 1);
		return (int)y;
	}
	static String getFirstTypeSolution(int hpA, int timA, int hpB, int timAB) {
		char[] ans = new char[timAB];
		for(int i = 0; i < timA; ++i)
			ans[i] = 'A';
		for(int i = timA; i < timAB; ++i) {
			ans[i] = 'B';
			hpB -= i + 1;
		}
		if(hpB > 0) {
			int upp = (int)((long)timA * (timA + 1) / 2) - hpA;
			ans[upp - 1] = 'B';
		}
		return String.valueOf(ans);
	}
	static String getSecondTypeSolution(int hpB, int timB, int hpA, int timAB) {
		char[] ans = new char[timAB];
		for(int i = 0; i < timB; ++i)
			ans[i] = 'B';
		for(int i = timB; i < timAB; ++i) {
			ans[i] = 'A';
			hpA -= i + 1;
		}
		int upp = (int)((long)timB * (timB + 1) / 2) - hpB;
		if(upp > 0)
			for(int i = 0; i < timB; ++i) {
				int nxt = upp - (i + 1);
				if(nxt < i + 2) { // the last 'A' must fit the lower bound
					ans[Math.max(i, hpA - 1)] = 'A';
					break;
				} // be able to place further 'A'
				ans[i] = 'A';
				upp = nxt;
				hpA -= i + 1;
			}
		return String.valueOf(ans);
	}
	public static void main(String[] args) throws IOException {
        InputReader cin = new InputReader(System.in);
        PrintWriter cout = new PrintWriter(System.out);
		int t = cin.nextInt();
		while((t--) > 0) {
			int hpA = cin.nextInt(), hpB = cin.nextInt();
			int atkA = cin.nextInt(), atkB = cin.nextInt();
			int timA = getLowestTime(hpA), timB = getLowestTime(hpB);
			int timAB = getLowestTime(hpA + hpB);
			long dmgA = (long)atkA * timA + (long)atkB * timAB;
			long dmgB = (long)atkB * timB + (long)atkA * timAB;
			String ansA = dmgA <= dmgB ? getFirstTypeSolution(hpA, timA, hpB, timAB) : "";
			String ansB = dmgB <= dmgA ? getSecondTypeSolution(hpB, timB, hpA, timAB) : "";
			if(dmgA < dmgB || (dmgA == dmgB && ansA.compareTo(ansB) < 0))
				cout.printf("%d %s%n", dmgA, ansA);
			else
				cout.printf("%d %s%n", dmgB, ansB);
		}
		cout.close();
	}
    static class InputReader {
        InputReader(InputStream in) {
            this.reader = new BufferedReader(new InputStreamReader(in));
            this.tokenizer = new StringTokenizer("");
        }
        public String nextToken() throws IOException {
            while (!tokenizer.hasMoreTokens()) {
                tokenizer = new StringTokenizer(reader.readLine());
            }
            return tokenizer.nextToken();
        }
        public int nextInt() throws IOException {
            return Integer.parseInt(nextToken());
        }
        private BufferedReader reader;
        private StringTokenizer tokenizer;
    }
}
