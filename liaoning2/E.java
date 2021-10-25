import java.math.BigInteger;
import java.util.Scanner;

public class Main {
    public static BigInteger anm(int n, int m) {
        BigInteger res = new BigInteger("1");
        while(n-- != 0) {
            res = res.multiply(new BigInteger(String.valueOf(m)));
            m--;
        }
        return res;
    }

    public static BigInteger cnm(int n, int m) {
        return anm(n, m).divide(anm(n, n));
    }
	public static void main(String[] args) {
		int n, m, t;
		Scanner scan = new Scanner(System.in);
		n = scan.nextInt();
		m = scan.nextInt();
		t = scan.nextInt();
		long ans = 0;
		for(int i = 4; i < Math.min(n + 1, t); i++) {
			    if(t - i > m) continue;
			    ans += (cnm(i, n).multiply(cnm(t - i, m))).longValue();
		    }
		System.out.println(ans);
	}
}
