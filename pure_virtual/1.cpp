#include <iostream>

/* NOTE: Pure Virtual Function
 * its a Virtual Function where it has no implementation in the base class 
 * and must be overridden in every desired class
 * Syntax:
 *          virtual void myFunction() = 0; // the '= 0 ' makes it pure virtual function
 */

/* NOTE: Abstract Class
 * A class with atleast one virtual function is called abstract class 
 *  -> you cannot create object from an abstract class
 *  -> you can create pointer / reference to it
 */

class Shape { /* Abstract class */

    public:
        virtual double area() = 0; /* pure virtual */
        virtual void draw() = 0; /* pure virtual */

        void describe() {
            std::cout << "Im a shape" << std::endl;
        }

};

class Circle : public Shape {
    private:
        double radius;
    public:
        Circle(double r) : radius(r) {};

        double area() override { /* must implement */
            return 3.14 * radius * radius;
        }

        void draw() override { /* must implement */
            std::cout << "Drawing Circle" << std::endl;
        }
};

class Rectange : public Shape {
    private:
        double w, h;

    public:
        Rectange(double w, double h) : w(w), h(h) { };
        double area() override {
            return w * h;
        }
        void draw() override {
            std::cout << "Drawing Rectange" << std::endl;
        }
};

int main() {
    // Shape s;   /* As now s is an abstract class we cannot instantiate it */

    Shape* s1 = new Circle(5); /* this is valid as its pointer to base */
    Shape* s2 = new Rectange(4,6);

    s1->draw();
    std::cout << "Area: " << s1->area() << std::endl;

    s2->draw();
    std::cout << "Area: " << s2->area() << std::endl;
}
