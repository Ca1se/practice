import java.util.Random;
import java.util.Scanner;

public class Game {
    public static void main(String[] args) {
        boolean play = true;
        Random rand = new Random();
        Scanner scan = new Scanner(System.in);

        while(play) {
            int randInt = rand.nextInt(100);
            System.out.print("Guess it(0 - 100):");
            int i;
            for(i = 0; i < 5; i++) {
                int gInt = scan.nextInt();
                if(gInt == randInt) {
                    System.out.println("Bingo!");
                    break;
                }
            }
            if(i == 5) System.out.println("You lose!");
            System.out.print("continue?[y/n]");
            char ch = scan.next().charAt(0);
            if(ch != 'y' && ch != 'Y') play = false;
        }
    }
}