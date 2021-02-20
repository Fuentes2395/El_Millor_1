#ifndef COBRANZA_H
#define COBRANZA_H

#include <iostream>
#include <string>
#include <fstream>

#include "Fecha.h"

class Cobranza
{
    public:
        //CONSTRUCTORES
        Cobranza();
        Cobranza(std::string nPagoRealizado, std::string nMensualidad, Fecha nFecha);
        //GETTERS
        std::string getPagoRealizado();
        std::string getMensualidad();
        Fecha getFecha();
        //SETTERS
        void setPagoRealizado(std::string nPagoRealizado);
        void setMensualidad(std::string nMenusalidad);
        void setFecha(Fecha nFecha);
    private:
        std::string pagoRealizado;
        std::string mensualidad;
        Fecha fecha;
};

//CÓDIGO
//CONSTRUCTORES
Cobranza::Cobranza()
{
    Fecha f(0,0,0);
    pagoRealizado = "Faltante";
    mensualidad = "N/A";
    fecha = f;
}
Cobranza::Cobranza(std::string nPagoRealizado, std::string nMensualidad, Fecha nFecha)
{
    pagoRealizado = nPagoRealizado;
    mensualidad = nMensualidad;
    fecha = nFecha;
}

//GETTERS
std::string Cobranza::getPagoRealizado()
{
    return pagoRealizado;
}
std::string Cobranza::getMensualidad()
{
    return mensualidad;
}
Fecha Cobranza::getFecha()
{
    return fecha;
}

//SETTERS
void Cobranza::setPagoRealizado(std::string nPagoRealizado)
{
    pagoRealizado = nPagoRealizado;
}
void Cobranza::setMensualidad(std::string nMensualidad)
{
    mensualidad = nMensualidad;
}
void Cobranza::setFecha(Fecha nFecha)
{
    fecha = nFecha;
}

#endif