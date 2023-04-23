#include "../../includes/c_location.hpp"
#include "../../includes/webserv.hpp"

c_location::c_location(int p, int loc_index, std::map<std::string, std::string>	cgi,bool autoindex, std::string index, std::string root, int client_body_size)
:	_port(p),
	_loc_index(loc_index),
	_root(root),
	_index(index),
	_cgi(cgi),
	_autoindex(autoindex),
	_client_body_size(client_body_size)
{
		_allow_method.push_back("POST");
		_allow_method.push_back("GET");
		_allow_method.push_back("DELETE");
		_upload_dir = "";
}

c_location::c_location(const c_location &src)
:	_port(src._port),
	_loc_index(src._loc_index),	
	_root(src._root),
	_allow_method(src._allow_method),
	_index(src._index),
	_cgi(src._cgi),
	_autoindex(src._autoindex),
	_upload_dir(src._upload_dir),
	_return(src._return),
	_client_body_size(src._client_body_size),
	_error_pages(src._error_pages),
	_uri(src._uri) {}

c_location &c_location::operator=(const c_location &src)
{
	c_location	tmp(src);
	std::swap(tmp, *this);
	return (*this);
}

c_location::~c_location(){}

/*
** c_location getters
*/
int									const &c_location::get_loc_index() const{return (_loc_index);}
int									const &c_location::get_port() const{return (_port);}
std::string							const &c_location::get_uri() const{return _uri;}
bool								const &c_location::get_autoindex() const{return _autoindex;}
std::string							const &c_location::get_index() const{return _index;}
std::string							const &c_location::get_return() const{return _return;}
std::vector<std::string>			const &c_location::get_allow_method() const{return _allow_method;}
std::string							const &c_location::get_root() const{return _root;}
std::string							const &c_location::get_upload_dir() const{return _upload_dir;}
std::map<std::string, std::string>	const &c_location::get_cgi() const{return _cgi;}
int									const &c_location::get_client_body_size() const{return (_client_body_size);}
std::string							const &c_location::get_error() const{return (_error_pages);}

void	c_location::set_location(const std::string &str,  int &count)
{
	
	std::string line = c_syntax::get_line(str, count);
	std::vector<std::string> token;
	token = c_syntax::split_string(line, WHITESPACES);
	set_uri(token);
	count ++;
	if(c_syntax::get_line(str, count).compare("{"))
		throw(ConfFileParseError("Invalid Location directive : no opening {"));
	count ++;
	int i = 0;
	int ct = 0;
	int closing_line;
	while (ct < count)
	{
		if(str[i] == '\n')
			ct++;
		i++;
	}
	closing_line = c_syntax::find_closing_bracket(str.substr(i));
	for (i = 0; i < closing_line; i++)
	{
		line = c_syntax::get_line(str, count++);
		parse_location(line);
	}
}

void	c_location::parse_location(std::string &line)
{
	typedef void (c_location::*loc_func)(std::vector<std::string> );
	loc_func	funcs[] = {&c_location::set_root, &c_location::set_allow_method, &c_location::set_index, 
	&c_location::set_cgi, &c_location::set_autoindex, &c_location::set_upload_dir, &c_location::set_return, &c_location::set_client_body_size,
	&c_location::set_error_pages};
	std::vector<std::string> token;
	int instruct;
	if ((token = c_syntax::split_string(line, WHITESPACES)).empty())
		return;
	else if ((instruct = (*this).correct_location_instruction(token)) != -1 && instruct < TOTAL_LOCATION_INSTRUCTIONS)
		(this->*funcs[instruct])(token);
	else if (instruct == TOTAL_LOCATION_INSTRUCTIONS)
		return;
	else
		throw (ConfFileParseError("Wrong input in location bloc [" + c_syntax::intToString(_loc_index)+"] : Directive " + token[0]+" invalid"));
}


/**
 * @brief Checks if the location directive are part of location block
 * 
 * @param token 
 * @return true 
 * @return false 
 */
int 	c_location::correct_location_instruction(std::vector<std::string> token)
{
	int i = 0;
	// check if the token corresponds to a valid instruction in server block
	while (i < TOTAL_LOCATION_INSTRUCTIONS)
	{
		if (!token[0].compare(c_syntax::location_instructions_tab[i].name))
			return i;
		i++;
	}
	if (c_syntax::is_nothing(token[0]) || !token[0].compare("{"))
		return TOTAL_LOCATION_INSTRUCTIONS;
	return -1;
}

int 	c_location::correct_method_instruction(std::vector<std::string> token)
{
	size_t i = 0;
	size_t j = 1;
	token[token.size() - 1] = token[token.size() - 1].erase(token[token.size() - 1].size() - 1);
	while (j < token.size())
	{
		i = 0;
		while (i < TOTAL_METHODS_INSTRUCTIONS)
		{
			if (!token[j].compare(c_syntax::method_tab[i].name))
				return j;
			i++;
		}
		j ++;
	}
	return -1;
}

/*
** c_location setters
*/
void	c_location::set_uri(std::vector<std::string> token)
{
	if(token.size() < 2 )
		throw(ConfFileParseError("Invalid Location directive : not enough arguments"));
	else if (token.size() == 2 )
		_uri = token[1];
	else if (token.size() == 3)
	{
		if (!token[1].compare("="))
			_uri =token[1] +" " + token[2];
		else throw(ConfFileParseError("Invalid Location directive : invalid location modifier " + token[1]));
	}
}

void	c_location::set_autoindex(std::vector<std::string> token)
{
	if (token.size() != 2 || !(token[1].compare("on") || token[1].compare("off")))
	throw(ConfFileParseError("Location bloc [" + c_syntax::intToString(_loc_index) +"] : problem with autoindex argument, on or off only"));
	switch (token[1].erase(token[1].size() - 1).compare("on"))
	{
	case 0:
		_autoindex = true;
		break;
	
	default:
		_autoindex = false;
		break;
	}
}
void	c_location::set_index(std::vector<std::string> token)
{
	_index = "";
	size_t i = 1;
	if (token.size() < 2)
		throw(ConfFileParseError("Location bloc [" + c_syntax::intToString(_loc_index) +"] : problem with number of arguments for index"));
	for (; i < token.size() - 1; i++)
		_index += token[i] + " ";
	_index += token[i].erase(token[i].size() - 1);
}

void	c_location::set_allow_method(std::vector<std::string> token)
{
	_allow_method.clear();
	if (correct_method_instruction(token) == -1)
		throw(ConfFileParseError("Location bloc [" + c_syntax::intToString(_loc_index) + "] : Method not allowed"));
	size_t i = 1;
	for (; i < token.size() - 1; i++)
		_allow_method.push_back(token[i]);
	_allow_method.push_back(token[i].erase(token[i].size() - 1));
}

void	c_location::set_root(std::vector<std::string> token)
{
	if (token.size() > 2)
		throw(ConfFileParseError("Location bloc [" + c_syntax::intToString(_loc_index) +"] : Only one root allowed"));
	_root = token[1].erase(token[1].size() - 1);
}

void	c_location::set_upload_dir(std::vector<std::string> token)
{
	_upload_dir = "";
	size_t i = 1;
	if (token.size() > 2)
		throw(ConfFileParseError("Location bloc [" + c_syntax::intToString(_loc_index) +"] : problem with number of arguments for upload dir"));
	_upload_dir += token[i].erase(token[i].size() - 1);
}
void	c_location::set_cgi(std::vector<std::string> token)
{
	if (token.size() != 3)
		throw(ConfFileParseError("Location bloc [" + c_syntax::intToString(_loc_index) +"] : cgi argument problem"));
	_cgi.insert(std::pair<std::string, std::string>(token[1], token[2].erase(token[2].size() - 1)));
}
void	c_location::set_error_pages(std::vector<std::string> token)
{
	if (token.size() != 3 )
		throw(ConfFileParseError("Location bloc [" + c_syntax::intToString(_loc_index) +"] : problem with number of arguments for error_page"));
	for (size_t i= 0 ; i < token[1].size(); i++)
		if (token[1][i] <48 &&  token[1][i]> 57)
			throw(ConfFileParseError("Location bloc [" + c_syntax::intToString(_loc_index) +"] : error_page : fisrt argument must be numeric"));
	if (atoi(token[1].c_str()) < 300 && atoi(token[1].c_str()) > 599)
		throw(ConfFileParseError("Location bloc [" + c_syntax::intToString(_loc_index) +"] : error_page : fisrt argument must be between 300 and 599"));
	_error_pages = token[1] + " " + token[2].erase(token[2].size() - 1);
}
void	c_location::set_client_body_size(std::vector<std::string> token)
{
	if (token.size() > 2)
		throw(ConfFileParseError("Location bloc [" + c_syntax::intToString(_loc_index) +"] : Only one client body size max"));
	_client_body_size = atoi(token[1].erase(token[1].size() - 1).c_str());
}
void	c_location::set_return(std::vector<std::string> token)
	{
		if (token.size() == 2)
			_return = token[1].erase(token[1].size() - 1);
		if (token.size() != 3 )
			throw(ConfFileParseError("Location bloc [" + c_syntax::intToString(_loc_index) +"] : problem with number of arguments for return"));
		for (size_t i= 0 ; i < token[1].size(); i++)
			if (token[1][i] <48 &&  token[1][i]> 57)
				throw(ConfFileParseError("Location bloc [" + c_syntax::intToString(_loc_index) +"] : _redirect : fisrt argument must be numeric"));
		if (atoi(token[1].c_str()) < 300 && atoi(token[1].c_str()) > 599)
			throw(ConfFileParseError("Location bloc [" + c_syntax::intToString(_loc_index) +"] : _redirect : fisrt argument must be between 300 and 599"));
		_return = token[1] + " " + token[2].erase(token[2].size() - 1);
	}

std::ostream    &operator<<(std::ostream &o, c_location  const &i) 
{
	o << "************* location bloc number ["<<i.get_loc_index()<<"] *************"<< std::endl;
	if (i.get_uri().empty() == false)
		o << "    uri				=	[" << i.get_uri() << "] :" << std::endl;
	o << "    port_number			=	[" << i.get_port() << "]" << std::endl;
	o << "    autoindex			=	[" << i.get_autoindex() << "]" << std::endl;
	if (i.get_index().empty() == false)
		o << "    index			=	[" << i.get_index() << "]" << std::endl;
	if (i.get_root().empty() == false)
		o << "    root			=	[" << i.get_root() << "]" << std::endl;
	if (i.get_return().empty() == false)
		o << "    redirect			=	[" << i.get_return() << "]" << std::endl;
	if (i.get_allow_method().empty() == false)
		o << "    methods			=	[" << i.get_allow_method() << "]" << std::endl;
	if (i.get_upload_dir().empty() == false)
		o << "    upload_dir			=	[" << i.get_upload_dir() << "]" << std::endl;
	if (i.get_cgi().empty() == false)
	{
		std::map<std::string, std::string>::const_iterator ite; 
		for (ite = i.get_cgi().begin();ite != i.get_cgi().end(); ite++)
			o << "    cgi				=	[" << ite->first<<" ; " << ite->second<<"]" << std::endl;
	}
	if (i.get_client_body_size() > 0)
		o << "    client_max_body_size	=	[" << i.get_client_body_size() << "]" << std::endl;
	if (i.get_error().empty() == false)
		o << "    error_page			=	[" << i.get_error() << "]" << std::endl;
	return (o);
};
