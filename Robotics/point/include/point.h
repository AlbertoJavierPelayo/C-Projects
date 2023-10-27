/* The point class Header */
#ifndef POINT_H
#define POINT_H
class Point
{
// private members
    private:
        int xvar_;
        int yvar_;
    public:
        Point(int xvar=0, int yvar=0);
        int getX(void) const;
        int getY(void) const;

        void setX(int xvar);
        void setY(int yvar);
        void setXY(int xvar, int yvar);
        
        double getMagnitude(void) const;
        double getArgument(void) const;
        void print(void) const;
};
#endif