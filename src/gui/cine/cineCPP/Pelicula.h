#ifndef PELICULA_HPP
# define PELICULA_HPP

# include <iostream>
# include <string>
# include <stdlib.h>
using namespace std;

class Pelicula
{

	public:

		Pelicula();
		Pelicula( Pelicula const & src );
		~Pelicula();

		Pelicula &		operator=( Pelicula const & rhs );

	private:
		String titulo;


};

std::ostream &			operator<<( std::ostream & o, Pelicula const & i );

#endif /* ******************************************************** PELICULA_H */