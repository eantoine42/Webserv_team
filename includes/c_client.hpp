#ifndef C_CLIENT_HPP
# define C_CLIENT_HPP
#include "webserv.hpp"

class ClientInfo
{
	private:
		server				&_server;
		std::string			_request;
		std::string			_response;
		std::string			_method;
		size_t				_id;

	public:
		ClientInfo(server &server);

		void	add_request(std::string const &str);
		void	set_method(std::string const &);
		void	set_response(std::string const &str);

		std::string const &get_request() const;
		server  &get_server() const;
		std::string const &get_response() const;
};

#endif