/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 21:47:26 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/10 22:08:11 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "AHTTPMessage.hpp"

class Response : public AHTTPMessage
{
	public:
		
		Response(void);
		virtual ~Response(void);
		Response(Response const & copy);
		Response &	operator=(Response const & rhs);
		

	private:
		// TODO: Change to enum
		std::string	_status;

};

#endif
