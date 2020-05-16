import java.io.*;
import java.util.*;

public class Main {
	static final int maxn = (int)1e5 + 1;
	static int[] a = new int[maxn];
	public static void main(String[] args) throws IOException {
		InputReader cin = new InputReader(System.in);
		PrintWriter cout = new PrintWriter(System.out);
		int t = cin.nextInt();
		while((t--) > 0) {
			int n = cin.nextInt(), mid = 0;
			for(int i = 1; i < n; ++i) {
				a[i] = cin.nextInt();
				mid += a[i];
			}
			a[0] = a[n] = 0;
			int lcnt = 0, rcnt = 0;
			long pre = 0, suf = 0, ans = 0;
			for(int i = 1; i <= n; ++i) {
				if((i & 1) == 1) { // left
					int val = a[i >> 1];
					mid -= val;
					pre += (long)(lcnt++) * val;
					ans += pre + (long)rcnt * mid + suf;
				} else { // right
					int val = a[n - (i >> 1) + 1];
					mid -= val;
					suf += (long)(rcnt++) * val;
					ans += pre + (long)lcnt * mid + suf;
				}
				cout.printf("%d%c", ans, i < n ? ' ' : '\n');
			}
		}
		cout.close();
	}
	static class InputReader {
		InputReader(InputStream in) {
			this.reader = new BufferedReader(new InputStreamReader(in));
			this.tokenizer = new StringTokenizer("");
		}
		public String nextToken() throws IOException {
			while(!tokenizer.hasMoreTokens())
				tokenizer = new StringTokenizer(reader.readLine());
			return tokenizer.nextToken();
		}
		public int nextInt() throws IOException {
			return Integer.parseInt(nextToken());
		}
		public long nextLong() throws IOException {
			return Long.parseLong(nextToken());
		}
		private BufferedReader reader;
		private StringTokenizer tokenizer;
	}
}
