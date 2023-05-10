/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:35:40 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/10 16:54:09 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

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

	this->_fds.push_back(pollfd{this->_listenerFd, POLLIN, 0});
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

		std::cout << "Poll received events" << std::endl;

		int i = 0;
		while (i < nFds)
		{
			std::cout << "Revents is equal to " << firstFd[i].revents << std::endl;
			switch (firstFd[i].revents) 
			{
				case NO_EVENTS:
					std::cout << "Revents is empty in this fd " << firstFd[i].fd << std::endl;
					break;
				case POLLIN:
					readRequest(firstFd[i]);
					firstFd = &this->_fds.front();
					break;
				case POLLOUT:
					writeResponse(firstFd[i]);
					break;
				case POLLNVAL:
					std::cout << "POLLNVAL" << std::endl;
					this->_fds.erase(this->_fds.begin() + i);
					nFds--;
					firstFd = &this->_fds.front();
					continue;
				default:
					std::cout << "Default" << std::endl;
					close(firstFd[i].fd);
					this->_fds.erase(this->_fds.begin() + i);
					nFds--;
					firstFd = &this->_fds.front();
					continue;
			}
			i++;
		}
	}
}

/* ************************************************************************** */
//						           EXCEPTION								  //
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

void	Server::readRequest(pollfd & fd)
{
	if (fd.fd == this->_listenerFd)
	{
		int acceptFd = accept(fd.fd, NULL, NULL);
		if (acceptFd < 0)
			std::cerr << "Accept: " << std::strerror(errno) << std::endl;
		else
			this->_fds.push_back(pollfd{acceptFd, POLLIN, 0});
	}
	else
	{
		char buffer[BUFFER_SIZE];
		int	bytesRead;

		if ((bytesRead = read(fd.fd, buffer, BUFFER_SIZE - 1)) <=0)
		{
			std::cerr << "Read: " << std::strerror(errno) << std::endl;
			close(fd.fd);
		}
		buffer[bytesRead] = '\0';
		std::cout << buffer;

		fd.events = POLLOUT;
	}
}

void	Server::writeResponse(pollfd & fd)
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

		result.append(std::to_string(size));
		result.append("\r\n\r\n");
		result.append(buffer);

		if (write(fd.fd, result.c_str(), result.length()) < 0)
			std::cerr << "Error writting" << std::endl;
		file.close();
		delete [] buffer;
		close(fd.fd);
	}
}

void	Server::handleError(pollfd & fd, int position)
{
	std::cout << "Err err\n";
	close(fd.fd);
	this->_fds.erase(this->_fds.begin() + position);
}

	/* ************************************************************************** */
	//						           FUNCTIONS								  //
	/* ************************************************************************** */

	/* { */
	/* 	std::cout << i << ": revents -> " << first[i].revents << " fd -> " << first[i].fd << std::endl; */
	/* 	if (first[i].revents == 0) */
	/* 		continue; */
	/*  */
	/* 	if (first[i].revents & POLLIN) */
	/* 	{ */
	/* 		if (first[i].fd == this->_listenerFd) */
	/* 		{ */
	/* 			int acceptfd = accept(this->_listenerFd, NULL, NULL); */
	/* 			if (acceptfd > 0) */
	/* 			{ */
	/* 				std::cout << "Accept ok" << std::endl; */
	/* 				fds.push_back(pollfd{acceptfd, POLLIN, 0}); */
	/* 				first = &fds.front(); */
	/* 			} */
	/* 			else */
	/* 				std::cerr << "Accept failed" << std::endl; */
	/* 		} */
	/* 		else */
	/* 		{ */
	/* 			char buffer[BUFFER_SIZE]; */
	/* 			int	bytesRead; */
	/*  */
	/* 			if ((bytesRead = read(first[i].fd, buffer, BUFFER_SIZE - 1)) <= 0) */
	/* 			{ */
	/* 				std::cerr << "Reading failed" << std::endl; */
	/* 				close(fds[i].fd); */
	/* 				//fds.erase(fds.begin() + i); */
	/* 				continue ; */
	/* 			} */
	/* 			buffer[bytesRead] = '\0'; */
	/* 			std::cout << buffer; */
	/*  */
	/* 			first[i].events = POLLOUT; */
	/* 		} */
	/* 	} */
	/* 	else if (fds[i].revents & POLLOUT) */
	/* 	{ */
	/*  */
	/* 		std::ifstream file("sample.json"); */
	/* 		if (!file.good()) */
	/* 			std::cerr << "Error while opening file" << std::endl; */
	/* 		else */
	/* 		{ */
	/* 			std::string result; */
	/* 			const char * response = "HTTP/1.1 200 OK\r\nContent-type: application/json\r\nContent-length: "; */
	/*  */
	/* 			result.append(response); */
	/*  */
	/* 			file.seekg(0, file.end); */
	/* 			int size = file.tellg(); */
	/* 			file.seekg(0, file.beg); */
	/*  */
	/* 			char * buffer = new char [size + 1]; */
	/* 			file.read(buffer, size); */
	/* 			buffer[file.gcount()] = '\0'; */
	/*  */
	/* 			result.append(std::to_string(size)); */
	/* 			result.append("\r\n\r\n"); */
	/* 			result.append(buffer); */
	/*  */
	/* 			if (write(fds[i].fd, result.c_str(), result.length()) < 0) */
	/* 				std::cerr << "Error writting" << std::endl; */
	/* 			file.close(); */
	/* 			delete [] buffer; */
	/* 			close(fds[i].fd); */
	/* 		} */
	/* 	} */
	/* 	else  */
	/* 	{ */
	/* 		if (fds[i].fd != this->_listenerFd) */
	/* 		{ */
	/* 			std::cout << "Err err\n"; */
	/* 			close(fds[i].fd); */
	/* 			fds.erase(fds.begin() + i); */
	/* 			//	exit(1); */
	/* 		} */
	/* 	} */
	/* 	//std::cout << fds.size() << std::endl; */
	/* } */
