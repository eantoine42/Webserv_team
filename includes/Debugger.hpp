#ifndef DEBUGGER_HPP
# define DEBUGGER_HPP

# include <iostream>
# include <string>
# include <ctime>
# include <sys/time.h>

# define DEBUG_START(ACTIVATE) Debugger::start(ACTIVATE)
# define DEBUG_STATUS (Debugger::getIsActive() == true)
# define DEBUG_COUT(MESSAGE) if (Debugger::getIsActive() == true) std::cerr << "[" << Debugger::getDate() << "] " << MESSAGE << std::endl

class Debugger
{
	public:

		static void 		start(bool ACTIVATE);
		static bool			getIsActive();
		static std::string	getDate();
		static std::string	getMessage(std::string);

	private:

		Debugger();
		~Debugger();
		Debugger( Debugger const & src );
		Debugger &		operator=( Debugger const & rhs );

		static bool _isActive;
};


#endif
