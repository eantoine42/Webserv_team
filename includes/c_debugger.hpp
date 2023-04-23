#ifndef C_DEBUGGER_HPP
# define C_DEBUGGER_HPP

# include <iostream>
# include <string>
# include <ctime>
# include <sys/time.h>

# define DEBUG_START(ACTIVATE) Debugger::start(ACTIVATE)
# define DEBUG_STATUS (Debugger::_webserv_debugger.get_is_active() == true)
# define DEBUG_COUT(MESSAGE) if (Debugger::_webserv_debugger.get_is_active() == true) std::cerr << "[" << Debugger::get_date() << "] " << MESSAGE << std::endl

class Debugger
{

	public:

		Debugger();
		~Debugger();

		static void 		start(bool ACTIVATE);
		bool				get_is_active();
		static std::string	get_date();
		//garantit qu'il n'y aura qu'une seule instance de la classe
		static Debugger 	_webserv_debugger;

	private:
		Debugger( Debugger const & src );
		Debugger &		operator=( Debugger const & rhs );
		bool _is_active;
};

#endif
