#ifndef DEPARTAMENTO_H
#define DEPARTAMENTO_H

#include <iostream>
#include <string>
#include <fstream>

#include "Persona.h"
#include "Cobranza.h"

class Departamento
{
    public:
        //CONSTRUCTORES
        Departamento();
        Departamento(std::string nNumero, Persona nPersona, Cobranza nCobranza);
        //GETTERS
        std::string getNumero();
        Persona getPersona();
        Cobranza getCobranza();
        //SETTERS
        void setNumero(std::string nNumero);
        void setPersona(Persona nPersona);
        void setCobranza(Cobranza nCobranza);
    private:
        std::string numero;
        Persona persona;
        Cobranza cobranza;
};

//CÓDIGO
//CONSTRUCTORES
Departamento::Departamento()
{
    Fecha f(0,0,0);
    Persona p("N/A", "N/A", "N/A");
    Cobranza c("Faltante","N/A", f);
    numero = "N/A";
    persona = p;
    cobranza = c;
}
Departamento::Departamento(std::string nNumero, Persona nPersona, Cobranza nCobranza)
{
    numero = nNumero;
    persona = nPersona;
    cobranza = nCobranza;
}

//GETTERS
std::string Departamento::getNumero()
{
    return numero;
}
Persona Departamento::getPersona()
{
    return persona;
}
Cobranza Departamento::getCobranza()
{
    return cobranza;
}

//SETTERS
void Departamento::setNumero(std::string nNumero)
{
    numero = nNumero;
}
void Departamento::setPersona(Persona nPersona)
{
    persona = nPersona;
}
void Departamento::setCobranza(Cobranza nCobranza)
{
    cobranza = nCobranza;
}

#endif