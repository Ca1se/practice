package com.stu.geo;

public class Rectangle extends GeometricObject {
    private double length;
    private double width;

    public Rectangle(double length, double width) {
        this.length = length;
        this.width = width;
        this.name = "Rectangle";
    }

    @Override
    public double getArea() {
        return length * width;
    }

    @Override
    public double getCircumference() {
        return 2 * (length + width);
    }

    @Override
    public String toString() {
        return String.format("%s, length: %f, width: %f", super.toString(), length, width);
    }
}
