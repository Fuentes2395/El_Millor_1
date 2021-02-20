#include <iostream>
#include <string>
#include <fstream>
#include <iomanip> //setw
#include <ctime> //https://www.softwaretestinghelp.com/date-and-time-in-cpp/ 
#include <sstream>
#include <stdio.h>

#include "Departamento.h"

void darAltaDatos(Departamento residentes[], int &cont, std::string &numero, std::string &apellidoPat, 
std::string &apellidoMat, std::string &nombre, std::string &mensualidad, std::string &pagoRealizado)
{
    char opcion;
    
    std::cout << "Favor de ingresar datos:" << "\n";
    std::cout << "NÚMERO DEPARTAMENTO: ";
    std::cout << numero << std::endl;
    std::cin.ignore(); //Para que no se salte el std::getline() | https://stackoverflow.com/questions/6649852/getline-not-working-properly-what-could-be-the-reasons
    std::cout << "NOMBRE: ";
    std::getline(std::cin, nombre);
    std::cout << "APELLIDO PATERNO: ";
    std::cin >> apellidoPat;
    std::cout << "APELLIDO MATERNO: ";
    std::cin >> apellidoMat;

    std::ifstream archResidentes ("residentes.csv");

    int conta = 1;
    std::string temp;
    std::string field;

    while (archResidentes.good())
    {
        getline(archResidentes, temp, ',');
        if (temp == numero)
        {
            conta++;
        }
        getline(archResidentes, temp, '\n');
    }

    int tempMensualidad;

    if (conta != 1)
    {
        while (true)
        {
            regresar: //goto regresar
            std::cout << conta-1 << " Personas viven en el departamento " << numero << "." << std::endl;
            std::cout << "¿DESEA DIVIDIR SU MENSUALIDAD EN " << conta << "? (S/n)" << std::endl;
            std::cout << "--> ";
            std::cin >> opcion;
            if (opcion == 'S')
            {
                for (int i = 0; i < cont; i++)
                {
                    if (residentes[i].getNumero() == numero)
                    {
                        /*
                        Convierte primero el objeto con getters a int cont std::stoi y lo guarda en tempMensualidad
                        Despues mensualidad va a ser igual a la conversion de int a string de tempMensualidad con
                        std::to_string()
                        */
                        tempMensualidad = (std::stoi(residentes[i].getCobranza().getMensualidad())*(conta-1)) / conta;
                        mensualidad = std::to_string(tempMensualidad);
                        while (true)
                        {
                            std::cout << "LA MENSUALIDAD EN ESTE CASO SERÍA DE " << mensualidad << 
                            ", ¿ESTA DE ACUERDO? (S/n)" << std::endl;
                            std::cout << "--> ";
                            std::cin >> opcion;
                            if (opcion == 'S')
                            {
                                break;
                            }
                            else if (opcion == 'n')
                            {
                                while (true)
                                {
                                    std::cout << "¿DESEA REGRESAR A LA OPCION DE DIVIDIR? (S/n)" << std::endl;
                                    std::cout << "--> ";
                                    std::cin >> opcion;
                                    if (opcion == 'S')
                                    {
                                        goto regresar; //Regresa a 'regresar' arriba
                                    }
                                    else if (opcion == 'n')
                                    {
                                        break;
                                    }
                                    else
                                    {
                                        std::cout << "FAVOR DE INGRESAR UN VALOR VALIDO" << std::endl;
                                        continue;
                                    }
                                }
                            }
                            else
                            {
                                std::cout << "FAVOR DE INGRESAR UN VALOR VÁLIDO" << std::endl;
                                continue;
                            }  
                        }
                        break;
                    }
                }
                break;
            }
            else if (opcion == 'n')
            {
                for (int i = 0; i < cont; i++)
                {
                    if (residentes[i].getNumero() == numero)
                    {
                        std::cout << "LA MENSUALIDAD DE CADA UNO SERÍA DE " << 
                        residentes[i].getCobranza().getMensualidad() << ", ¿ESTA DE ACUERDO? (S/n)" << std::endl;
                        std::cout << "--> ";
                        std::cin >> opcion;
                        if (opcion == 'S')
                        {
                            mensualidad = residentes[i].getCobranza().getMensualidad();
                            break;
                        }
                        else if (opcion == 'n')
                        {
                            while (true)
                            {
                                std::cout << "¿QUIERE MODIFICAR LAS OPCIONES? (S/n)" << std::endl;
                                std::cout << "--> ";
                                std::cin >> opcion;
                                if (opcion == 'S')
                                {
                                    goto regresar;
                                }
                                else if (opcion == 'n')
                                {
                                    break;
                                }
                                else
                                {
                                    std::cout << "FAVOR DE INGRESAR UN VALOR VÁLIDO" << std::endl;
                                    continue;
                                }
                            }
                        }
                        else
                        {
                            std::cout << "FAVOR DE INGRESAR UN VALOR VÁLIDO" << std::endl;
                            continue;
                        }
                    }
                }
               break;
            }
            else
            {
                std::cout << "FAVOR DE INGRESAR UN VALOR VÁLIDO" << std::endl;
            }
        }
    }
    else
    {
        std::cout << "MENSUALIDAD: ";
        std::cin >> mensualidad;
    }
    

    while (true)
    {
        std::cout << "¿YA REALIZÓ SU PRIMER PAGO? (S/n)";
        std::cout << "--> ";
        std::cin >> opcion;

        if (opcion == 'S')
        {
            pagoRealizado = "Pagada";
            break;
        }
        else if (opcion == 'n')
        {
            pagoRealizado = "Faltante";
            break;
        }
        else
        {
            std::cout << "Favor de ingresar un valor válido." << "\n";
            continue;
        }   
    }
}

void imprimirResidentes(Departamento residentes[], int &cont)
{
    std::cout << std::endl;
    std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" <<
    "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << std::endl;
    std::cout << "VER RESIDENTES" << "\n";
    std::cout << "Departamento" << std::setw(17) << "Apellido Pat" << std::setw(17) << "Apellido Mat" << std::setw(20) << 
    "Nombre Completo" << std::setw(16) << "Mensualidad" << std::setw(20) << "Estado de Renta" << "\n";

    for(int i = 0; i < cont; i++)
    {
        std::cout << std::setw(12) << residentes[i].getNumero() << std::setw(17) << residentes[i].getPersona().getApellidoPat() 
        << std::setw(17) << residentes[i].getPersona().getApellidoMat() << std::setw(20) << 
        residentes[i].getPersona().getNombre() << std::setw(11) << "$" << residentes[i].getCobranza().getMensualidad() << 
        std::setw(20) << residentes[i].getCobranza().getPagoRealizado() << "\n";
    }

    std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" <<
    "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << std::endl;
}

void cargarDatos(Departamento residentes[], int &cont)
{
    cont = 0;

    std::string numero;
    std::string apellidoPat;
    std::string apellidoMat;
    std::string nombre;
    std::string mensualidad;
    std::string pagoRealizado;
    
    std::ifstream csvResidentes;
    csvResidentes.open("residentes.csv");

    while (csvResidentes.good())
    {
        getline(csvResidentes, numero, ',');
        getline(csvResidentes, apellidoPat, ',');
        getline(csvResidentes, apellidoMat, ',');
        getline(csvResidentes, nombre, ',');
        getline(csvResidentes, mensualidad, ',');
        getline(csvResidentes, pagoRealizado, '\n');

        residentes[cont].setNumero(numero);
        Persona mainP(apellidoPat, apellidoMat, nombre);
        residentes[cont].setPersona(mainP);
        Fecha mainF;
        Cobranza mainC(pagoRealizado, mensualidad, mainF);
        residentes[cont].setCobranza(mainC);

        cont++;
    }
    cont--;
}

std::string mensualidadEscrita(std::string mes)
{
    if (mes == "1")
    {
        mes = "Enero";
    }
    else if (mes == "2")
    {
        mes = "Febrero";
    }
    else if (mes == "3")
    {
        mes = "Marzo";
    }
    else if (mes == "4")
    {
        mes = "Abril";
    }
    else if (mes == "5")
    {
        mes = "Mayo";
    }
    else if (mes == "6")
    {
        mes = "Junio";
    }
    else if (mes == "7")
    {
        mes = "Julio";
    }
    else if (mes == "8")
    {
        mes = "Agosto";
    }
    else if (mes == "9")
    {
        mes = "Septiembre";
    }
    else if (mes == "10")
    {
        mes = "Octubre";
    }
    else if (mes == "11")
    {
        mes = "Noviembre";
    }
    else if (mes == "12")
    {
        mes = "Diciembre";
    }
    
    return mes;
}

void buscarResidente(Departamento residentes[], int &cont)
{
    std::string numDepa;
    int tempI = 0;
    bool loop = true;

    std::cout << std::endl;
    std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << std::endl; 
    std::cout << "FAVOR DE INGRESAR NÚMERO DE DEPARTAMENTO" << "\n";
    std::cout << "--> ";
    std::cin >> numDepa;
    std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << std::endl; 
    
    if (numDepa == "r")
    {
        return;
    }
    
    for (int i = 0; i < cont; i++)
    {
        if (numDepa == residentes[i].getNumero() && tempI == 0)
        {
            loop = false;
            tempI++;
            
            std::cout << std::endl;
            std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" <<
            "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << std::endl;

            std::cout << "Departamento" << std::setw(17) << "Apellido Pat" << std::setw(17) 
            << "Apellido Mat" << std::setw(20) << "Nombre Completo" << std::setw(16) << "Mensualidad" 
            << std::setw(20) << "Estado de Renta" << "\n";

            std::cout << std::setw(12) << residentes[i].getNumero() << std::setw(17) 
            << residentes[i].getPersona().getApellidoPat() << std::setw(17) << residentes[i].getPersona().getApellidoMat() 
            << std::setw(20) << residentes[i].getPersona().getNombre() << std::setw(11) << "$" 
            << residentes[i].getCobranza().getMensualidad() << std::setw(20) << 
            residentes[i].getCobranza().getPagoRealizado() << std::endl;
        }
        else if (numDepa == residentes[i].getNumero() && tempI != 0)
        {
            std::cout << std::setw(12) << residentes[i].getNumero() << std::setw(17) 
            << residentes[i].getPersona().getApellidoPat() << std::setw(17) << residentes[i].getPersona().getApellidoMat() 
            << std::setw(20) << residentes[i].getPersona().getNombre() << std::setw(11) << "$" 
            << residentes[i].getCobranza().getMensualidad() << std::setw(20) << 
            residentes[i].getCobranza().getPagoRealizado() << std::endl;
        }
        else if (i == cont-1)
        {
            std::cout << std::endl;
            std::cout << "EL DEPARTAMENTO INGRESADO NO EXISTE" << "\n";
        }
    }
}

void agregarResidentes(Departamento residentes[], int &cont)
{
    //Declaración de variables
    std::string numero;
    std::string apellidoPat;
    std::string apellidoMat;
    std::string nombre;
    std::string mensualidad;
    std::string pagoRealizado;
    char opcion;
    bool decidir = true;
    int limite = 0;
    bool boolImprimir = true;
    bool dividirDinero = false;

    ingresar: //Sali de la loop grande y lo vuelvo a repetir desde aqui con goto
    std::cout << "INGRESAR NÚMERO DE DEPARTAMENTO: " << std::endl;
    std::cout << "--> ";
    std::cin >> numero;

    std::cout << std::endl;
    std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" <<
    "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << std::endl;

    for (int i = 0; i < cont+1; i++)
    {
        if (residentes[i].getNumero() == numero)
        {
            decidir = false;
            
            if (boolImprimir == true)
            {
                std::cout << "Departamento" << std::setw(17) << "Apellido Pat" << std::setw(17) 
                << "Apellido Mat" << std::setw(20) << "Nombre Completo" << std::setw(16) << "Mensualidad" 
                << std::setw(20) << "Estado de Renta" << "\n";

                boolImprimir = false;
            }
            std::cout << std::setw(12) << residentes[i].getNumero() << std::setw(17) 
            << residentes[i].getPersona().getApellidoPat() << std::setw(17) << residentes[i].getPersona().getApellidoMat() 
            << std::setw(20) << residentes[i].getPersona().getNombre() << std::setw(11) << "$" 
            << residentes[i].getCobranza().getMensualidad() << std::setw(20) << 
            residentes[i].getCobranza().getPagoRealizado() << std::endl;
        }
        else if (cont == 0 || i == cont-1 && decidir == true)
        {
            while (true)
            {
                std::cout << "NADIE VIVE EN EL DEPARTAMENTO " << numero << ". ¿DESEA AGREGARLO A LA LISTA? (S/n)" 
                << std::endl;
                std::cout << "--> ";
                std::cin >> opcion;
                if (opcion == 'S')
                {
                    darAltaDatos(residentes, cont, numero, apellidoPat, apellidoMat, nombre, mensualidad, pagoRealizado);
                    break;
                }
                else if (opcion == 'n')
                {
                    while (true)
                    {
                        std::cout << "¿DESEA CAMBIAR EL NÚMERO DE DEPARTAMENTO? (S/r)" << std::endl;
                        std::cout << "--> ";
                        std::cin >> opcion;
                        if (opcion == 'S')
                        {
                            goto ingresar; //El goto te regresa a la parte de codigo que marcas con ingresar:
                        }
                        else if (opcion == 'r')
                        {
                            return;
                        }
                        else
                        {
                            std::cout << "FAVOR DE INGRESAR UN VALOR VÁLIDO" << std::endl;
                            continue;
                        }
                    }
                }
                else
                {
                    std::cout << "FAVOR DE INGRESAR UN VALOR VÁLIDO" << std::endl;
                    continue;
                }
            }
        }
    }

    if (decidir == false)
    {
        while (true)
        {
            std::cout << "ELLOS VIVEN EN ESTE DEPARTAMENTO" << std::endl;
            std::cout << "DESEA AGREGARLOS? (S/n)" << std::endl;
            std::cout << "--> ";
            std::cin >> opcion;
            if (opcion == 'S')
            {
                darAltaDatos(residentes, cont, numero, apellidoPat, apellidoMat, nombre, mensualidad, pagoRealizado);
                dividirDinero = true;
                break;
            }
            else if (opcion == 'n')
            {
                break;
            }
            else
            {
                std::cout << "FAVOR DE AGREGAR UN VALOR VÁLIDO" << std::endl;
                continue;
            }
        }
    }

    std::ofstream crearArchivo ("tempResidentes.csv");
  
    for (int i = 0; i < cont; i++)
    {
        if (numero != residentes[i].getNumero())
        {
            crearArchivo << residentes[i].getNumero() << "," << residentes[i].getPersona().getApellidoPat() <<
            "," << residentes[i].getPersona().getApellidoMat() << "," << residentes[i].getPersona().getNombre() <<
            "," << residentes[i].getCobranza().getMensualidad() << "," << residentes[i].getCobranza().getPagoRealizado()
            << "\n";
        }
        else if (numero == residentes[i].getNumero())
        {
            crearArchivo << residentes[i].getNumero() << "," << residentes[i].getPersona().getApellidoPat() <<
            "," << residentes[i].getPersona().getApellidoMat() << "," << residentes[i].getPersona().getNombre() <<
            "," << mensualidad << "," << residentes[i].getCobranza().getPagoRealizado()
            << "\n";
        }
    }

    crearArchivo << numero << "," << apellidoPat << "," << apellidoMat << "," << nombre  << "," 
    << mensualidad << "," << pagoRealizado << "\n";
    
    remove("residentes.csv");

    rename("tempResidentes.csv", "residentes.csv");

    //crea un archivo
    std::ofstream menResidentes;
    menResidentes.open("mensualidadResidentes/" + numero + "_" + apellidoPat + apellidoMat + nombre + ".csv", 
    std::ios::app);

    time_t ttime = time(NULL);
    tm *local_time = localtime(&ttime);

    std::string mes = std::to_string(local_time->tm_mon + 1);
    mes = mensualidadEscrita(mes);

    menResidentes << local_time->tm_mday << "," << mes << "," << local_time->tm_year + 1900 << "," 
    << pagoRealizado << "\n";
}

void agregarMensualidad(Departamento residentes[], int &cont)
{   
    char opcion;
    std::string pagoRealizado;
    int contResidentes = 0;
    std::string numDepa;
    bool numDepaBool = false;

    time_t ttime = time(NULL);
    tm *local_time = localtime(&ttime);

    regresar: //goto regresar

    while (true)
    {
        std::cout << "FAVOR DE INGRESAR EL NÚMERO DE DEPARTAMENTO: " << std::endl;
        std::cout << "--> ";
        std::cin >> numDepa;
        for (int i = 0; i < cont; i++)
        {        
            if (numDepa == residentes[i].getNumero())
            {
                numDepaBool = true;
                std::cout << "¿Desea agregar una mensualidad al residente: " << residentes[i].getPersona().getNombre() << " " <<
                residentes[i].getPersona().getApellidoPat() << " del departamento " << residentes[i].getNumero() << "?"
                << " (S/n)" << "\n";
                std::cout << "--> ";
                std::cin >> opcion;

                if (opcion == 'S')
                {
                    contResidentes = i;
                    break;
                }
                else if (opcion == 'n' && i == cont-1)
                {
                    std::cout << "NINGÚN RESIDENTE SELECCIONADO" << std::endl;
                    continue;
                }
                else
                {
                    continue;
                } 
            }
            else if (numDepaBool == false && i == cont-1)
            {
                while (true)
                {
                    std::cout << "EL DEPARTAMENTO SELECCIONADO NO EXISTE." << std::endl;
                    std::cout << "¿DESEA AGREGARLO?" << std::endl;
                    std::cout << "--> ";
                    std::cin >> opcion;

                    if (opcion == 'S')
                    {
                        break;
                    }
                    else if (opcion == 'n')
                    {
                        goto regresar; //regresar arriba
                    }
                    else
                    {
                        std::cout << "FAVOR DE INGRESAR UN VALOR VÁLIDO" << std::endl;
                        continue;
                    }   
                }
            }
        }
        break;
    }
    
    std::string mes = std::to_string(local_time->tm_mon + 1);
    mes = mensualidadEscrita(mes);

    std::string rDia;
    std::string rMes;
    std::string rAno;
    std::string rPagado;

    std::cin.clear();
    std::cin.ignore();

    while (true)
    {
        if (opcion == 'S')
        {
            std::ofstream archivoMensualidad("mensualidadResidentes/" + residentes[contResidentes].getNumero() + "_" +
            residentes[contResidentes].getPersona().getApellidoPat() + residentes[contResidentes].getPersona().getApellidoMat() + 
            residentes[contResidentes].getPersona().getNombre() + ".csv", std::ios::app);

            while (true)
            {
                std::cout << "¿YA REALIZÓ EL PAGO DEL MES DE " << mes << " DEL " << local_time->tm_year + 1900
                << "? (S/n)";
                std::cout << "--> ";
                std::cin >> opcion;

                if (opcion == 'S')
                {
                    std::ifstream leerArchivo("mensualidadResidentes/" + residentes[contResidentes].getNumero() 
                    + "_" + residentes[contResidentes].getPersona().getApellidoPat() + 
                    residentes[contResidentes].getPersona().getApellidoMat() + 
                    residentes[contResidentes].getPersona().getNombre() + ".csv");

                    while (leerArchivo.good())
                    {
                        getline(leerArchivo, rDia, ',');
                        getline(leerArchivo, rMes, ',');
                        getline(leerArchivo, rAno, ',');
                        getline(leerArchivo, rPagado, '\n');

                        if (rPagado == "Faltante")
                        {
                            std::cout << "DESPUES SE CAMBIA" << std::endl;
                        }

                        if (rMes == mes && rAno == std::to_string(local_time->tm_year + 1900))
                        {
                            while (true)
                            {
                                std::cout << "YA EXISTE ESTA DADO DE ALTA EL MES DE " << rMes << " DEL "
                                << rAno << ". ¿DESEA AGREGARLO DE TODOS MODOS? (S/n)" << std::endl;
                                std::cout << "--> ";
                                std::cin >> opcion;
                                
                                if (opcion == 'S')
                                {
                                    //se sale del loop de while(leerArchivo.good()) para que solo se agregue uno
                                    goto salir; 
                                }
                                else if (opcion == 'n')
                                {
                                    std::cout << "REGRESANDO AL MENÚ DE INICIO" << std::endl;
                                    return;
                                }
                                else
                                {
                                    std::cout << "FAVOR DE INGRESAR UN VALOR VÁLIDO" << std::endl;
                                    continue;
                                }
                            }
                        }
                    }
                    
                    salir: ////goto salir ARRIBA
                    pagoRealizado = "Pagada";
                    break;
                }
                else if (opcion == 'n')
                {
                    pagoRealizado = "Faltante";
                    break;
                }
                else
                {
                    std::cout << "Favor de ingresar un valor válido." << "\n";
                    continue;
                }   
            }

            archivoMensualidad << local_time->tm_mday << "," << mes  << "," 
            << local_time->tm_year + 1900 << "," << pagoRealizado << "\n";

            break;
        }
        else if (opcion == 'n')
        {
            return;
        }
        else if (opcion != 'S' || opcion != 'n')
        {
            std::cout << "Favor de ingresar un valor válido" << "\n";
            continue;
        }
        
    } 
}

void cambiarMensualidad(Departamento residentes[], int &cont)
{
    std::string numDepa;
    bool numDepaBool = false;
    char opcion;
    int contResidentes;
    
    bool loop1 = true;
    bool loop2 = true;
    while (loop1)
    {
        //Puede ser que no se ocupe per por si las moscas
        loop1 = true;
        loop2 = true;

        std::cout << "FAVOR DE INGRESAR EL NÚMERO DE DEPARTAMENTO" << std::endl;
        std::cout << "--> ";
        std::cin >> numDepa;
        
        for (int i = 0; i < cont; i++)
        {
            if (numDepa == residentes[i].getNumero())
            {
                numDepaBool = true;
                std::cout << "Desea revisar si el residente: " << residentes[i].getPersona().getNombre() << " " <<
                residentes[i].getPersona().getApellidoPat() << " del departamento: " << residentes[i].getNumero() <<
                " tiene un pago faltante? (S/n)" << std::endl;
                std::cout << "--> ";
                std::cin >> opcion;

                if (opcion == 'S')
                {
                    contResidentes = i;
                    loop1 = false;
                    break;
                }
                else if (opcion == 'n')
                {
                    if (i == cont-1 && numDepaBool == true)
                    {
                        while (loop2)
                        {
                            std::cout << "NINGUN DEPARTAMENTO SELECCIONADO" << std::endl;
                            std::cout << "¿DESEA REGRESAR AL MENU DE INICIO? (S/n)" << std::endl;
                            std::cout << "--> ";
                            std::cin >> opcion;
                            if (opcion == 'S')
                            {
                                return;
                            }
                            else if (opcion == 'n')
                            {
                                loop2 = false;
                            }
                            else
                            {
                                std::cout << "FAVOR DE INGRESAR UN VALOR VÁLIDO" << std::endl;
                                continue;
                            }
                        }
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    std::cout << "FAVOR DE INGRESAR UN VALOR VÁLIDO" << std::endl;
                    i--;
                    continue;
                }
            }
            else if (i == cont-1 && numDepaBool == false)
            {
                while (loop2)
                {
                    std::cout << "EL DEPARTAMENTO INGRESADO NO EXISTE" << std::endl;
                    std::cout << "¿DESEA REGRESAR AL MENU DE INICIO? (S/n)" << std::endl;
                    std::cout << "--> ";
                    std::cin >> opcion;
                    if (opcion == 'S')
                    {
                        return;
                    }
                    else if (opcion == 'n')
                    {
                        loop2 = false;
                    }
                    else
                    {
                        std::cout << "FAVOR DE INGRESAR UN VALOR VÁLIDO" << std::endl;
                        continue;
                    }
                }
            }
        }
    }

    loop1 = true;
    loop2 = true;

    std::string dia;
    std::string mes;
    std::string ano;
    std::string estatus;

    std::string tempS = "temp";

    std::ifstream archivoIndividual ("mensualidadResidentes/" + residentes[contResidentes].getNumero() + "_" +
    residentes[contResidentes].getPersona().getApellidoPat() + residentes[contResidentes].getPersona().getApellidoMat()
    + residentes[contResidentes].getPersona().getNombre() + ".csv");

    std::ofstream tempo;
    tempo.open("mensualidadResidentes/" + tempS + ".csv");

    std::string arregloDia[1000];
    std::string arregloMes[1000];
    std::string arregloAno[1000];
    std::string arregloEstatus[1000];
    int i2 = 0;
    
    while (archivoIndividual.good())
    {
        getline(archivoIndividual, dia, ',');
        getline(archivoIndividual, mes, ',');
        getline(archivoIndividual, ano, ',');
        getline(archivoIndividual, estatus);

        arregloDia[i2] = dia;
        arregloMes[i2] = mes;
        arregloAno[i2] = ano;
        arregloEstatus[i2] = estatus;

        i2++;
    }

    for (int i = 0; i < i2-1; i++)
    {
        if (arregloEstatus[i] == "Faltante")
        {
            while (true)
            {
                std::cout << "La mensualidad de " << mes << " del " << ano << " no ha sido pagada." << std::endl;
                std::cout << "¿DESEA CAMBIAR SU ESTATUS A \"Pagada\"? (S/n)" << std::endl;
                std::cout << "--> ";
                std::cin >> opcion;

                if (opcion == 'S')
                {
                    tempo << arregloDia[i] << "," << arregloMes[i] << "," << arregloAno[i] << "," << "Pagada" << "\n";
                    break;
                }
                else if (opcion == 'n')
                {
                    tempo << arregloDia[i] << "," << arregloMes[i] << "," << arregloAno[i] << "," << arregloEstatus[i]<< "\n";
                    break;
                }
                else
                {
                    std::cout << "FAVOR DE INGRESAR UN VALOR VÁLIDO" << std::endl;
                    continue;
                }
            }
        }
        else 
        {
            tempo << arregloDia[i] << "," << arregloMes[i] << "," << arregloAno[i] << "," << arregloEstatus[i]<< "\n";
        }
    }



    //I named variables that are equal to "residentes[] (object)"
    std::string tempNum = residentes[contResidentes].getNumero();
    std::string tempAPat = residentes[contResidentes].getPersona().getApellidoPat();
    std::string tempAMat = residentes[contResidentes].getPersona().getApellidoMat();
    std::string tempNombre = residentes[contResidentes].getPersona().getNombre();

    std::string str = "mensualidadResidentes/" + tempNum + "_" + tempAPat + tempAMat + tempNombre + ".csv";
    const char * c = str.c_str();
    
    remove(c);
    
    rename("mensualidadResidentes/temp.csv", c);
}

int main()
{
    //Creación de variables utilizadas en main()
    Departamento residentes[1000];
    int cont = 0;
    char opcion;
    bool loop = true;

    //Función que carga los valores de "residentes.csv"
    cargarDatos(residentes, cont);
    std::cout << cont << std::endl;

    //Inicio Bonito
    std::cout << "\n";
    std::cout << " ______ _   __  __ _ _ _            " << std::endl;
    std::cout << "|  ____| | |  \\/  (_) | |           " << std::endl;
    std::cout << "| |__  | | | \\  / |_| | | ___  _ __ " << std::endl;
    std::cout << "|  __| | | | |\\/| | | | |/ _ \\| '__|" << std::endl;
    std::cout << "| |____| | | |  | | | | | (_) | |   " << std::endl;
    std::cout << "|______|_| |_|  |_|_|_|_|\\___/|_|   " << std::endl;
    std::cout << "+-+-+-+-+-+-+-+-+-+" << std::endl;
    std::cout << "SISTEMA DE COBRANZA" << std::endl;
    std::cout << "+-+-+-+-+-+-+-+-+-+" << std::endl;

    //Loop para que el switch se repita varias veces
    while (loop)
    {
        std::cout << std::endl;
        std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
        std::cout << "INICIO" << std::endl;
        std::cout << "FAVOR DE SELECCIONAR UNA DE LAS SIGUIENTES OPCIONES" << std::endl;
        std::cout << "    a) Ver Residentes" << std::endl;
        std::cout << "    b) Agregar Residentes" << std::endl;
        std::cout << "    c) Mensualidades" << std::endl;
        std::cout << "    s) SALIR" << std::endl;
        std::cout << "    --> ";
        std::cin >> opcion;
        std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
        std::cout << std::endl;
        switch (opcion)
        {
        case 'a':
            while (loop)
            {
                std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
                std::cout << "FAVOR DE SELECCIONAR UNA DE LAS SIGUIENTES OPCIONES" << std::endl;
                std::cout << "    a) VER TODOS los residentes" << std::endl;
                std::cout << "    b) BUSCAR residente" << std::endl;
                std::cout << "    r) Regresar" << std::endl;
                std::cout << "    --> ";
                std::cin >> opcion;
                std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
                switch (opcion)
                {
                case 'a':
                    loop = false;
                    imprimirResidentes(residentes, cont); //Imprime lista con todas las funciones
                    cargarDatos(residentes, cont); //Vuelve a cargar los datos por si acaso
                    break;

                case 'b':
                    loop = false;
                    buscarResidente(residentes, cont); //Busca un residente en específico
                    cargarDatos(residentes, cont); //Vuelve a cargar los datos por si acaso
                    break;

                case 'r':
                    loop = false; //Regresa a la página de inicio
                    break;
            
                default: //Cualquier otro valor marca que lo vuelvas a meter en la terminal
                    std::cout << std::endl;
                    std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
                    std::cout << "FAVOR DE INGRESAR UN VÁLIDO" << std::endl;
                    std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
                    std::cout << std::endl;
                    break;
                }
            }
            loop = true;
            break;
        
        case 'b':
            agregarResidentes(residentes, cont);
            cargarDatos(residentes, cont);
            break;

        case 'c':
            while (loop)
            {
                std::cout << "---------------------------------" << "\n";
                std::cout << "FAVOR DE SELECCIONAR UNA DE LAS SIGUIENTES OPCIONES: " << "\n";
                std::cout << "a) AGREGAR Mensualidad" << "\n";
                std::cout << "b) CAMBIAR MENSUALIDAD residente" << "\n";
                std::cout << "--> ";
                std::cin >> opcion;
                switch (opcion)
                {
                    case 'a':
                        loop = false;
                        agregarMensualidad(residentes, cont);
                        cargarDatos(residentes, cont);
                        break;
                    case 'b':
                        loop = false;
                        cambiarMensualidad(residentes, cont);
                        break;
                    default:

                        break;
                }
            }
            loop = true;
            break;
            
        
        case 's': //Salir del programa
            loop = false;
            break;
        
        default: //Cualquier otro valor marca que lo vuelvas a meter en la terminal
            std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
            std::cout << "FAVOR DE INGRESAR UN VÁLIDO" << std::endl;
            std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
            break;
        }
    }
    std::cout << " _____                                              _____                        _       " << std::endl;
    std::cout << "|  __ \\                                            / ____|                      | |      " << std::endl;
    std::cout << "| |__) | __ ___   __ _ _ __ __ _ _ __ ___   __ _  | |     ___ _ __ _ __ __ _  __| | ___  " << std::endl;
    std::cout << "|  ___/ '__/ _ \\ / _` | '__/ _` | '_ ` _ \\ / _` | | |    / _ \\ '__| '__/ _` |/ _` |/ _ \\ " << std::endl;
    std::cout << "| |   | | | (_) | (_| | | | (_| | | | | | | (_| | | |___|  __/ |  | | | (_| | (_| | (_) |" << std::endl;
    std::cout << "|_|   |_|  \\___/ \\__, |_|  \\__,_|_| |_| |_|\\__,_|  \\_____\\___|_|  |_|  \\__,_|\\__,_|\\___/ " << std::endl;
    std::cout << "                  __/ |                                                                  " << std::endl;
    std::cout << "                 |___/                                                                   " << std::endl;
    std::cout << std::endl;

    return 0;
}
