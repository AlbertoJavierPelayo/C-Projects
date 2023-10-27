#include <string>
#include <iostream>
const double var_PI = 3.14159; // No magic numbers!!!


class Circle
{
    private:
        double radius_; // Data member (Variable)
        std::string color_; // Data member (Variable)
    public:
        Circle(double radius = 1.0, std::string color = "naranja");
        ~Circle();
        void setParams(double radius, std::string color);
        double getRadius(void) const; // Member function (Getters)
        std::string getColor(void) const; // Member function
        double getArea(void) const;// Member function
};

int main()
{
    Circle circulo_uno(10.0, "rojo");
    circulo_uno.setParams(5,"verde");

    std::cout << circulo_uno.getArea() << "\n";
    std::cout << circulo_uno.getRadius() << "\n";

    Circle circulo_dos(10.0);

    std::cout << circulo_dos.getColor() << "\n";

    Circle circulo_tres;
    std::cout << circulo_tres.getColor() << "\n";

    circulo_dos.~Circle();
    return 0;
}

Circle::Circle(double radius, std::string color)
{
    radius_ = radius;
    color_ = color;
}

Circle::~Circle()
{
    std::cout << "Destructor!!! \n";
}

void Circle::setParams(double radius, std::string color)
{
    radius_ = radius;
    color_ = color;
}

double Circle::getRadius(void) const // Member function (Getters)
{
    return radius_;
}

std::string Circle::getColor(void) const // Member function
{
    return color_;
}

double Circle::getArea(void) const// Member function
{
    return radius_*radius_*var_PI;
}