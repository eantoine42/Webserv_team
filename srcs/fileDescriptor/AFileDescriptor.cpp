/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AFileDescriptor.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:40:16 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/18 16:57:51 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AFileDescriptor.hpp"
#include <iostream>

// Cannonical Form
AFileDescriptor::AFileDescriptor(void)
{}

AFileDescriptor::AFileDescriptor(AFileDescriptor const & copy)
	: _fd(copy._fd), _rawData(copy._rawData), _open(copy._open)
{}

AFileDescriptor & AFileDescriptor::operator=(AFileDescriptor const & rhs)
{
	if (this != &rhs)
	{
		this->_fd = rhs._fd;
		this->_rawData = rhs._rawData;
		this->_open = rhs._open;
	}
	return (*this);
}

AFileDescriptor::~AFileDescriptor()
{
	std::cout << "Destructor AFileDescriptor" << std::endl;
}

// Constructors
AFileDescriptor::AFileDescriptor(int fd)
	:	_fd(fd)
{}

// Geters
int		AFileDescriptor::getFd() const
{
	return (this->_fd);
}

std::string const &		AFileDescriptor::getRawData() const
{
	return (this->_rawData);
}

bool	AFileDescriptor::isOpen() const
{
	return (this->_open);
}
