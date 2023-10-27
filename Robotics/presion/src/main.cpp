#include <presion.h>
#include <iostream>

int main()
{
    float PAtm=101325; //Presion Atmosferica al nivel del mar
    
    std::cout<<"INSTANCIA 1:\n";

    Presion problema1;
    problema1.print();
    std::cout<<"\nSeteamos valores\n";
    problema1.setAll(12.0,PAtm,1000,9.81);
    problema1.print();
    std::cout<<"\nCálculo de presón Absoluta\n";
    std::cout <<"Presión Absoluta: "<< problema1.getPAbs() << " Pa\n\n";

     std::cout<<"\nINSTANCIA 2:\n";

    Presion problema2(12.0,PAtm,1000,9.81);
    
    std::cout<<"Profundidad (Altura) = "<<problema2.getH()<<" m \n";
    std::cout<<"Presion Superficial (P_o) = "<<problema2.getPSup()<<" Pa\n";
    std::cout<<"Densidad = "<<problema2.getDens()<<" Kg/m3\n";
    std::cout<<"Gravedad = "<<problema2.getGrav()<<" m/s2\n";

    std::cout<<"\nCálculo de presón Manométrica\n";
    std::cout <<"Presion Manométrica: "<< problema2.getPMan() << " Pa\n";
    
    return 0;
}