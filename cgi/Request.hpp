/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:16:50 by lfrederi          #+#    #+#             */
/*   Updated: 2023/05/10 22:07:58 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "AHTTPMessage.hpp"

class Request : public AHTTPMessage 
{
	public:
		
	Request(void);
	virtual ~Request(void);
	Request(Request const & copy);
	Request &	operator=(Request const & rhs);	

	bool	isRequestTerminated() const;	
	void	fillFieldsWithRawData();

	private:
		// TODO: change to enum
		std::string	_httpMethod;
		std::string	_pathRequest;


};

#endif
