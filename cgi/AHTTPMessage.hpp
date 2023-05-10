/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AHTTPMessage.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:48:26 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/10 22:07:41 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_HTTP_MESSAGE
#define A_HTTP_MESSAGE

#include <string>
#include <map>

class AHTTPMessage
{
	protected:
		std::string							_rawData;
		std::string							_httpVersion;
		std::map<std::string, std::string>	_headers;
		std::string							_bodyMessage;
		
		AHTTPMessage(void);
		virtual ~AHTTPMessage(void);
		AHTTPMessage(AHTTPMessage const & copy);
		AHTTPMessage &	operator=(AHTTPMessage const & rhs);	

	public:
		std::string &	getRawData();
};

#endif
