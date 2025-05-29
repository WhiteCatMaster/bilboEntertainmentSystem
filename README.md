Para ejecutar el programa será necesario ejecutar dos scripts a la vez, los cuales están conectados por sockets. Se puede obtener nuestro programa copiando el GitHub
Con el comando: git clone https://github.com/WhiteCatMaster/bilboEntertainmentSystem.git

Luego depositarse en el proyecto y ejecutar 
para linux
./mainMenu // para la parte de c++
./mainMenuC // para la parte de c
para windows
./mainMenuWindows.exe 
./mainMenuCWindows.exe

compilación menu en C:
gcc src/main/mainMenu.c src/gui/libreria/libreriaMain/mainlibreria.c src/gui/libreria/libreriaMain/libreria.c src/BBDD/cineDB.c src/BBDD/sqlite3.c  src/gui/cine/cineMain/main.c src/gui/cine/cineMain/leerTextoGigante.c src/gui/cine/cineMain/funcionesCine.c src/gui/cine/cineMain/funcionesCriticas.c src/gui/cine/webscrap/webscrapMain.c -o mainMenuC
