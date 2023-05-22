/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketFd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:02:19 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/22 19:29:49 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketFd.hpp"
#include "Debugger.hpp"

#include <cstddef>
#include <iostream>
#include <unistd.h> // read
#include <cstdio> // perror
#include <fstream>

SocketFd::SocketFd(void) : AFileDescriptor()
{}

SocketFd::SocketFd(SocketFd const & copy)
	:	AFileDescriptor(copy)
{}

SocketFd & SocketFd::operator=(SocketFd const & rhs)
{
	if (this != &rhs)
	{
		this->_fd = rhs._fd;
		this->_rawData = rhs._rawData;
		this->_open = rhs._open;
	}

	return (*this);

}

SocketFd::~SocketFd()
{
	std::cout << "SocketFd destructor()" << std::endl;
}

SocketFd::SocketFd(int fd)
	:	AFileDescriptor(fd)
{}


Request const &	SocketFd::getRequest() const
{
	return (this->_request);
}

int		SocketFd::doOnRead()
{
	char	buffer[BUFFER_SIZE];
	size_t	n;
	size_t	posHeadersEnd;

	while ((n = read(this->_fd, buffer, BUFFER_SIZE - 1)) > 0)
	{
		buffer[n] = '\0';
		this->_rawData.append(buffer);
		// End request
		if ((posHeadersEnd = this->_rawData.find("\r\n\r\n") != std::string::npos))
			break ;
	}
	
	std::cout << this->_rawData;

	// Socket connection close, a EOF was present
	if (n == 0)
		return (1); 

	// Try to fill hearders if empty
	if (this->_request.getHeaders().empty())
	{
		if (posHeadersEnd == std::string::npos)
			return (Request::requestUncomplete);
		this->_request.fillHeaders(this->_rawData);
	}

	if (!this->_request.hasMessageBody())
	{
		this->_rawData.clear();
		return (Request::requestComplete);
	}

	this->_request.fillMessageBody(this->_rawData);
	if (this->_request.isMessageBodyTerminated())
		return (Request::requestComplete);

	return (Request::requestUncomplete);
}

int		SocketFd::doOnWrite()
{
	std::ifstream file("sample.json");
	if (!file.good())
	{
		std::cerr << "Error while opening file" << std::endl;
		return (1);
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
	write(this->_fd, result.c_str(), result.length());

	return (0);
}
