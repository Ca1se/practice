package com.stu.wu;

public class Rectangle extends GeometricObject {
    private double length;
    private double width;

    public Rectangle(double length, double width) {
        this.length = length;
        this.width = width;

        this.area = length * width;
        this.circumference = 2 * (length + width);
    }

    public double getArea() {
        return area;
    }

    public double getCircumference() {
        return circumference;
    }

    @Override
    public String toString() {
        return String.format("%s, length: %lf, width: %lf", super.toString(), length, width);
    }
}
