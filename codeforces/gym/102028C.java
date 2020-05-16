import java.io.*;
import java.util.*;

public class Main {
	static final int maxn = (int)3e5 + 1;
	static int[] seq = new int[maxn], rid = new int[maxn], cid = new int[maxn];
	static long choose2(int x) {
		return (long)x * (x - 1) / 2;
	}
	public static void main(String[] args) throws IOException {
        InputReader cin = new InputReader(System.in);
        PrintWriter cout = new PrintWriter(System.out);
		int t = cin.nextInt();
		while((t--) > 0) {
			int n = cin.nextInt(), m = cin.nextInt();
			for(int i = 1; i <= n; ++i) {
				int x = cin.nextInt(), y = cin.nextInt();
				seq[i] = x;
				rid[y] = x;
				cid[x] = y;
			}
			int xL = 1, xR = n, dx = 0;
			int yL = 1, yR = n, dy = 0;
			int cLL = cid[1] == 1 ? 1 : 0;
			int cLR = n > 1 && cid[1] == n ? 1 : 0;
			int cRL = cid[n] == 1 ? 1 : 0;
			int cRR = n > 1 && cid[n] == n ? 1 : 0;
			while((m--) > 0) {
				String typ = cin.nextToken();
				int adt = 0;
				if(typ.charAt(0) != '!')
					adt = cin.nextInt();
				switch(typ.charAt(0)) {
				case 'L' :
					dy -= adt;
					while(yL < yR && yL + dy < 1) {
						++yL;
						if(yL == yR)
							break;
						if(rid[yL] <= xL)
							++cLL;
						else if(rid[yL] >= xR)
							++cRL;
					}
					dy = Math.max(dy, 1 - yL);
					break;
				case 'R' :
					dy += adt;
					while(yL < yR && yR + dy > n) {
						--yR;
						if(yL == yR)
							break;
						if(rid[yR] <= xL)
							++cLR;
						else if(rid[yR] >= xR)
							++cRR;
					}
					dy = Math.min(dy, n - yR);
					break;
				case 'U' :
					dx -= adt;
					while(xL < xR && xL + dx < 1) {
						++xL;
						if(xL == xR)
							break;
						if(cid[xL] <= yL)
							++cLL;
						else if(cid[xL] >= yR)
							++cLR;
					}
					dx = Math.max(dx, 1 - xL);
					break;
				case 'D' :
					dx += adt;
					while(xL < xR && xR + dx > n) {
						--xR;
						if(xL == xR)
							break;
						if(cid[xR] <= yL)
							++cRL;
						else if(cid[xR] >= yR)
							++cRR;
					}
					dx = Math.min(dx, n - xR);
					break;
				case '?' :
					int x = seq[adt], y = cid[x];
					cout.printf("%d %d\n", Math.min(Math.max(x, xL), xR) + dx, Math.min(Math.max(y, yL), yR) + dy);
					break;
				case '!' :
					long ans;
					if(xL == xR && yL == yR) {
						ans = choose2(n);
					} else if(xL == xR) {
						ans = choose2(cLL + cRL) + choose2(cLR + cRR);
					} else if(yL == yR) {
						ans = choose2(cLL + cLR) + choose2(cRL + cRR);
					} else {
						ans = choose2(cLL) + choose2(cLR) + choose2(cRL) + choose2(cRR);
					}
					cout.printf("%d\n", ans);
				}
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
