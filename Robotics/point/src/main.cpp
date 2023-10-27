#include <point.h>
#include <iostream>

int main()
{
    Point pxy1;
    Point pxy2(5,5);
    pxy1.print();
    pxy2.print();
    std::cout << pxy2.getMagnitude() << "\n";
    return 0;
}