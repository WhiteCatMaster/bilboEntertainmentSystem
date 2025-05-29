/* --- KillSesion.h --- */

/* ------------------------------------------
Author: undefined
Date: 27/5/2025
------------------------------------------ */

#ifndef KILLSESION_H
#define KILLSESION_H
#include "Usuario.h"

class KillSesion{
public:
    KillSesion(Usuario,  string);
    ~KillSesion();

    int getDia();
    void setDia(int& value);
    int getMes();
    void setMes(int& value);
    int getAnyo();
    void setAnyo(int& value);
    string getTipoMuerte();
    void setTipoMuerte(string& value);

private:
    Usuario usuario;
    int dia;
    int mes;
    int anyo;
    string tipoMuerte;

};

#endif // KILLSESION_H
