#include "Usuario.h"
#include "KillSesion.h"
#include "../../BBDD/suicidiosBD.h"
#include <algorithm> 
#include <cctype>    
#include <sstream>  
#include <limits>
#include <ctime>

Usuario logIn();
KillSesion menuSeleccionTipoMuerte(Usuario);
void imprimirRecibo(KillSesion, Usuario);
int mainSuicidios();