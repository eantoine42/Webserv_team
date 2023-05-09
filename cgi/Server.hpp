/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:33:20 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/09 19:11:38 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>

#define BUFFER_SIZE 1080

class Server
{
	public:
		
		Server(void);
		Server(Server const & copy);
		~Server(void);
		Server &	operator=(Server const & rhs);

		int		getListenerFd() const;

		void	serverInit(short portNumber);
		void	listening() const;

		class ServerInitException : std::exception
		{
			public:
				ServerInitException(std::string const message);
				
				virtual const char * what() const throw();

			private:
				const std::string _message;
		};

	private:
		int		_listenerFd;

};

#endif

