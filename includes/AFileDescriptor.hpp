/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AFileDescriptor.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:06:22 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/19 13:21:22 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_FILE_DESCRIPTOR_HPP
#define A_FILE_DESCRIPTOR_HPP

#include <string>

class AFileDescriptor
{
	protected:

		int			_fd;
		std::string	_rawData;
		bool		_open;

		// Cannonical fornm
		AFileDescriptor();
		AFileDescriptor(AFileDescriptor const & copy);
		AFileDescriptor & operator=(AFileDescriptor const & rhs);

		// Constructors
		AFileDescriptor(int fd);

	public:
		virtual ~AFileDescriptor();

		// Geters
		int					getFd() const;
		std::string const &	getRawData() const;
		bool				isOpen() const;
		
		// Seters
			

		virtual int	doOnRead() = 0;
		virtual int	doOnWrite() = 0;

};


#endif
