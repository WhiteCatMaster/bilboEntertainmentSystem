#include <iostream>

using namespace std;

void mostrarMenu() {
    cout << "==================================" << endl;
    cout << "  Bienvenido al menu de admin     " << endl;
    cout << "==================================" << endl;
    cout << "Seleccione una opcion:" << endl;
    cout << "1 - Borrar base de datos de Libros" << endl;
    cout << "2 - Borrar base de datos de Tarjetas" << endl;
    cout << "3 - Borrar base de datos de Inventario" << endl;
    cout << "4 - Borrar base de datos de Pelicula" << endl;
    cout << "5 - Borrar base de datos de Critica" << endl;
    cout << "S - Salir" << endl;
    cout << "==================================" << endl;
    cout << "Ingrese su opcion: ";
}

int main() {
    char opcion; 

    while (true) {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case '1':
                //void borrarbdLibro();
                //Comunicarse con la funcion que esta en cineDB.c, si se borra correctamente devuelve un 0, si llega un 0
                //poner algun mensaje de tarjeta borrada correctamente.
                break;
            case '2':
                //borrarbdTarjeta();
                break;
            case '3':
                //borrarbdInventario();
                break;
            case '4':
                //borrarbdPelicula();
                break;
            case '5':
                //borrarbdCritica();
                break;
            case 'S':
            case 's':
                cout << "Saliendo del programa" << endl;
                return 0;
            default:
                cout << "\nOpcion invalida. Intente de nuevo.\n" << endl;
                break;
        }
    }
}
