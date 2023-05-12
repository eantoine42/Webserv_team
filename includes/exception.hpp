#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP
#include "webserv.hpp"

/*
Conf File
*/

class WrongInputInServer : public std::exception
{
	public:
		char const	*what() const throw()
		{
			return "wrong input in server";
		}
};

class InvalidConfFilePath : public std::exception
{
	public:
		char const	*what() const throw()
		{
			return "Invalid Configuration File Path";
		}
};

class PathIsDir : public std::exception
{
	public:
		char const	*what() const throw()
		{
			return "Path is a directory, not a file";
		}
};
class EmptyConfPath: public std::exception
{
	public:
		char const	*what() const throw()
		{
			return "Configuration Path is empty";
		}
};

class CantOpenConfFile : public std::exception
{
	public:
		char const	*what() const throw()
		{
			return "Can't open the config file";
		}
};

class FileDoesNotExist : public std::exception
{
	public:
		char const	*what() const throw()
		{
			return "The file doesn't exist";
		}
};

class FileNotReadable : public std::exception
{
	public:
		char const	*what() const throw()
		{
			return "The file can't be read";
		}
};
class BadExtensionConfFile: public std::exception
{
	public:
		char const	*what() const throw()
		{
			return "Configuration File has a bad extension (needs to be .conf)";
		}
};

class InvalidConfFile : public std::exception
{
	public:
		char const	*what() const throw()
		{
			return "Invalid Configuration File";
		}
};

class ConfFileParseError : public std::exception
{
	private:
		std::string	_msg;

	public:
		ConfFileParseError(std::string msg)
		:	_msg(msg) {}

		~ConfFileParseError() throw() {};

		char const	*what() const throw()
		{
			std::cerr << "Configuration File Parse Error :" << std::endl;
			return _msg.c_str();
		}
};

class SetServerException : public std::exception
{
	private:
		std::string	_msg;

	public:
		SetServerException(std::string msg)
		:	_msg(msg) {}

		~SetServerException() throw() {};

		char const	*what() const throw()
		{
			std::cerr << "Setting Server Error :" << std::endl;
			return _msg.c_str();
		}
};

class RunServerException : public std::exception
{
	private:
		std::string	_msg;

	public:
		RunServerException(std::string msg)
		:	_msg(msg) {}

		~RunServerException() throw() {};

		char const	*what() const throw()
		{
			std::cerr << "Running Server Error :" << std::endl;
			return _msg.c_str();
		}
};

class epollFail : public std::exception
{
	private:
		std::string	_msg;

	public:
		epollFail(std::string msg)
		:	_msg(msg) {}

		~epollFail() throw() {};

		char const	*what() const throw()
		{
			std::cerr << "Epoll Error :" << std::endl;
			return _msg.c_str();
		}
};


#endif
