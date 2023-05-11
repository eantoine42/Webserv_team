/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:32:48 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/11 11:12:54 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include <string>

/* ************************************************************************** */
//						           PUBLIC									  //
/* ************************************************************************** */

// Canonical form
Request::Request(void)
{}

Request::~Request(void)
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
		this->_messageBody = rhs._messageBody;
	}

	return (*this);
}

// Constructor
Request::Request(std::string httpMethod,
				std::string pathRequest,
				std::string httpVersion,
				std::map<std::string, std::string> headers,
				std::string messageBody)
	:	_httpMethod(httpMethod),
		_pathRequest(pathRequest),
		_httpVersion(httpVersion),
		_headers(headers),
		_messageBody(messageBody)
{}

// Members methods
std::string &	Request::getMessageBody()
{
	return this->_messageBody;
}
/* ************************************************************************** */
//						           PRIVATE									  //
/* ************************************************************************** */

//	Static attributes


// Static methods


