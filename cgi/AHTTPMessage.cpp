/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AHTTPMessage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:07:08 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/10 23:28:51 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AHTTPMessage.hpp"

#include <iostream>
#include <cerrno>
#include <cstring>
#include <unistd.h>

/* ************************************************************************** */
//						           PUBLIC									  //
/* ************************************************************************** */

// Canonical form
AHTTPMessage::AHTTPMessage(void)
{}

AHTTPMessage::~AHTTPMessage(void)
{}

AHTTPMessage::AHTTPMessage(AHTTPMessage const & copy)
	:	_rawData(copy._rawData),
	_httpVersion(copy._httpVersion),
	_headers(copy._headers),
	_bodyMessage(copy._bodyMessage)
{}

AHTTPMessage & AHTTPMessage::operator=(AHTTPMessage const & rhs)
{
	if (this != &rhs)
	{
		this->_rawData = rhs._rawData;
		this->_httpVersion = rhs._httpVersion;
		this->_headers = rhs._headers;
		this->_bodyMessage = rhs._bodyMessage;
	}

	return (*this);
}

// Members methods
std::string &	AHTTPMessage::getRawData()
{
	return (this->_rawData);
}

bool	AHTTPMessage::readRawData(int socketFd)
{
	char buffer[BUFFER_SIZE];
	int	bytesRead;

	if ((bytesRead = read(socketFd, buffer, BUFFER_SIZE - 1)) <=0)
	{
		std::cerr << "Read: " << std::strerror(errno) << std::endl;
		return false;
	}
	buffer[bytesRead] = '\0';
	std::cout << buffer;
	return true;
}

/* ************************************************************************** */
//						           PRIVATE									  //
/* ************************************************************************** */

//	Static attributes


// Static methods


// Constructor
