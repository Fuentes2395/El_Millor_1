#ifndef FECHA_H
#define FECHA_H

#include <iostream>
#include <string>
#include <fstream>

class Fecha
{
    public:
        //CONSTRUCTORES
        Fecha();
        Fecha(int nDia, int nMes, int nAno);
        //GETTERS
        int getDia();
        int getMes();
        int getAno();
        //SETTERS
        void setDia(int nDia);
        void setMes(int nMes);
        void setAno(int nAno);
    private:
        int dia;
        int mes; 
        int ano;
};

//CÓDIGO
//CONSTRUCTORES
Fecha::Fecha()
{
    dia = 01;
    mes = 01;
    ano = 2021;
}
Fecha::Fecha(int nDia, int nMes, int nAno)
{
    dia = nDia;
    mes = nMes;
    ano = nAno;
}

//GETTERS
int Fecha::getDia()
{
    return dia;
}
int Fecha::getMes()
{
    return mes;
}
int Fecha::getAno()
{
    return ano;
}

//SETTERS
void Fecha::setDia(int nDia)
{
    dia = nDia;
}
void Fecha::setMes(int nMes)
{
    mes = nMes;
}
void Fecha::setAno(int nAno)
{
    ano = nAno;
}

#endif