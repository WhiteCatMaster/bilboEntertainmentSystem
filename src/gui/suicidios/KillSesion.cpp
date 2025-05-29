/* --- KillSesion.cpp --- */

/* ------------------------------------------
author: undefined
date: 27/5/2025
------------------------------------------ */

#include "KillSesion.h"

KillSesion::KillSesion(Usuario _usuario, string _tipoMuerte) : usuario(_usuario){
    
    tipoMuerte = _tipoMuerte;
    dia = 11;
    mes = 9;
    anyo = 2001;

}

KillSesion::~KillSesion() {
    // Destructor
}

int KillSesion::getDia() {
    return dia;
}
void KillSesion::setDia(int& value) {
    dia = value;
}
int KillSesion::getMes() {
    return mes;
}
void KillSesion::setMes(int& value) {
    mes = value;
}
int KillSesion::getAnyo() {
    return anyo;
}
void KillSesion::setAnyo(int& value) {
    anyo = value;
}
string KillSesion::getTipoMuerte() {
    return tipoMuerte;
}
void KillSesion::setTipoMuerte(string& value) {
    tipoMuerte = value;
}
