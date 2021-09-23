package com.stu.geo;

public abstract class GeometricObject {
    protected String name;

    public abstract double getArea();
    public abstract double getCircumference();

    @Override
    public String toString() {
        return String.format("name: %s", name);
    }
}
