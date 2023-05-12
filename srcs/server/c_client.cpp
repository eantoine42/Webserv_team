#include "../../includes/c_client.hpp"

ClientInfo::ClientInfo(server  &server):_server(server), _request(""), _response("")
{
	
}

void	ClientInfo::add_request(std::string const &str)
{
	_request += str;
}


void	ClientInfo::set_response(std::string const &str)
{
	_response = str;
}

std::string const &ClientInfo::get_request() const
{
	return _request;
}

server  &ClientInfo::get_server() const
{
	return _server;
}


std::string const &ClientInfo::get_response() const
{
	return _response;
}
