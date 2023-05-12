/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:08:27 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/12 20:20:11 by lfrederi         ###   ########.fr       */
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
		_open(copy._open),
		_requestRawData(copy._requestRawData),
		_request(copy._request),
		_response(copy._response)
{}

Connection & Connection::operator=(Connection const & rhs)
{
	if (this != &rhs)
	{
		this->_socketFd = rhs._socketFd;
		this->_open = rhs._open;
		this->_requestRawData = rhs._requestRawData;
		this->_request = rhs._request;
		this->_response = rhs._response;
	}

	return (*this);
}

// Constructors
Connection::Connection(int socketFd) 
	:	_socketFd(socketFd),
		_open(true)
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
	// Ajouter le buffer dans rawRequest et verifier si la requete est terminee ou pas
	
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

bool	Connection::getOpen()
{
	return this->_open;
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

void	Connection::setOpen(bool close)
{
	this->_open = close;
}
/* ************************************************************************** */
//						           PRIVATE									  //
/* ************************************************************************** */

//	Static attributes


// Static methods


// Constructor
