/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:09:19 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/11 11:16:47 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_FACTORY
#define MESSAGE_FACTORY

#include <string>
#include "Request.hpp"


class MessageFactory
{
	private:
		MessageFactory(void);
		~MessageFactory(void);
		MessageFactory(MessageFactory const & copy);
		MessageFactory &	operator=(MessageFactory const & rhs);

		static bool	allHeadersReceived();

	public:
		static Request *	createRequest(std::string const & rawData);
		
		



};

#endif
