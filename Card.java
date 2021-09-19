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
        Eight,
        Nine,
        Ten,
        Jack,
        Queen,
        King,
        SubJoker,
        Joker
    };
    
    private static String[] COVERS = {
        "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "SubJoker", "Joker"
    };
    private Value value;
    private Suit suit;

    public Card(Suit suit, Value value) {
        this.value = value;
        this.suit = suit;
    }

    public Suit getSuit() {
        return suit;
    }

    public Value getValue() {
        return value;
    }

    public String getCover() {
        return COVERS[value.ordinal()];
    }
}