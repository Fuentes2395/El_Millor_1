#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>
#include <string>
#include <fstream>

class Persona
{
    public:
        //CONSTRUCTORES
        Persona();
        Persona(std::string nApellidoPat, std::string nApellidoMat, std::string nNombre);
        //GETTERS
        std::string getApellidoPat();
        std::string getApellidoMat();
        std::string getNombre();
        //SETTERS
        void setApellidoPat(std::string nApellidoPat);
        void setApellidoMat(std::string nApellidoMat);
        void setNombre(std::string nNombre);
    private:
        std::string apellidoPat;
        std::string apellidoMat;
        std::string nombre;

};

//CÓDIGO
//CONSTRUCTORES
Persona::Persona()
{
    apellidoPat = "N/A";
    apellidoMat = "N/A";
    nombre = "N/A";
}
Persona::Persona(std::string nApellidoPat, std::string nApellidoMat, std::string nNombre)
{
    apellidoPat = nApellidoPat;
    apellidoMat = nApellidoMat;
    nombre = nNombre;
}

//GETTERS
std::string Persona::getApellidoPat()
{
    return apellidoPat;
}
std::string Persona::getApellidoMat()
{
    return apellidoMat;
}
std::string Persona::getNombre()
{
    return nombre;
}

//SETTERS
void Persona::setApellidoPat(std::string nApellidoPat)
{
    apellidoPat = nApellidoPat;
}
void Persona::setApellidoMat(std::string nApellidoMat)
{
    apellidoMat = nApellidoMat;
}
void Persona::setNombre(std::string nNombre)
{
    nombre = nNombre;
}


#endif
