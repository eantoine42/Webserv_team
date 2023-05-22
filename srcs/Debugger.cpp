#include "Debugger.hpp"

bool Debugger::_isActive = false;

Debugger::Debugger()
{}

Debugger::Debugger(Debugger const & src) {
	(void)src; 
}

Debugger::~Debugger() {}

Debugger &Debugger::operator=( Debugger const & rhs) {
	(void)rhs;
	return *this;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

bool	Debugger::getIsActive() {
	return Debugger::_isActive;
}

void	Debugger::start(bool activate) {
	Debugger::_isActive = activate;
}

std::string	Debugger::getDate() {
	struct tm *date = NULL;
	char buff[64];
	struct timeval tv;

	gettimeofday(&tv, NULL);
	date = localtime(&(tv.tv_sec));
	strftime(buff, sizeof(buff), "%D %T", date);
	return (std::string(buff));
}

std::string Debugger::getMessage(std::string message)
{
	return "[" + Debugger::getDate() + "]" + message;
}

/* ************************************************************************** */
