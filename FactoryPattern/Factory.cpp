#include <iostream>
#include <string>
#include <memory>
using namespace std;
// Abstract Base Class
class Shape {
public:
    virtual void draw() const = 0;  // Pure virtual function
};

// Concrete subclass for Circle
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Inside Circle::draw() method." << std::endl;
    }
};

// Concrete subclass for Rectangle
class Rectangle : public Shape {
public:
    void draw() const override {
        std::cout << "Inside Rectangle::draw() method." << std::endl;
    }
};

// Concrete subclass for Square
class Square : public Shape {
public:
    void draw() const override {
        std::cout << "Inside Square::draw() method." << std::endl;
    }
};
// Factory Class
class ShapeFactory {
public:
    static Shape* getShape(const string& shapeType) {
        if (shapeType == "CIRCLE") {
            return new Circle();
        } else if (shapeType == "RECTANGLE") {
            return new Rectangle();
        } else if (shapeType == "SQUARE") {
            return new Square();
        } else {
            return nullptr;
        }
    }
};
int main() {
    auto shape1 = ShapeFactory::getShape("CIRCLE");
    if (shape1) {
        shape1->draw();
    }

    auto shape2 = ShapeFactory::getShape("RECTANGLE");
    if (shape2) {
        shape2->draw();
    }

    auto shape3 = ShapeFactory::getShape("SQUARE");
    if (shape3) {
        shape3->draw();
    }

    return 0;
}
