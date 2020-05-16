import java.io.*;
import java.util.*;

public class Main {
	public static void main(String[] args) throws IOException {
        InputReader cin = new InputReader(System.in);
        PrintWriter cout = new PrintWriter(System.out);
		int t = cin.nextInt();
		while((t--) > 0) {
			int a = cin.nextInt(), b = cin.nextInt(), r = cin.nextInt();
			double rr = Math.sqrt(b * b + (a + r) * (a + r));
			double dt = Math.atan2(b, a + r) - Math.PI / 180 * cin.nextInt();
			cout.printf("%.20f%n", rr * Math.cos(Math.max(dt, 0)) - r);
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
        public long nextLong() throws IOException {
            return Long.parseLong(nextToken());
        }
        private BufferedReader  reader;
        private StringTokenizer tokenizer;
    }
}
