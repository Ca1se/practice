package com.stu.geo;

public class Circle extends GeometricObject {
    private static final double PI = 3.14;
    private double radius;

    public Circle(double radius) {
        this.radius = radius;
        this.name = "Circle";
    }

    @Override
    public double getArea() {
        return radius * radius * PI;
    }

    @Override
    public double getCircumference() {
        return 2 * radius * PI;
    }

    @Override
    public String toString() {
        return String.format("%s, radius: %f", super.toString(), radius);
    }
}
