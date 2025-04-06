#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../BBDD/cineDB.h"
#include "libreria.h"
#include <time.h>
#define CINE_DB_H
#define MAX_LINE 1000

int mostrarLibrosDisponibles() {
    while (getchar() != '\n');
    int opcion;
    int resultado;

    printf("-----------------------------\n");
    printf("LIBROS DISPONIBLES:\n");
    Libro *libros;
    int cuantosLibros = 0;

    int comprobacion = 0;
    //Contar cuantos libros hay en la BD, para poder hacer el for
    comprobacion = count_libros();

    //Se comprueba si la BD no tiene ningun libro cargado, en cuyo caso se cargan del CSV
    if(comprobacion == 0) {
        //printf("BD VACIA\n");
        borrarbdLibro();
        leer_csv("src\\gui\\libreria\\libreriaMain\\LibrosBien.csv");
    } else {
        //printf("BD LLENA");
    }

    //Se cargan en el array "libros" todos los libros cargados de la BD
    libros = show_libro();
    cuantosLibros = count_libros();

    //Y se van imprimiendo por pantalla uno a uno
    for(int i=0;i<cuantosLibros;i++) {
        printf("%d. %s\n", i+1, libros[i].nombre);
    }
    printf("-----------------------------\n");
    printf("Selecciona un libro:\n");

    scanf(" %d", &opcion);

    // Validación de la opción seleccionada
    while (opcion < 0 || opcion > cuantosLibros) {
        printf("Por favor, selecciona un libro valido...\n");
        for(int i=0;i<cuantosLibros;i++) {
            printf("%d. %s\n", i+1, libros[i].nombre);
        }
        printf("-----------------------------\n");
        printf("Selecciona un libro:\n");
        scanf(" %d", &opcion);
    }  

    // Llamada a la función si la opción es válida
    resultado = unLibro(libros, opcion - 1);


    free(libros);
    //Se devuelve el numero (en la lista) del libro que se quiere comprar
    return resultado;
}

int unLibro(Libro *libros, int num) {
    char opcion2;
    int devolver = 0;

    //Se muestra la ficha tecnica del libro
    printf("-----------------------------\n"); 
    printf("Ficha del libro:\n");
    printf("Nombre: %s\n", libros[num].nombre);
    printf("Genero: %s\n", libros[num].genero);
    printf("Descripcion: %s\n", libros[num].descripcion);
    printf("Precio compra: %f\n", libros[num].precioCo);
    printf("Precio alquilado: %f\n", libros[num].precioAl);
    printf("-----------------------------\n");
    printf("P [Pagar]\n");
    printf("V [Apagar]\n");
    while (getchar() != '\n');
    scanf("%c", &opcion2);

    //Se le lleva a la ventana anterior
    if(opcion2 == 'V') {
        exit(0);
    //Se devuelve el numero (en la lista) del libro que se quiere comprar
    } else if(opcion2 == 'P') {
        devolver = num;
    } else {
        exit(0);
    }

    return devolver;
}

Libro pagarTarjetas(int numlibro, int numtarjetas) {
    while (getchar() != '\n');

    //Cargar la fecha de hoy para poder hacer mas calculos de cual es el limite para devolver el libro
    time_t t;
    struct tm *tm_info;
    time(&t);
    tm_info = localtime(&t);
    int dia = tm_info->tm_mday;
    int mes = tm_info->tm_mon + 1;  //Mes que va del 0 al 11
    int ano = tm_info->tm_year + 1900; 

    int proxdia;
    int proxmes;
    int proxano;

    Libro *libros;
    int cuantosLibros = 0;

    Tarjeta *tarjetas;

    //Cargar los arrays con todos los libros y tarjetas
    libros = show_libro();
    tarjetas = show_tarjeta();

    Libro libroSeleccionado;
    Libro *libropuntero;
    libropuntero = &libroSeleccionado;

    //Se carga el valor del libro que ha sido elegido antes
    libroSeleccionado = libros[numlibro];

    int seleccion;
    int seleccionado;
    char seleccion2;

    printf("-----------------------------\n"); 
    printf("Tarjetas disponibles:\n");
    
    //Mostrar todas las tarjetas disponibles
    for(int i = 0; i < numtarjetas; i++) {
        printf("%d. Numero:%s CVV:%d Saldo:%f\n",i + 1, tarjetas[i].numero, tarjetas[i].CVV, tarjetas[i].saldo);
    }
    printf("-----------------------------\n");
    printf("Selecciona una tarjeta:\n");
    scanf("%d", &seleccion);
    seleccionado = seleccion;

    //Comprobar si la tarjeta es valida
    if(seleccion < 0) {
        printf("Por favor, selecciona una tarjeta valida...\n");
        pagarTarjetas(numlibro, numtarjetas);
    } else if (seleccion > numtarjetas) {
        printf("Por favor, selecciona una tarjeta valida...\n");
        pagarTarjetas(numlibro, numtarjetas);
    } else {
        //Comprobar si se quiere comprar o alquilar el libro para elegir el precio adecuado
        while (getchar() != '\n');
        printf("-----------------------------\n");
        printf("Comprar [C] o Alquilar [A]?\n");
        scanf("%c", &seleccion2);

        if(seleccion2 == 'C') {
            //Comprobar si se tiene el saldo suficiente
            if(tarjetas[seleccionado-1].saldo > libroSeleccionado.precioCo) {
                printf("Compra finalizada; el libro se ha anadido al inventario\n");
                //Eliminar el libro de la BD
                delete_libro(libropuntero);
                //Calcular el nuevo saldo que tendra la tarjeta
                float nuevoSaldo = tarjetas[seleccionado-1].saldo - libroSeleccionado.precioCo;
                //Y meterlo en la BD
                update_saldo(tarjetas[seleccionado-1], nuevoSaldo);
                //Añadir el libro al inventario
                insert_inventario(&libroSeleccionado, 01, 0, 2999);
            } else {
                printf("No tienes suficiente saldo para comprar el libro.\n");
            }
        } else if(seleccion2 == 'A') {
            //Lo mismo que al comprarlo
            if(tarjetas[seleccionado-1].saldo > libroSeleccionado.precioAl) {
                printf("Compra finalizada; el libro se ha anadido al inventario\n");
                delete_libro(libropuntero);
                float nuevoSaldo = tarjetas[seleccionado-1].saldo - libroSeleccionado.precioAl;
                update_saldo(tarjetas[seleccionado-1], nuevoSaldo);

                //Calculando dinamicamente la fecha a la que se tendra que devolver el libro
                //Teniendo en cuenta el dia del mes en el que el usuario se encuentre
                if(dia < 19) {
                    proxdia = dia + 10;
                    proxmes = mes;
                    proxano = ano;
                } else {
                    proxdia = 30 - dia;
                    if (mes == 11) {
                        proxmes = 0;
                        proxano = ano + 1;
                    } else {
                        proxmes = mes + 1;
                        proxano = ano;
                    } 
                }

                insert_inventario(&libroSeleccionado, proxdia, proxmes, proxano);

            } else {
                printf("No tienes suficiente saldo para comprar el libro.\n");
            }

        } else {
            pagarTarjetas(numlibro, numtarjetas);
        }
    }
    free(tarjetas);
    free(libros);
    return libroSeleccionado;
    exit(0);
}

void cargarTarjetas(Tarjeta **tarjetas, int cuantasTarjetas) {
    //Guarda las tarjetas en la BD (solo se llama si no hay ninguna)
    while (getchar() != '\n');

    for(int i=0;i<cuantasTarjetas;i++) {
        insert_tarjeta(*tarjetas[i]);
    }
}

void mostrarInventario() {
    time_t t;
    struct tm *tm_info;
    time(&t);
    tm_info = localtime(&t);
    int dia = tm_info->tm_mday;
    int mes = tm_info->tm_mon + 1;  //Mes que va del 0 al 11
    int ano = tm_info->tm_year + 1900;

    Tarjeta *tarjetas;
    tarjetas = show_tarjeta();

    //Mostrar los libros que hay en el inventario
    char opcion;
    int opcion2;

    printf("-----------------------------\n");
    printf("Libros en el inventario:\n");

    int cuantos;
    cuantos = count_inventario();

    if(cuantos == 0) {
        printf("No hay libros en el inventario\n");
    } else {

        int cuantosinv;
        cuantosinv = count_inventario();
        Libro *librosinv;
        librosinv = show_inventario();

        
        for(int i=0;i<cuantosinv;i++) {
            //Las fechas se guardan separando dia, mes y año. Para mostrar un dia, hay que usar...
            //la funcion "getdiaInventarioPorNombre", a la que hay que pasarle el nombre del libro y esta calculara su dia de devolucion.
            //Los libros comprados tienen todos la fecha de entrega en el 2999
            if(getanoInventarioPorNombre(librosinv[i].nombre) == 2999) {
                printf("%d. %s (Comprado)\n",i+1, librosinv[i].nombre);
            //Los libros alquilados
            } else {
                if(getdiaInventarioPorNombre(librosinv[i].nombre) == dia && getmesInventarioPorNombre(librosinv[i].nombre) == mes && getanoInventarioPorNombre(librosinv[i].nombre) == ano) {
                    delete_libroInventario(&librosinv[i]);
                    insert_libro(&librosinv[i]);
                    update_saldo(tarjetas[0], tarjetas[0].saldo - 100);
                } else {
                    printf("%d. %s (%d-%d-%d)\n",i+1, librosinv[i].nombre, getdiaInventarioPorNombre(librosinv[i].nombre), getmesInventarioPorNombre(librosinv[i].nombre), getanoInventarioPorNombre(librosinv[i].nombre));
                }
            }

        }
        printf("-----------------------------\n");
        printf("D [Devolver]\n");
        printf("V [Apagar]\n");
        scanf(" %c", &opcion);
        if(opcion == 'D') {
            printf("Selecciona un libro que devolver:\n");
            scanf(" %d", &opcion2);
            //Si se va a devolver se comprueba si el libro que se quiere devolver esta comprado o alquilado
            if(getanoInventarioPorNombre(librosinv[opcion2-1].nombre) == 2999) {
                printf("Selecciona un libro alquilado!\n");
                mostrarInventario();
            } else {
                //Se elimina de la BD de inventario y se vuelve a guardar en la de los libros
                printf("Devolucion completada!\n");
                delete_libroInventario(&librosinv[opcion2-1]);
                insert_libro(&librosinv[opcion2-1]);
            }
        } else if(opcion == 'V') {
            printf("-----------------------------\n");
            exit(0);
        }

        free(librosinv);
    }

    exit(0);
}

void pantallamain() {
    //Lo mismo que hace el main, para cuando se necesite volver a esta pantalla
    char opcion;
    int numeroLibro;
    while (getchar() != '\n');

    printf("BIENVENIDO A LA LIBRERIA!!\n");
    printf("-----------------------------\n");
    printf("I [Inventario]\n");
    printf("L [Libros]\n");
    printf("F [Vaciar BD]\n");

    scanf("%c", &opcion);
        if(opcion == 'L') {
            numeroLibro = mostrarLibrosDisponibles();
        } else if (opcion == 'F') {
            borrarbdLibro();
            borrarbdTarjeta();
        } else if (opcion == 'I') {
            mostrarInventario();
        }
    
    pagarTarjetas(numeroLibro, 3);
}


void leer_csv(const char *filename) {
    //Para leer el csv con los datos de los libros
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error al abrir el archivo");
        return;
    }

    char line[MAX_LINE];

    while (fgets(line, sizeof(line), file)) {
        char *nombre, *descripcion, *genero;
        float precioCo, precioAl;

        // Usar ";" como delimitador
        nombre = strtok(line, ";");
        descripcion = strtok(NULL, ";");
        precioCo = atof(strtok(NULL, ";"));
        precioAl = atof(strtok(NULL, ";"));
        genero = strtok(NULL, ";\n");
       
        Libro lib;
        lib.nombre =nombre;
        lib.descripcion= descripcion;
        lib.precioCo = precioCo;
        lib.precioAl = precioAl; 
        lib.genero= genero;

        insert_libro(&lib); // Insertar el libro en la base de datos

    }

    fclose(file);
}

