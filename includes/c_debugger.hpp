#ifndef C_DEBUGGER_HPP
# define C_DEBUGGER_HPP

# include <iostream>
# include <string>
# include <ctime>
# include <sys/time.h>

# define DEBUG_START(ACTIVATE) Debugger::start(ACTIVATE)
# define DEBUG_STATUS (Debugger::_webserv_debugger.getIsActive() == true)
# define DEBUG_COUT(MESSAGE) if (Debugger::_webserv_debugger.getIsActive() == true) std::cerr << "[" << Debugger::getDate() << "] " << MESSAGE << std::endl

class Debugger
{

	public:

		Debugger();
		~Debugger();

		static void 		start(bool ACTIVATE);
		bool				getIsActive();
		static std::string	getDate();
		//garantit qu'il n'y aura qu'une seule instance de la classe
		static Debugger 	_webserv_debugger;

	private:
		Debugger( Debugger const & src );
		Debugger &		operator=( Debugger const & rhs );
		bool _is_active;
};


#endif
