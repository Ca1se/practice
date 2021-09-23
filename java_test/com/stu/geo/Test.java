package com.stu.geo;

public class Test {
    public static void main(String[] args) {
        DrawingGraphics graph = new DrawingGraphics(5);

        graph.AddGeometric(new Triangle(1, 1, 1));
        graph.AddGeometric(new Circle(2));
        graph.AddGeometric(new Rectangle(3, 2));

        System.out.println(graph);
    }
}
