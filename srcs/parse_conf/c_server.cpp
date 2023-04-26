#include "../../includes/c_server.hpp"
#include "../../includes/webserv.hpp"

	c_server::c_server(void)
	:	_root("html"),
		_port(8080),
		_server_name(""),
		_IP("0.0.0.0"),
		_index("index index.html"),
		_autoindex(false),
		_client_body_size(1){}

	c_server::c_server(c_server const &src)
	:	_root(src._root),
		_port(src._port),
		_server_name(src._server_name),
		_IP(src._IP),
		_error_pages(src._error_pages),
		_index(src._index),
		_client_body_size(src._client_body_size),
		_cgi(src._cgi),
		_location(src._location)	{}
	
	c_server &c_server::operator=(c_server const &src){
		c_server tmp(src);
		std::swap(tmp, *this);
		return (*this);
	}

	c_server::~c_server(){}

	/*
	** Server getters
	*/
	std::string							const &c_server::getRoot() const{return (_root);}
	std::map<std::string, std::string>	const &c_server::getCgi() const{return (_cgi);}
	int									const &c_server::getPort() const{return (_port);}
	std::string							const &c_server::getName() const{return (_server_name);}
	std::string							const &c_server::getIndex() const{return (_index);	}
	bool								const &c_server::getAutoindex() const{return (_autoindex);}
	std::string							const &c_server::getIp() const{return (_IP);}
	std::string							const &c_server::getError() const{return (_error_pages);}
	int									const &c_server::getClientBodySize() const{return (_client_body_size);}
	std::vector<c_location>				const &c_server::getLocation() const{return (_location);}
	
/**
	 * @brief Checks if the server directive are part of server or location block
	 * 
	 * @param token 
	 * @return true 
	 * @return false 
	 */
	int 	c_server::correctServerInstruction(std::vector<std::string> token)
	{
				int i = 0;
		// check if the token corresponds to a valid instruction in server block
		while (i < TOTAL_SERVER_INSTRUCTIONS)
		{
			if (!token[0].compare(c_syntax::server_instructions_tab[i].name))
				return i;
			i++;
		}
		if (c_syntax::isNothing(token[0]) || !token[0].compare("{"))
			return TOTAL_SERVER_INSTRUCTIONS;
		return -1;}

/**
 * @brief returns the number of line of location bloc
 * 
 * @param str 
 * @param count 
 * @return int 
 */
int	c_server::skipLocationBlock(std::string str, int count)
{
	int i = 0;
	int in = 0;
	int ct = 0;
	while (str[i] && ct < count)
	{
		if (str[i] == '\n')
			ct++;
		i++;
	}
	i +=8;
	while (str[i] && str[i] != '\n' && in == 0)
	{
		if (str[i] == '{')
			in = 1;
		i++;
	}
	ct += c_syntax::findClosingBracket(str.substr(i + 2));
	return (ct -1 - count);
}

/**
 * @brief from the config string
 * parse the server and locations blocs
 * 
 * @param str 
 */
void	c_server::setServer(const std::string &str)
{
	int count = 0;
	int pos_end = c_syntax::findClosingBracket(str);
	int location_ct = 0;
	//DEBUG_COUT("\n****Server to parse without line server {  \n\n" + str);
	while (count < pos_end)
	{
		c_server::parseServer(str, count);
		count++;
	}
	count = 0;
	while (count < pos_end)
	{
		if (c_server::getLocationBloc(str,count) == -1)
			count++;
		else c_server::addLocation(str, count, ++location_ct);
	}
	//std::cout<<*this<<std::endl;
}

int	c_server::getLocationBloc(std::string str, int &count)
{
	std::vector<std::string> token;
	std::string line = c_syntax::getLine(str, count);
	if ((token = c_syntax::splitString(line, WHITESPACES)).empty())
		return -1;
	else if ((*this).correctServerInstruction(token) != LOCATION_INSTRUCTION)
		return -1;
	else return 1;
}

void c_server::init_vector_server_fct(std::vector<server_func> &funcs)
{
	funcs.push_back(&c_server::setRoot);
	funcs.push_back( &c_server::setPort);
	funcs.push_back(&c_server::setName);
	funcs.push_back(&c_server::setError);
	funcs.push_back(&c_server::setIndex);
	funcs.push_back(&c_server::setAutoindex);
	funcs.push_back(&c_server::setClientBodySize);
	funcs.push_back(&c_server::setCgi);
}


/**
 * @brief fills all the server data
 * 
 * @param str 
 */
void	c_server::parseServer(std::string str, int &count)
{
	std::vector<server_func>	funcs;
	init_vector_server_fct(funcs);

	std::vector<std::string> token;
	int instruct;
	std::string line = c_syntax::getLine(str, count);
	if ((token = c_syntax::splitString(line, WHITESPACES)).empty())
		return ;
	else if ((instruct = (*this).correctServerInstruction(token)) != -1)
	{
		if (instruct == LOCATION_INSTRUCTION)
			count += skipLocationBlock(str, count);
		else
			if (instruct < TOTAL_SERVER_INSTRUCTIONS && instruct != LOCATION_INSTRUCTION)
				(this->*funcs[instruct])(token);		
	}
	else
		throw (ConfFileParseError("Wrong input in server : Directive " + token[0]+" invalid"));
}

void	c_server::addLocation(std::string str, int &count, int &server_ct)
{
		c_location loc(getPort(),server_ct, getCgi(), getAutoindex(), getIndex(), getRoot(), getClientBodySize());
		loc.setLocation(str, count);
		this->_location.push_back(loc);
}


void	c_server::setRoot(std::vector<std::string> token)
{
	if (token.size() > 2)
		throw(ConfFileParseError("Only one root allowed"));
	_root = token[1].erase(token[1].size() - 1);
}
	
void	c_server::setCgi(std::vector<std::string> token)
{
	if (token.size() != 3)
		throw(ConfFileParseError("cgi argument problem"));
	_cgi.insert(std::pair<std::string, std::string>(token[1], token[2].erase(token[2].size() - 1)));
}
	
void	c_server::setPort(std::vector<std::string> token)
{
	setIp(token);
	std::string str;
	if (token.size() > 2)
		throw(ConfFileParseError("Only one port allowed"));
	std::vector<std::string> tmp = c_syntax::splitString(token[1],":");
	if (tmp.size() == 1)
		str = tmp[0].substr(0, tmp[0].size() - 1);
	else 
		str = tmp[1].substr(0, tmp[1].size() - 1);
	for (size_t i = 0; i < str.size(); i++)
		if (str[i] < 48 || str[i] > 57)
			throw(ConfFileParseError("put only digits for port"));
	_port = atoi(str.c_str());
}

void	c_server::setIp(std::vector<std::string> token)
{
	std::string str;
	if (token.size() > 2)
		throw(ConfFileParseError("Only one IP:port allowed"));
	std::vector<std::string> tmp = c_syntax::splitString(token[1],":");
	if ((!tmp[0].compare("*") && tmp[0].size() == 1))
	{
		_IP = tmp[0];
		return ;
	}
	if ((!tmp[0].compare("localhost") && tmp[0].size() == 9))
	{
		_IP = "127.0.0.1";
		return ;
	}
	std::vector<std::string> tmp1 = c_syntax::splitString(tmp[0],".");
	if (tmp1.size() != 4)
		throw(ConfFileParseError("IP formating problem"));
	for (int j = 0; j< 4; j++)
	{
		if(atoi(tmp1[j].c_str()) < 0 || atoi(tmp1[j].c_str()) > 255)
			throw(ConfFileParseError("IP formating problem"));
	}
	_IP = tmp[0];
}

void	c_server::setName(std::vector<std::string> token)
{
	size_t i = 0;
	_server_name = "";
	if (token.size() <2)
		throw(ConfFileParseError("Parameter problem with server name"));
	token.erase(token.begin());
	for (std::vector<std::string>::iterator it = token.begin(); it != token.end(); ++it) {
        std::string& str = *it;
        str.erase(std::remove(str.begin(), str.end(), ';'), str.end());
    }
		std::sort(token.begin(), token.end());
		token.erase(std::unique(token.begin(), token.end()), token.end());//enleve les noms en doublons dans chaque serveur
	for (; i < token.size(); i++)
	{
		_server_name += token[i];
		if (i != token.size() - 1)
			_server_name += " ";
	}
}
	
void	c_server::setError(std::vector<std::string> token)
{
	if (token.size() != 3 )
		throw(ConfFileParseError("problem with number of arguments for error_page"));
	for (size_t i= 0 ; i < token[1].size(); i++)
		if (token[1][i] <48 &&  token[1][i]> 57)
			throw(ConfFileParseError("error_page : fisrt argument must be numeric"));
	if (atoi(token[1].c_str()) < 300 && atoi(token[1].c_str()) > 599)
		throw(ConfFileParseError("error_page : fisrt argument must be between 300 and 599"));
	_error_pages = token[1] + " " + token[2].erase(token[2].size() - 1);
}

void	c_server::setIndex(std::vector<std::string> token)
{
	_index = "";
	size_t i = 1;
	if (token.size() < 2)
		throw(ConfFileParseError("problem with number of arguments for index"));
	for (; i < token.size() - 1; i++)
		_index += token[i] + " ";
	_index += token[i].erase(token[i].size() - 1);
}

void	c_server::setAutoindex(std::vector<std::string> token)
{
	if (token.size() != 2 || !(token[1].compare("on") || token[1].compare("off")))
		throw(ConfFileParseError("problem with autoindex argument"));
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

void	c_server::setClientBodySize(std::vector<std::string> token)
{
	if (token.size() > 2)
		throw(ConfFileParseError("Only one client body size max"));
	_client_body_size = atoi(token[1].erase(token[1].size() - 1).c_str());
}


void c_server::cleanDupServer(std::vector<c_server> server_info)
{
	if (server_info.size() == 0)
	return ;
	std::vector<c_server>::iterator it = server_info.begin();
	std::vector<std::string>::iterator it2;
	std::string list_names;
	std::string res;
	std::vector<std::string> vect_names1;
	std::vector<std::string> vect_names2 = c_syntax::splitString(this->_server_name);

	for(; it != server_info.end(); it++)
	{
		if (!(this->_IP.compare(it->_IP)) && (this->_port ==(it->_port)))
		{		
			list_names = (*it).getName();
			vect_names1 = c_syntax::splitString(list_names);
			std::vector<std::string> vect_names4(vect_names1.size() + vect_names2.size());
			it2 = std::set_intersection(vect_names1.begin(), vect_names1.end(), vect_names2.begin(), vect_names2.end(), vect_names4.begin());
			vect_names4.resize(it2 - vect_names4.begin());
			it2 = vect_names4.begin();
			for(;it2 !=vect_names4.end();it2++)
				std::cerr<<"Duplicate server name : ["<<*it2<<"] only the first instance will be kept, the other will be ignored\n";	

			std::vector<std::string> vect_names3;
			std::set_difference(vect_names2.begin(), vect_names2.end(),
				vect_names1.begin(), vect_names1.end(), std::inserter(vect_names3, vect_names3.begin()));
			for (std::vector<std::string>::iterator it = vect_names3.begin(); it != vect_names3.end(); it++){
				res += *it;
				if (it != vect_names3.end() - 1)
					res+=" ";
			}
			this->_server_name = res;
		}
		
	}
	
}

std::ostream    &operator<<(std::ostream &o, c_server const &i)
{
    
	o << "************* Server bloc [" << i.getName() << "] *************"<< std::endl;
	if (i.getIp().empty() == false)
		o << "    listen			=	[" << i.getIp() << "]" << std::endl;
	if (i.getPort() >0 )
		o << "    portNumber			=	[" << i.getPort() << "]" << std::endl;
    if (i.getName().empty() == false)
		o << "    serverName			=	[" << i.getName() << "]" << std::endl;
	if (i.getRoot().empty() == false)
		o << "    root			=	[" << i.getRoot() << "]" << std::endl;
	if (i.getIndex().empty() == false)
		o << "    indexPage			=	[" << i.getIndex() << "]" << std::endl;
	o << "    autoindex			=	[" << i.getAutoindex() << "]" << std::endl;
    if (i.getError().empty() == false)
		o << "    errorPage			=	[" << i.getError() << "]" << std::endl;
	if (i.getCgi().empty() == false)
	{
		std::map<std::string, std::string>::const_iterator ite; 
		for (ite = i.getCgi().begin();ite != i.getCgi().end(); ite++)
	   		o << "    cgi 			=	[" << ite->first<<" ; " << ite->second<<"]" << std::endl;
	}
    if (i.getClientBodySize() > 0)
		o << "    clientMaxBodySize		=	[" << i.getClientBodySize() << "]" << std::endl;
	for (size_t j = 0; j< i.getLocation().size(); j++)
		o<<i.getLocation()[j]<< std::endl;
    return (o);
};

std::ostream    &operator<<(std::ostream &o, std::vector<c_server>  const &srv)
{
	for (size_t i = 0; i< srv.size(); i++)
		o<<srv[i]<< std::endl;
	return (o);
}

//TODO ignore a server if same ip:port or name
