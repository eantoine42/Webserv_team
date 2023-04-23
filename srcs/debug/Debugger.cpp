#include "../../includes/c_debugger.hpp"

/* Variable statique globale declaree */
Debugger Debugger::_webserv_debugger;

Debugger::Debugger() : _is_active(false) {}

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

bool	Debugger::get_is_active() {
	return _is_active;
}

void	Debugger::start(bool activate) {
	_webserv_debugger._is_active = activate;
}

std::string	Debugger::get_date() {
	struct tm *date = NULL;
	char buff[64];
	struct timeval tv;

	gettimeofday(&tv, NULL);
	date = localtime(&(tv.tv_sec));
	strftime(buff, sizeof(buff), "%D %T", date);
	return (std::string(buff));
}

/* ************************************************************************** */
