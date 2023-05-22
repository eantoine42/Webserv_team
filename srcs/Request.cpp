/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:21:33 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/18 23:04:59 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

int const Request::requestUncomplete = REQUEST_UNCOMPLETE;
int const Request::requestComplete = REQUEST_COMPLETE;

Request::Request()
{}

Request::Request(Request const & copy)
	:	_httpMethod(copy._httpMethod),
		_pathRequest(copy._pathRequest),
		_httpVersion(copy._httpVersion),
		_headers(copy._headers),
		_messageBody(copy._messageBody)
{}

Request & Request::operator=(Request const & rhs)
{
	if (this != &rhs)
	{
		this->_httpMethod = rhs._httpMethod;
		this->_pathRequest = rhs._pathRequest;
		this->_httpVersion = rhs._httpVersion;
		this->_headers = rhs._headers;
		this->_messageBody = rhs._messageBody;
	}

	return (*this);
}
	
Request::~Request()
{}

// Geters
std::string const & Request::getHttpMethod() const
{
	return (this->_httpMethod);
}

std::string const & Request::getPathRequest() const
{
	return (this->_pathRequest);
}

std::string const & Request::getHttpVersion() const
{
	return (this->_httpVersion);
}

std::map<std::string, std::string> const & Request::getHeaders() const
{
	return (this->_headers);
}

std::string const & Request::getMessageBody() const
{
	return (this->_messageBody);
}

bool	Request::hasMessageBody() const
{
	return (false);
}

// Seters
void	Request::setHttpMethod(std::string const & httpMethod)
{
	this->_httpMethod = httpMethod;
}

void	Request::setPathRequest(std::string const & pathRequest)
{
	this->_pathRequest = pathRequest;
}

void	Request::setHttpVersion(std::string const & httpVersion)
{
	this->_httpVersion = httpVersion;
}

void	Request::setHeaders(std::map<std::string, std::string> const & headers)
{
	this->_headers = headers; 
}

void	Request::setMessageBody(std::string const & messageBody)
{
	this->_messageBody = messageBody;
}

// Members methods
void	Request::fillHeaders(std::string const & data)
{
	(void) data;
}

void	Request::fillMessageBody(std::string const & data)
{
	(void) data;
}

bool	Request::isMessageBodyTerminated()
{
	return (false);
}
