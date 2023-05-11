/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:17:46 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/11 12:35:21 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MessageFactory.hpp"
#include <map>

/* ************************************************************************** */
//						           PUBLIC									  //
/* ************************************************************************** */

// Canonical form
MessageFactory::MessageFactory(void)
{}

MessageFactory::~MessageFactory(void)
{}

MessageFactory::MessageFactory(MessageFactory const & copy)
{
	(void) copy;
}

MessageFactory & MessageFactory::operator=(MessageFactory const & rhs)
{
	if (this != &rhs)
	{}

	return (*this);
}

// Members static methods
Request *	MessageFactory::createRequest(std::string const & rawData)
{
	(void) rawData;

	std::map<std::string, std::string> headers;	
	headers["Host"] = "localhost:18000";
	headers["User-Agent"] = "curl/7.81.0";
	headers["Accept"] = "*/*";

	return new Request("GET", "/index.php", "HTTP/1.1", headers, "");	
}


/* ************************************************************************** */
//						           PRIVATE									  //
/* ************************************************************************** */

//	Static attributes


// Static methods


// Constructor
