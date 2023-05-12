/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:17:46 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/12 20:06:51 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MessageFactory.hpp"

#include <map>
#include <fstream>
#include <iostream>

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

std::string		MessageFactory::createResponse()
{
	std::ifstream file("sample.json");
	if (!file.good())
	{
		std::cerr << "Error while opening file" << std::endl;
		return (MessageFactory::errorResponse());
	}
	std::string result;
	const char * response = "HTTP/1.1 200 OK\r\nContent-type: application/json\r\nContent-length: ";

	result.append(response);

	file.seekg(0, file.end);
	int size = file.tellg();
	file.seekg(0, file.beg);

	char * buffer = new char [size + 1];
	file.read(buffer, size);
	buffer[file.gcount()] = '\0';

	char integer[20];
	std::sprintf(integer, "%d", size);
	result.append(integer);
	result.append("\r\n\r\n");
	result.append(buffer);

	delete [] buffer;
	file.close();
	return (result);
}

std::string		MessageFactory::errorResponse()
{
	std::string error("HTTP/1.1 400 BAD REQUEST\r\n");

	return (error);
}
/* ************************************************************************** */
//						           PRIVATE									  //
/* ************************************************************************** */

//	Static attributes


// Static methods


// Constructor
