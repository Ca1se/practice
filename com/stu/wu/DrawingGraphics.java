package com.stu.wu;

public class DrawingGraphics {
    private GeometricObject[] geometries;

    public DrawingGraphics() {
        geometries = new GeometricObject[2];

        geometries[0] = new Rectangle(1, 2);
        geometries[1] = new Circle(3);
    }
}
