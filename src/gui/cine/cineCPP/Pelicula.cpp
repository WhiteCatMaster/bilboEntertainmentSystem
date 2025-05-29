#include "Pelicula.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Pelicula::Pelicula()
{
}

Pelicula::Pelicula( const Pelicula & src )
{
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Pelicula::~Pelicula()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Pelicula &				Pelicula::operator=( Pelicula const & rhs )
{
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Pelicula const & i )
{
	//o << "Value = " << i.getValue();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/


/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */