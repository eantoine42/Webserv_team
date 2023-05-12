#include "../../includes/server.hpp"

static int	createSocket(server &srv)
{
	int	socket_fd, enabled = 1;
	struct sockaddr_in sockaddr;
	struct protoent *proto;
	//The getprotobyname function is a part of the C library functions which is used to map a protocol name such as 
	// "tcp" to the corresponding protocol number defined in the netinet/in.h header file.
	if (!(proto = getprotobyname("tcp")))
		throw(SetServerException("Problem using protobyname, protocol not found"));
	if ((socket_fd = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		throw(SetServerException("Problem creating Socket"));
	DEBUG_COUT("Server " + srv.getName() + " created");
	// allows a socket to be bound to an address that is already in use, provided that the original socket using the address is no longer active. 
	//This behavior is useful in cases where the server needs to restart after a crash or when multiple instances of the server need to run on the same machine.
	//This option allows the socket to be bound to a previously used address and port, which is useful in cases where the socket is closed and then immediately reopened,
	// without waiting for the operating system to release the socket resources. Without this option,
	//the socket may fail to bind to the address and port, resulting in a "Address already in use" error.
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enabled, sizeof(enabled)) == -1)
		throw(SetServerException("Problem setting Socket options"));//
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(srv.getPort());
	sockaddr.sin_addr.s_addr = inet_addr(srv.getIp().c_str());
	if (bind(socket_fd, reinterpret_cast<struct sockaddr *>(&sockaddr), sizeof(sockaddr)) == -1)
		throw(SetServerException("Problem binding socket"));
	DEBUG_COUT("Server with file descriptor " <<  socket_fd << " has been successfully bind on port: " << srv.getPort());

	//if (fcntl(socket_fd, F_SETFL, O_NONBLOCK) == -1) //makes the socket nonblock
  //      throw(SetServerException("Problem setting the socket"));
	if (listen(socket_fd, MAX_CLIENT))
		throw(SetServerException("Problem with listen"));
	
	return socket_fd;
}

std::map<int, server *> createServerSockets(std::vector<server>& serverlist)
{
	std::map<int, server *> result; 
	std::vector<server>::iterator it;
	for (it = serverlist.begin();it != serverlist.end(); it++)
	{
		result[createSocket(*it)] = &(*it);
	}
	return (result);
}
