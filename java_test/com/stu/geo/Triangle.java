package com.stu.geo;


public class Triangle extends GeometricObject {
    private double a;
    private double b;
    private double c;

    public Triangle(double a, double b, double c) {
        this.a = a;
        this.b = b;
        this.c = c;
        this.name = "Triangle";
    }

    @Override
    public double getArea() {
        double p = (a + b + c) / 2;
        return Math.sqrt(p * (p - a) * (p - b) * (p - c));
    }

    @Override
    public double getCircumference() {
        return a + b + c;
    }

    @Override
    public String toString() {
        return String.format("%s, a: %f, b: %f, c: %f",
            super.toString(), a, b, c);
    }
}
