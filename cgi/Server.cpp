/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:35:40 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/12 20:25:08 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include <cstdio>
#include <iostream>
#include <cerrno>
#include <sys/poll.h>
#include <vector>
#include <cstring>
#include <fstream>
#include <string>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <stdlib.h>

#include "Connection.hpp"
#include "MessageFactory.hpp"

/* ************************************************************************** */
//						           PUBLIC									  //
/* ************************************************************************** */

// Canonical form
Server::Server(void) 
{}

Server::Server(Server const & copy) : _listenerFd(copy._listenerFd), _fds(copy._fds)
{}

Server::~Server(void)
{
	close(this->_listenerFd);
}

Server &	Server::operator=(Server const & rhs)
{
	if (this != &rhs)
	{
		this->_listenerFd = rhs._listenerFd;
	}
	return *this;
}

// Members methods
int		Server::getListenerFd() const 
{
	return this->_listenerFd;
}

std::vector<pollfd> &		Server::getFds()
{
	return this->_fds;
}

std::map<int, Connection> &	Server::getConnections()
{
	return this->_connections;
}

void	Server::serverInit(short portNumber)
{
	struct sockaddr_in addr;

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(portNumber);

	if ((this->_listenerFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw ServerInitException(std::strerror(errno));

	if (bind(this->_listenerFd,(struct sockaddr *) &addr, sizeof(addr)) < 0)
		throw ServerInitException(std::strerror(errno));

	if (listen(this->_listenerFd, 10) < 0)
		throw ServerInitException(std::strerror(errno));

	pollfd serverFd = {this->_listenerFd, POLLIN, 0};
	this->_fds.push_back(serverFd);
	std::cout << "The server is ready to listening on port " << portNumber << std::endl;
}

// Members methods
void	Server::readRequest(pollfd & pollFd)
{
	if (pollFd.fd == this->_listenerFd)
	{
		int acceptFd = accept(pollFd.fd, NULL, NULL);
		if (acceptFd < 0)
			std::cerr << "Accept: " << std::strerror(errno) << std::endl;
		else
		{
			pollfd connectFd = {acceptFd, POLLIN, 0};
			this->_fds.push_back(connectFd);

			Connection co(acceptFd);
			this->_connections[acceptFd] = co;
		}
	}
	else
	{
		Connection & connection = this->_connections[pollFd.fd]; 
		// Read request data
		if (!connection.readRequest())
		{
			close(pollFd.fd);
			this->_connections[pollFd.fd].setOpen(false);
		}
		else
		{
			if (!connection.isRequestTerminated())
				return ;

			std::string & rawData = connection.getRequestRawData();
			// TODO: Create a method in Request
			Request * request = MessageFactory::createRequest(rawData);	
			connection.setRequest(*request);	
			delete request;
			pollFd.events = POLLOUT;
		}
	}
}

void	Server::writeResponse(pollfd & pollFd)
{
	std::string response = MessageFactory::createResponse();

	if (write(pollFd.fd, response.c_str(), response.length()) < 0)
	{
		close(pollFd.fd);
		this->_connections[pollFd.fd].setOpen(false);
		std::cerr << "Error writting" << std::endl;
	}
	// Verifier que la reponse soit complete
	pollFd.events = POLLRDHUP; 
}

/* ************************************************************************** */
//						           EXCEPTION								  //
/* ************************************************************************** */
Server::ServerInitException::ServerInitException(std::string const message)
	: _message(message)
{}

Server::ServerInitException::~ServerInitException() throw()
{}

const char *	Server::ServerInitException::what() const throw()
{
	return this->_message.c_str();
}

