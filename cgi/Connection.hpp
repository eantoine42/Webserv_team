/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:02:51 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/11 15:03:33 by lfrederi         ###   ########.fr       */
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
		std::string	_requestRawData;
		Request		_request;
		Response	_response;


	public:
		Connection(void);
		~Connection(void);
		Connection(Connection const & copy);
		Connection &	operator=(Connection const & rhs);

		Connection(int socketFd);

		bool	readRequest();
		bool	isRequestTerminated();

		Request &		getRequest();
		std::string &	getRequestRawData();
		int				getSocketFd();
		void			setRequest(Request & request);
		void			setSocketFd(int socketFd);
};

#endif
