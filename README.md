BES (Bilbao Entertainment System) es un sistema de centros de ocio en Bilbao, entre los que se incluyen: Cine y Librería (programados en C) y máquina de suicidios (programada en C + +). 

Este programa está creado para ser usado en Linux, los usuarios de Windows tendrán que descargar WLS con el comando:
wsl --install

Y más adelante habrá que descargar el gcc y diferentes paquetes de python para asegurarse de que todas las funciones trabajan de forma óptima (no hay entorno virtual):

sudo apt install gcc

pip install requests

pip install beautifulsoup4

Para ejecutar el programa será necesario ejecutar dos scripts a la vez, los cuales están conectados por sockets. Se puede obtener nuestro programa copiando el GitHub:
https://github.com/WhiteCatMaster/bilboEntertainmentSystem
Con el comando: git clone https://github.com/WhiteCatMaster/bilboEntertainmentSystem.git

Posteriormente se deberá depositar en el proyecto y ejecutar este comando:

./mainMenu → para la parte de C++
./mainMenuC → para la parte de C

El programa tiene dos menús, uno para la parte de C y otro para la parte de C + +. 

Cuando se abre el menú de C, aparecerán las opciones de ir a la librería, al cine y a los sockets. Las primeras dos opciones son bastante autodescriptivas y llevarán al usuario a la parte que haya seleccionado. En el caso del cine hay 2 opciones: comprar entradas y añadir críticas. Para comprar entradas hay que elegir el número de estas y la posición de las butacas. La opción de ver críticas permite ver las críticas por cada película. En cuanto a la librería, permite comprar o alquilar libros y consultar el inventario de los libros (con la posibilidad de devolver los alquilados).

De la opción de Sockets hablaremos más adelante.

Cuando se abre el menú de C + +, aparecerán las opciones de la cabina de suicidios y la gestión del admin. La cabina de suicidios (puesta en el proyecto como referencia a Futurama, a modo de humor) permite a un usuario escribir sus datos y la forma en la que quiere morir.

La opción del admin (Sockets) de aquí se conecta con la del menú hecho en C. Para acceder se pedirá una contraseña (“root”) para poder acceder. Una vez dentro, estarán las opciones de borrar las bases de datos de todas las partes del proyecto. Antes de seleccionar una opción, se deberá entrar a en la opción de Sockets de la parte de C y que salga el mensaje de “Escuchando en el puerto”. Cuando eso esté hecho, se podrá seleccionar que BD se desea borrar. Para salir de la opción de Sockets en el menú de C habrá que hacer ctrl + c. El admin también tiene funcionalidades sin Socket, ver lista de suicidios y eliminar la BD de la máquina de suicidios.

Compilación del menú de C:
gcc src/main/mainMenu.c src/gui/libreria/libreriaMain/mainlibreria.c src/gui/libreria/libreriaMain/libreria.c src/BBDD/cineDB.c src/BBDD/sqlite3.c  src/gui/cine/cineMain/main.c src/gui/cine/cineMain/leerTextoGigante.c src/gui/cine/cineMain/funcionesCine.c src/gui/cine/cineMain/funcionesCriticas.c src/gui/cine/webscrap/webscrapMain.c src/gui/sockets/server.c -o mainMenuC

Compilación del menú de C++:
 g++ src/main/mainMenu.cpp  src/gui/suicidios/main.cpp src/gui/suicidios/KillSesion.cpp src/gui/suicidios/Usuario.cpp src/gui/sockets/client.c src/BBDD/suicidiosBD.cpp src/BBDD/sqlite3.o src/main/Admin.cpp -o mainMenu
