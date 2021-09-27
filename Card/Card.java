public class Card {
    public enum Suit {
        Spade,
        Heart,
        Club,
        Diamond,
        SubJoker,
        Joker
    }

    public enum Value {
        Ace,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Nine,
        Ten,
        Jack,
        Queen,
        King,
    }

    private static String[] valueCover = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    private Suit suit;
    private Value value;

    public Card(Suit suit, Value value) {
        this.suit = suit;
        this.value = value;
    }

    public String getCover() {
        return valueCover[value.ordinal()];
    }

    @Override
    public String toString() {
        return String.format("value: %d, suit: %s, cover: %s",
            value.ordinal(), suit.toString(), getCover());
    }
}