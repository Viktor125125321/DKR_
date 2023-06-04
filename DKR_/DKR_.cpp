#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

// Клас для логування
class Logger {
public:
    static void log(const std::string& message) {
        std::cout << "[LOG] " << message << std::endl;
    }
};

// Базовий клас для чотирикутників
class Quadrilateral {
protected:
    double sideA;
    double sideB;
    double sideC;
    double sideD;

public:
    Quadrilateral(double a, double b, double c, double d)
        : sideA(a), sideB(b), sideC(c), sideD(d) {}

    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual std::string getType() const = 0;

    void logDetails() const {
        std::string details = "Type: " + getType() + ", Area: " + std::to_string(getArea()) + ", Perimeter: " + std::to_string(getPerimeter());
        Logger::log(details);
    }
};

// Клас для квадратів
//є підкласом Quadrilateral 
//має конструктор, який приймає довжину сторони і передає це значення у конструктор Quadrilateral
//реалізує методи getArea(), getPerimeter() та getType(),
//щоб повернути відповідні значення для квадрата
class Square : public Quadrilateral {
public:
    Square(double side) : Quadrilateral(side, side, side, side) {}

    double getArea() const override {
        return sideA * sideA;
    }

    double getPerimeter() const override {
        return 4 * sideA;
    }

    std::string getType() const override {
        return "Square";
    }
};

// Клас для прямокутників
class Rectangle : public Quadrilateral {
public:
    Rectangle(double length, double width) : Quadrilateral(length, width, length, width) {}

    double getArea() const override {
        return sideA * sideB;
    }

    double getPerimeter() const override {
        return 2 * (sideA + sideB);
    }

    std::string getType() const override {
        return "Rectangle";
    }
};

// Клас для ромбів
class Rhombus : public Quadrilateral {
public:
    Rhombus(double side, double height) : Quadrilateral(side, side, side, side) {}

    double getArea() const override {
        return sideA * sideA;
    }

    double getPerimeter() const override {
        return 4 * sideA;
    }

    std::string getType() const override {
        return "Rhombus";
    }
};

// Клас для довільних чотирикутників
class ArbitraryQuadrilateral : public Quadrilateral {
public:
    ArbitraryQuadrilateral(double a, double b, double c, double d) : Quadrilateral(a, b, c, d) {}


    double getArea() const override {
        // Використовуємо формулу Гаусса для обчислення площі чотирикутника
        double s = (sideA + sideB + sideC + sideD) / 2;
        double area = std::sqrt((s - sideA) * (s - sideB) * (s - sideC) * (s - sideD));
        return area;
    }

    double getPerimeter() const override {
        return sideA + sideB + sideC + sideD;
    }

    std::string getType() const override {
        return "Arbitrary Quadrilateral";
    }
};

int main() {
    std::vector<Quadrilateral*> quadrilaterals;

    // Додавання чотирикутників у масив
    quadrilaterals.push_back(new Square(5.0));
    quadrilaterals.push_back(new Rectangle(4.0, 6.0));
    quadrilaterals.push_back(new Rhombus(3.0, 4.0));
    quadrilaterals.push_back(new ArbitraryQuadrilateral(2.0, 3.0, 4.0, 5.0));

    double maxArea = 0.0;
    double minArea = std::numeric_limits<double>::max();
    double maxPerimeter = 0.0;
    double minPerimeter = std::numeric_limits<double>::max();

    Quadrilateral* maxAreaQuadrilateral = nullptr;
    Quadrilateral* minAreaQuadrilateral = nullptr;
    Quadrilateral* maxPerimeterQuadrilateral = nullptr;
    Quadrilateral* minPerimeterQuadrilateral = nullptr;

    // Перебір чотирикутників для знаходження найбільших та найменших значень площі та периметру
    for (Quadrilateral* quad : quadrilaterals) {
        double area = quad->getArea();
        double perimeter = quad->getPerimeter();

        if (area > maxArea) {
            maxArea = area;
            maxAreaQuadrilateral = quad;
        }

        if (area < minArea) {
            minArea = area;
            minAreaQuadrilateral = quad;
        }

        if (perimeter > maxPerimeter) {
            maxPerimeter = perimeter;
            maxPerimeterQuadrilateral = quad;
        }

        if (perimeter < minPerimeter) {
            minPerimeter = perimeter;
            minPerimeterQuadrilateral = quad;
        }

        // Логування деталей про чотирикутник
        quad->logDetails();
    }

    // Виведення результатів
    std::cout << "Max Area Quadrilateral: ";
    if (maxAreaQuadrilateral != nullptr) {
        maxAreaQuadrilateral->logDetails();
    }

    std::cout << "Min Area Quadrilateral: ";
    if (minAreaQuadrilateral != nullptr) {
        minAreaQuadrilateral->logDetails();
    }

    std::cout << "Max Perimeter Quadrilateral: ";
    if (maxPerimeterQuadrilateral != nullptr) {
        maxPerimeterQuadrilateral->logDetails();
    }

    std::cout << "Min Perimeter Quadrilateral: ";
    if (minPerimeterQuadrilateral != nullptr) {
        minPerimeterQuadrilateral->logDetails();
    }

    // Видалення об'єктів з пам'яті
    for (Quadrilateral* quad : quadrilaterals) {
        delete quad;
    }

    return 0;
}