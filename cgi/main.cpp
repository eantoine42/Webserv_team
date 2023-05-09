/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:42:00 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/09 18:57:01 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int main()
{
	Server server;

	try
	{
		server.serverInit(18000);
	} catch (Server::ServerInitException & e) {
		std::cout << e.what() << std::endl;
		return (1);
	}
	
	server.listening();


	return (0);
}
