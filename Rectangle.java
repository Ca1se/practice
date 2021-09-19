public class Rectangle extends GeometricObject {
    private double length;
    private double width;
    private double circumference;

    public Rectangle(double length, double width) {
        this.length = length;
        this.width = width;

        this.area = length * width;
        this.circumference = 2 * (length + width);
    }

    public double getArea() {
        return this.area;
    }

    public double getCircumference() {
        return this.circumference;
    }

    @Override
    public String toString() {
        return String.format("name: %s, area: %lf, circumference: %lf", name, area);
    }
}
