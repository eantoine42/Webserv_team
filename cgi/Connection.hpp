/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:02:51 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/10 22:09:00 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "Request.hpp"
#include "Response.hpp"

class Connection
{
	private:
		int			_socketFd;
		Request		_request;
		Response	_response;

		Connection(void);

	public:
		~Connection(void);
		Connection(Connection const & copy);
		Connection &	operator=(Connection const & rhs);

		Connection(int socketFd);
};

#endif
