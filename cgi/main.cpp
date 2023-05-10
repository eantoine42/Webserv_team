/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:42:00 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/10 18:48:36 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Request.hpp"
#include <iostream>

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
	
	Request reauest;
	reauest.getRawData();

	server.listening();


	return (0);
}
