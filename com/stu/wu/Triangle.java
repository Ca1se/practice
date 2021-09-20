package com.stu.wu;

import java.util.*;

public class Triangle extends GeometricObject {
    private double base;
    private double height;
    private double a;
    private double b;
    private double c;

    public Triangle(double a, double b, double c) {
        this.a = a;
        this.b = b;
        this.c = c;

        double p = (a + b + c) / 2;

        this.area = Math.sqrt(p * (p - a) * (p - b) * (p - c));
        this.circumference = a + b + c;
    }

    public double getArea() {
        return area;
    }

    public double getCircumference() {
        return circumference;
    }

    @Override
    public String toString() {
        return String.format("%s, base: %lf, height: %lf, a: %lf, b: %lf, c: %lf",
            super.toString(), base, height, a, b, c);
    }
}
