/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:35:40 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/09 23:00:47 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

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

/* ************************************************************************** */
//						           PUBLIC									  //
/* ************************************************************************** */

// Canonical form
Server::Server(void) : _listenerFd(-1) 
{}

Server::Server(Server const & copy) : _listenerFd(copy._listenerFd)
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

// Constructors

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

	std::cout << "The server is ready to listening on port " << portNumber << std::endl;
}

/* void	Server::listening() const */
/* { */
/* 	char buf[BUFFER_SIZE]; */
/* 	struct sockaddr_in	addrAccept; */
/* 	unsigned int		acceptFd; */
/* 	socklen_t			size; */
/* 	int					n; */
/*  */
/* 	size = sizeof(addrAccept); */
/* 	while (true) */
/* 	{ */
/* 		std::cout << "Waiting connection ..." << std::endl; */
/*  */
/* 		acceptFd = accept(this->_listenerFd, (struct sockaddr *) &addrAccept, &size); */
/* 		if (acceptFd > 0) */
/* 		{ */
/* 			// Read message from client */
/* 			if ((n = read(acceptFd, buf, BUFFER_SIZE - 1)) < 0) { */
/* 					std::cerr << "Error while reading" << std::endl; */
/* 					continue ; */
/* 			} */
/* 			buf[n] = '\0'; */
/* 			std::cout << buf << std::endl; */
/*  */
/* 			// Send message to client */
/* 			std::ifstream file("sample.json"); */
/* 			if (!file.good()) */
/* 			{ */
/* 				std::cerr << "Error while opening file" << std::endl; */
/* 			} */
/* 			else */
/* 			{ */
/* 				std::string result; */
/* 				const char * response = "HTTP/1.1 200 OK\r\nContent-type: application/json\r\nContent-length: "; */
/*  */
/* 				result.append(response); */
/* 				 */
/* 				file.seekg(0, file.end); */
/* 				int size = file.tellg(); */
/* 				file.seekg(0, file.beg); */
/* 				 */
/* 				char * buffer = new char [size + 1]; */
/* 				file.read(buffer, size); */
/* 				buffer[file.gcount()] = '\0'; */
/*  */
/* 				result.append(std::to_string(size)); */
/* 				result.append("\r\n\r\n"); */
/* 				result.append(buffer); */
/* 				 */
/* 				if (write(acceptFd, result.c_str(), result.length()) < 0) */
/* 					std::cerr << "Error writting" << std::endl; */
/* 				file.close(); */
/* 				delete [] buffer; */
/* 			} */
/* 			 */
/* 			close(acceptFd); */
/* 		} */
/* 	} */
/* } */

void	Server::listening() const
{
	std::vector<struct pollfd> fds;

	struct pollfd listen;
	listen.fd = this->_listenerFd;
	listen.events = POLLIN;
	
	fds.push_back(listen);
	struct pollfd *first = &fds.front();

	while (true)
	{
		int size = fds.size();
		poll(first, size, -1);
		/* std::cout << "test\n"; */

		for (int i = 0; i < size; i++)
		{
			std::cout << i << ": revents -> " << first[i].revents << std::endl;
			if (first[i].revents & POLLIN)
			{
				if (first[i].fd == this->_listenerFd)
				{
					int acceptfd = accept(this->_listenerFd, NULL, NULL);
					if (acceptfd > 0)
					{
						std::cout << "Accept ok" << std::endl;
						/* struct pollfd fd; */
						/* fd.fd = acceptfd; */
						/* fd.events = POLLIN; */
						fds.push_back(pollfd{acceptfd, POLLIN, 0});
						first = &fds.front();
					}
					else
						std::cerr << "Accept failed" << std::endl;
				}
				else
				{
					char buffer[BUFFER_SIZE];
					int	bytesRead;

					if ((bytesRead = read(first[i].fd, buffer, BUFFER_SIZE - 1)) <= 0)
					{
						std::cerr << "Reading failed" << std::endl;
						close(fds[i].fd);
						//fds.erase(fds.begin() + i);
						continue ;
					}
					buffer[bytesRead] = '\0';
					std::cout << buffer;

					/* first[i].events = POLLHUP; */
				}
			}
			else 
			{
				if (fds[i].fd != this->_listenerFd)
				{
					std::cout << "Err err\n";
					close(fds[i].fd);
					fds.erase(fds.begin() + i);
				//	exit(1);
				}
			}
			//std::cout << fds.size() << std::endl;
		}

		
	}

}

/* ************************************************************************** */
//						           PRIVATE									  //
/* ************************************************************************** */
Server::ServerInitException::ServerInitException(std::string const message)
	: _message(message)
{}

const char *	Server::ServerInitException::what() const throw()
{
	return this->_message.c_str();
}

/* ************************************************************************** */
//						           PRIVATE									  //
/* ************************************************************************** */

// Members methods


/* ************************************************************************** */
//						           FUNCTIONS								  //
/* ************************************************************************** */
