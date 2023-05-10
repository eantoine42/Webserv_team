/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:33:20 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/10 21:58:59 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <exception>
#include <string>
#include <vector>

#define BUFFER_SIZE 1080
#define	NO_EVENTS	0

class Server
{
	private:
		int							_listenerFd;
		std::vector<struct pollfd>	_fds;

		void	readRequest(pollfd & pollfd);
		void	writeResponse(pollfd & pollfd);

	public:
		
		Server(void);
		Server(Server const & copy);
		~Server(void);
		Server &	operator=(Server const & rhs);

		int		getListenerFd() const;

		void	serverInit(short portNumber);
		void	listening();

		class ServerInitException : std::exception
		{
			public:
				ServerInitException(std::string const message);
				virtual ~ServerInitException() throw();

				virtual const char * what() const throw();

			private:
				const std::string _message;
		};

		
};

#endif

