/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:08:27 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/11 15:03:59 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"

#include <cerrno>
#include <iostream>
#include <cstring>
#include <unistd.h>

/* ************************************************************************** */
//						           PUBLIC									  //
/* ************************************************************************** */

// Canonical form
Connection::Connection(void)
{}

Connection::~Connection(void)
{
	/* close(this->_socketFd); */
}

Connection::Connection(Connection const & copy)
	:	_socketFd(copy._socketFd),
		_request(copy._request),
		_response(copy._response)
{}

Connection & Connection::operator=(Connection const & rhs)
{
	if (this != &rhs)
	{
		this->_socketFd = rhs._socketFd;
		this->_request = rhs._request;
		this->_response = rhs._response;
	}

	return (*this);
}

// Constructors
Connection::Connection(int socketFd) 
	:	_socketFd(socketFd)
{}

// Members methods
bool	Connection::readRequest()
{
	char buffer[BUFFER_SIZE];
	int	bytesRead;

	if ((bytesRead = read(this->_socketFd, buffer, BUFFER_SIZE - 1)) <= 0)
	{
		std::cerr << "Error on fd -> " << this->_socketFd << std::endl;
		std::cerr << "Read: " << std::strerror(errno) << std::endl;
		return false;
	}
	buffer[bytesRead] = '\0';
	/* std::cout << buffer; */
	return true;
}

bool	Connection::isRequestTerminated()
{
	return true;
}

// Accessor
void	Connection::setSocketFd(int socketFd)
{
	this->_socketFd = socketFd;
}

Request &	Connection::getRequest()
{
	return this->_request;
}

void	Connection::setRequest(Request & request)
{
	this->_request = request;
}

std::string &	Connection::getRequestRawData()
{
	return this->_requestRawData;
}

int		Connection::getSocketFd()
{
	return this->_socketFd;
}
/* ************************************************************************** */
//						           PRIVATE									  //
/* ************************************************************************** */

//	Static attributes


// Static methods


// Constructor
