// The presion class implementation
#include <presion.h>
#include <iostream>


Presion::Presion()
{
    profundidad_=0.0;
    presionsup_=0.0;
    densidad_=0.0;
    gravedad_=0.0;
}
        
Presion::Presion(float profundidad, float presionsup, float densidad, float gravedad)
{
    profundidad_=profundidad;
    presionsup_=presionsup;
    densidad_=densidad;
    gravedad_=gravedad;
}

Presion:: ~Presion()
{

}

float Presion::getH(void) const
{
    return profundidad_;
}

float Presion::getPSup(void) const
{
    return presionsup_;
}

float Presion::getDens(void) const
{
    return densidad_;
}

float Presion::getGrav(void) const
{
    return gravedad_;
}

void Presion::setH(float profundidad)
{
    profundidad_=profundidad;
}

void Presion::setPSup(float presionsup)
{
    presionsup_=presionsup;
}

void Presion::setDens(float densidad)
{
    densidad_=densidad;
}

void Presion::setGrav(float gravedad)
{
    gravedad_=gravedad;
}

void Presion::setAll(float profundidad, float presionsup, float densidad, float gravedad)
{
    profundidad_=profundidad;
    presionsup_=presionsup;
    densidad_=densidad;
    gravedad_=gravedad;
}
        
double Presion::getPMan(void) const
{
    double PMan;
    PMan=densidad_*gravedad_*profundidad_;
    return PMan;
}
double Presion::getPAbs(void) const
{
    double PMan=Presion::getPMan();
    double PAbs=presionsup_+PMan;
    return PAbs;
}
void Presion::print(void) const
{
    std::cout<<"Profundidad (Altura) = "<<profundidad_<<" m \n";
    std::cout<<"Presion Superficial (P_o) = "<<presionsup_<<" Pa\n";
    std::cout<<"Densidad = "<<densidad_<<" Kg/m3\n";
    std::cout<<"Gravedad = "<<gravedad_<<" m/s2\n";
}