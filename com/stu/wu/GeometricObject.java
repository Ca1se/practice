package com.stu.wu;

public abstract class GeometricObject {
    protected String name;
    protected double area;
    protected double circumference;

    @Override
    public String toString() {
        return String.format("name: %s, area: %lf, circumference: %lf", name, area, circumference);
    }
}
