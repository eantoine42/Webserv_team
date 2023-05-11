/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:16:50 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/11 12:31:00 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <map>

class Request 
{
	private:
		// TODO: change to enum
		const std::string							_httpMethod;
		const std::string							_pathRequest;
		const std::string							_httpVersion;
		const std::map<std::string, std::string>	_headers;
		std::string									_messageBody;


	public:
		Request(void);
		~Request(void);
		Request(Request const & copy);
		Request &	operator=(Request const & rhs);	

		Request(std::string httpMethod,
				std::string pathRequest,
				std::string httpVersion,
				std::map<std::string, std::string> headers,
				std::string messageBody);

		std::string &	getMessageBody();



};

#endif
