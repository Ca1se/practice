import java.util.*;

public class RandomString {
    public static String GenerateRandomString(int length, boolean print) {
        if(length < 4 || length > 6) {
            System.err.println("RandomString::GenerateRandomString(): length must be between 4 and 6!");
            return null;
        }
        StringBuffer res = new StringBuffer();
        Random rand = new Random();

        for(int i = 0; i < length; i++) {
            int randInt = rand.nextInt(62);
            if(randInt < 26) res.append((char) ('a' + randInt));
            else if(randInt < 52) res.append((char) ('A' + randInt - 26));
            else res.append((char) ('0' + randInt - 52));
        }

        if(print) System.out.println(res);

        return res.toString();
    }

    public static void main(String[] args) {
        String randomString = GenerateRandomString(5, false);
        System.out.println(randomString);
    }
}