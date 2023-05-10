/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:32:48 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/10 21:42:09 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

/* ************************************************************************** */
//						           PUBLIC									  //
/* ************************************************************************** */

// Canonical form
Request::Request(void) : AHTTPMessage()
{}

Request::~Request(void)
{}

Request::Request(Request const & copy)
	:	AHTTPMessage(copy),
		_httpMethod(copy._httpMethod),
		_pathRequest(copy._pathRequest)	
{}

Request & Request::operator=(Request const & rhs)
{
	if (this != &rhs)
	{
		this->_rawData = rhs._rawData;
		this->_httpVersion = rhs._httpVersion;
		this->_headers = rhs._headers;
		this->_bodyMessage = rhs._bodyMessage;
		this->_httpMethod = rhs._httpMethod;
		this->_pathRequest = rhs._pathRequest;
	}

	return (*this);
}

// Constructors


// Destructor


// Members methods


/* ************************************************************************** */
//						           PRIVATE									  //
/* ************************************************************************** */

//	Static attributes


// Static methods


// Constructor
