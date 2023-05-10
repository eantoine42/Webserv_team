/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 21:52:51 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/10 21:55:30 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"
#include "AHTTPMessage.hpp"

/* ************************************************************************** */
//						           PUBLIC									  //
/* ************************************************************************** */

// Canonical form
Response::Response(void) : AHTTPMessage()
{}

Response::~Response(void)
{}

Response::Response(Response const & copy)
	:	AHTTPMessage(copy),
		_status(copy._status)
{}

Response & Response::operator=(Response const & rhs)
{
	if (this != &rhs)
	{
		this->_rawData = rhs._rawData;
		this->_httpVersion = rhs._httpVersion;
		this->_headers = rhs._headers;
		this->_bodyMessage = rhs._bodyMessage;
		this->_status = rhs._status;
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
