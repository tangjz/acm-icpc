import java.util.*;

public class Main {
	static String[] ans = new String[]{"Typically Otaku", "Eye-opener", "Young Traveller", "Excellent Traveller", "Contemporary Xu Xiake"};
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		int t = cin.nextInt();
		while((t--) > 0) {
			int ctr = 0;
			for(int i = 0; i < 4; ++i) {
				int x = cin.nextInt();
				ctr += x > 0 ? 1 : 0;
			}
			System.out.println(ans[ctr]);
		}
		cin.close();
	}
}
