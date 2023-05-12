/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:33:20 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/12 19:05:02 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <exception>
#include <string>
#include <vector>
#include <map>

#include "Connection.hpp"

#define BUFFER_SIZE 1080
#define	NO_EVENTS	0

class Server
{
	private:
		// TODO: Change to vector to many servers
		int							_listenerFd;
		std::vector<struct pollfd>	_fds;
		std::map<int, Connection>	_connections;

	public:
		
		Server(void);
		Server(Server const & copy);
		~Server(void);
		Server &	operator=(Server const & rhs);

		// Getters Setters
		int							getListenerFd() const;
		std::vector<pollfd> &		getFds();
		std::map<int, Connection> &	getConnections();
		

		void	serverInit(short portNumber);
		void	readRequest(pollfd & poolFd);
		void	writeResponse(pollfd & pollFd);
		bool	isListenerFd(int fd);

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

