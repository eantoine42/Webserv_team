/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:42:00 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/08 22:26:14 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int main()
{
	Server server;
	std::cout << server;

	try
	{
		server.serverInit(18000);
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
	
	server.listening();


	return (0);
}
