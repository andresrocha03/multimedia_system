
class Circle {
    private:
        double radius;

    public:
        Circle(double r) : radius(r) {}

        double area() const {
            return 3.14159 * radius * radius;
        }

}