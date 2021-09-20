package com.stu.wu;

public class Circle extends GeometricObject {
    private static final double PI = 3.14;
    private double radius;

    public Circle(double radius) {
        this.radius = radius;

        this.area = radius * radius * PI;
        this.circumference = 2 * radius * PI;
    }

    public double getArea() {
        return area;
    }

    public double getCircumference() {
        return circumference;
    }

    @Override
    public String toString() {
        return String.format("%s, radius: %lf", super.toString(), radius);
    }
}
