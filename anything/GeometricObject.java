public abstract class GeometricObject {
    protected String name;
    protected double area;
    @Override
    public String toString() {
        return String.format("name: %s, area: %lf", name, area);
    }
}
