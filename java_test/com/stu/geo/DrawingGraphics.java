package com.stu.geo;

public class DrawingGraphics {
    private GeometricObject[] geometries;
    private final int maxSize;

    private int size = 0;
    private int rectCount = 0;
    private int circleCount = 0;
    private int triCount = 0;

    public DrawingGraphics(int maxSize) {
        geometries = new GeometricObject[maxSize];
        this.maxSize = maxSize;
    }

    public void AddGeometric(GeometricObject geometric) {
        if(size == maxSize) {
            System.err.println("DrawingGraphics::AddGeometric(): geometries is full!");
            return;
        }

        if(geometric instanceof Rectangle) {
            rectCount++;
        }else if(geometric instanceof Circle) {
            circleCount++;
        }else {
            triCount++;
        }

        geometries[size++] = geometric;
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();

        for(int i = 0; i < size; i++) {
            double area = geometries[i].getArea();
            double circumference = geometries[i].getCircumference();
            String graphicInfo = String.format("%s, getArea(): %f, getCircumference(): %f",
                    geometries[i].toString(), area, circumference);
            stringBuilder.append(graphicInfo);
            stringBuilder.append('\n');
        }

        return String.format("Rectangle Count: %d, Circle Count: %d, Triangle Count: %d\n%s",
                rectCount, circleCount, triCount, stringBuilder);
    }
}
