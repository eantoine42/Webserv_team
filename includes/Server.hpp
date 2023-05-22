/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:14:41 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/22 18:50:42 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER
#define SERVER

#include "AFileDescriptor.hpp"
#include <map>

class Server
{
	private:
		int	_fd;

	public:

		Server(void);
		Server(Server const & copy);
		Server & operator=(Server const & rhs);
		virtual ~Server();

		// Constructors
		Server(int fd);
		
		// Members methods
		void	clientConnect(std::map<int, AFileDescriptor *> & map);

};

#endif
