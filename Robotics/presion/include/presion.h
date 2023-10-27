/* The point class Header */
#ifndef PRESION_H
#define PRESION_H

class Presion
{
    //private members
    private:
        float profundidad_;
        float presionsup_;
        float densidad_;
        float gravedad_;
    public:
        Presion();
        Presion(float profundidad, float presionsup, float densidad, float gravedad);
        ~Presion();

        float getH(void) const;
        float getPSup(void) const;
        float getDens(void) const;
        float getGrav(void) const;

        void setH(float profundidad);
        void setPSup(float presionsup);
        void setDens(float densidad);
        void setGrav(float gravedad);
        void setAll(float profundidad, float presionsup, float densidad, float gravedad);
        
        double getPMan(void) const;
        double getPAbs(void) const;
        void print(void) const;

};

#endif