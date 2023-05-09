#include "Cgi.hpp"
#include <iostream>
#include <unistd.h>

/* ************************************************************************** */
//						           PUBLIC									  //
/* ************************************************************************** */

// Canonical form
Cgi::Cgi(void) : _cgiBin(""), _extension("")
{
	std::cout << "Cgi default constructor called" << std::endl;
}

Cgi::~Cgi(void)
{
	std::cout << "Cgi destructor called" << std::endl;
}

Cgi::Cgi(Cgi const & copy) : _cgiBin(copy._cgiBin), _extension(copy._extension)
{
	std::cout << "Cgi copy constructor called" << std::endl;
}

Cgi & Cgi::operator=(Cgi const & rhs)
{
	std::cout << "Cgi copy assignment called" << std::endl;
	if (this == &rhs) {
	}
		
	return (*this);
}

// Constructors
Cgi::Cgi(const std::string pathBin, const std::string extension) 
	: _cgiBin(pathBin), _extension(extension)
{

}

// Members methods
void	Cgi::execScript(const std::string filename)
{
	execve(const char *__path, char *const *__argv, char *const *__envp);
}


/* ************************************************************************** */
//						           PRIVATE									  //
/* ************************************************************************** */

//	Static attributes


// Static methods


// Constructor
