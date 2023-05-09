#include "../../includes/server.hpp"

static int	createSocket(server &info)
{
	int	socket_fd, enabled = 1;
	struct sockaddr_in sockaddr;
	struct protoent *proto;

	if (!(proto = getprotobyname("tcp")))
		throw(SetServerException("Problem using protobyname, protocol not found"));
	if ((socket_fd = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		throw(SetServerException("Problem creating Socket"));
	std::cerr << "Server " + info.getName() + " created" << "\n";
	// allows a socket to be bound to an address that is already in use, provided that the original socket using the address is no longer active. 
	//This behavior is useful in cases where the server needs to restart after a crash or when multiple instances of the server need to run on the same machine.
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enabled, sizeof(enabled)) == -1)
		throw(SetServerException("Problem setting Socket options"));//
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(info.getPort());
	sockaddr.sin_addr.s_addr = inet_addr(info.getIp().c_str());
	if (bind(socket_fd, reinterpret_cast<struct sockaddr *>(&sockaddr), sizeof(sockaddr)) == -1)
		throw(SetServerException("Problem binding socket"));

	if (fcntl(socket_fd, F_SETFL, O_NONBLOCK) == -1) //makes the socket nonblock
        throw(SetServerException("Problem setting the socket"));

	if (listen(socket_fd, MAX_CLIENT))
		throw(SetServerException("Problem with listen"));
	
	return socket_fd;
}

std::map<int, server *> createServerSockets(std::vector<server>& serverlist)
{
	std::map<int, server *> result; 
	for (unsigned i = 0 ; i < serverlist.size() ; ++i)
	{
		result[createSocket(serverlist[i])] = &serverlist[i];
	}
	return (result);
}
