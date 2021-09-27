import java.util.Random;

public class Game {
    private static Card.Suit[] suits = Card.Suit.values();
    private static Card.Value[] values = Card.Value.values();

    public void PlayGame() {
        long mem = 0;
        int count = 0;

        Random rand = new Random();
        Card[] cards = new Card[4];

        while(count < 4) {
            int randInt = rand.nextInt(52);
            if((mem & (1 << randInt)) != 0) continue;

            int value = randInt / 4;
            int suit = randInt - value * 4;

            mem = mem | (1 << randInt);

            cards[count++] = new Card(suits[suit], values[value]);
        }

        for(int i = 0; i < 4; i++) {
            System.out.println(cards[i]);
        }
    }
}