/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:35:40 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/11 17:28:19 by lfrederi         ###   ########.fr       */
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

void	Server::listening()
{
	int				nFds;
	struct pollfd	*firstFd;

	while (true)
	{
		nFds = this->_fds.size();
		firstFd = &this->_fds.front();
		poll(firstFd, nFds, -1);

		/* std::cout << "Poll received events" << std::endl; */

		int i = 0;
		while (i < nFds)
		{
			/* std::cout << "Revents is equal to " << firstFd[i].revents << "on fd -> " << firstFd[i].fd << std::endl; */
			switch (firstFd[i].revents) 
			{
				case NO_EVENTS:
					/* std::cout << "Revents is empty in this fd " << firstFd[i].fd << std::endl; */
					break;
				case POLLIN:
					readRequest(firstFd[i].fd);
					firstFd = &this->_fds.front();
					if (firstFd[i].fd != this->_listenerFd)
						firstFd[i].events = POLLOUT;
					break;
				case POLLOUT:
					writeResponse(firstFd[i].fd);
					firstFd[i].events = POLLRDHUP;
					break;
				case POLLNVAL:
					std::cout << "POLLNVAL" << std::endl;
					this->_connections.erase((this->_fds.begin() + i)->fd);
					this->_fds.erase(this->_fds.begin() + i);
					nFds--;
					firstFd = &this->_fds.front();
					i--;
					break ;
				case POLLRDHUP:
					std::cout << "POLLRDHUP" << std::endl;
					close(firstFd[i].fd);
					this->_connections.erase((this->_fds.begin() + i)->fd);
					this->_fds.erase(this->_fds.begin() + i);
					nFds--;
					firstFd = &this->_fds.front();
					i--;
					break ;
				default:
					std::cout << "Default" << std::endl;
					/* close(firstFd[i].fd); */
					/* this->_fds.erase(this->_fds.begin() + i); */
					/* nFds--; */
					/* firstFd = &this->_fds.front(); */
					/* this->_connections.erase((this->_fds.begin() + i)->fd); */
					/* i--; */
					break ;
			}
			i++;
		}
	}
}

/* ************************************************************************** */
//						           PRIVATE									  //
/* ************************************************************************** */
// Members methods

void	Server::readRequest(int fd)
{
	if (fd == this->_listenerFd)
	{
		int acceptFd = accept(fd, NULL, NULL);
		if (acceptFd < 0)
			std::cerr << "Accept: " << std::strerror(errno) << std::endl;
		else
		{
			pollfd connectFd = {acceptFd, POLLIN, 0};
			this->_fds.push_back(connectFd);

			Connection co(acceptFd);
			this->_connections.insert(std::pair<int, Connection>(acceptFd, co));
		}
	}
	else
	{
		if (this->_connections.find(fd) == this->_connections.end()) {
			std::cout << "OUAAAAAAAAAAAAAAAAA --> " << fd << std::endl;
			exit(3);
		}
		// Read request data
		if (!this->_connections[fd].readRequest())
			close(fd);
		else
		{
			if (!this->_connections[fd].isRequestTerminated())
				return ;

			std::string & rawData = this->_connections[fd].getRequestRawData();
			// TODO: Check
			Request * request = MessageFactory::createRequest(rawData);	
			this->_connections[fd].setRequest(*request);	
			delete request;
		}
	}
}

void	Server::writeResponse(int fd)
{
	std::ifstream file("sample.json");
	if (!file.good())
		std::cerr << "Error while opening file" << std::endl;
	else
	{
		std::string result;
		const char * response = "HTTP/1.1 200 OK\r\nContent-type: application/json\r\nContent-length: ";

		result.append(response);

		file.seekg(0, file.end);
		int size = file.tellg();
		file.seekg(0, file.beg);

		char * buffer = new char [size + 1];
		file.read(buffer, size);
		buffer[file.gcount()] = '\0';

		char integer[20];
		std::sprintf(integer, "%d", size);
		result.append(integer);
		result.append("\r\n\r\n");
		result.append(buffer);

		if (write(fd, result.c_str(), result.length()) < 0)
			std::cerr << "Error writting" << std::endl;
		file.close();
		delete [] buffer;
	}
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

