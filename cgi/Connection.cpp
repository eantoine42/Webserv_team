/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:08:27 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/10 22:16:51 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"

#include <unistd.h>

/* ************************************************************************** */
//						           PUBLIC									  //
/* ************************************************************************** */

// Canonical form
Connection::Connection(void)
{}

Connection::~Connection(void)
{
	close(this->_socketFd);
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

// Destructor


// Members methods


/* ************************************************************************** */
//						           PRIVATE									  //
/* ************************************************************************** */

//	Static attributes


// Static methods


// Constructor
