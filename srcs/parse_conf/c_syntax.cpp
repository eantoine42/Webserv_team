#include "../../includes/webserv.hpp"

/**
 * @brief trim line from # until the end
 * 
 * @param str 
 * @return std::string 
 */
std::string		syntax::trimComments(const std::string &str) {
	std::string new_line;
	size_t hash_char_pos;

	new_line = str;
	hash_char_pos = new_line.find('#');
	if (hash_char_pos == std::string::npos)
		return new_line;
	return new_line.substr(0, hash_char_pos);
}

/**
 * @brief Delete extra whitespaces if more than one
 * 
 * @param str 
 * @return std::string 
 */
std::string		syntax::replaceConsecutiveSpaces(const std::string& str) 
{
    std::stringstream ss;
    bool previousCharIsSpace = false;
    for (std::string::const_iterator it = str.begin(); it!=str.end(); ++it) 
	{
        char c = *it;
        if ( !isspace(c) || !previousCharIsSpace)
            ss << c;
        previousCharIsSpace = isspace(c);
    }
    return ss.str();
}

/**
 * @brief Trim whitespaces at beginning, at end of line, 
 *	and replaces chain of whitespaces by a single space
 *	return : std::string
 * 
 * @param str 
 * @return std::string 
 */
std::string		syntax::trimWhitespaces(const std::string& str)
{
	std::string whitespaces;
	std::string new_line;
	size_t start, end;

	whitespaces = WHITESPACES;
	new_line = str;
	start = new_line.find_first_not_of(whitespaces);
	if (start != std::string::npos)
		new_line = new_line.substr(start);
	end = new_line.find_last_not_of(whitespaces);
	if (end != std::string::npos)
		new_line = new_line.substr(0, end + 1);
	new_line = replaceConsecutiveSpaces(new_line);
	std::replace_if(new_line.begin(), new_line.end(), isspace, ' ');
	return new_line;
}

/**
 * @brief gets a line into a line filles with "\n"
 * given a line number
 * @param str 
 * @param n quelle ligne?
 * @return std::string 
 */
std::string		syntax::getLine(std::string str, size_t n)
{
	int i = 0;
	size_t j = 0;
	size_t ct = 0;
	std::string temp;

	if (n >= nbLines(str))
		return std::string();
	while (ct < n)
	{
		if (str[i++] =='\n')
			ct++;
	}
	while (std::isspace(str[i]) && str[i] != '\n')
		++i;
	while (str[i + j] && str[i + j] != '\n')
		j++;
	while (j > 0 && std::isspace(str[i + j - 1]))
		--j;
	temp = std::string(str, i, j);
	return (temp);
}

/**
 * @brief return  number of lines in the string (\n separated)
 * 
 * @param str_config 
 * @return size_t 
 */
size_t			syntax::nbLines(std::string &str_config)
{
	size_t lines = 1;
	for (std::string::iterator ite = str_config.begin(); ite!=str_config.end(); ite++)
		if (*ite == '\n')
			lines++;
	return (lines);
}

/**
 * @brief Check if the line from conf file is of interest 
 * ie size > 0 and not }
 * @param str 
 * @param pos 
 * @return true 
 * @return false 
 */
bool			syntax::isNothing(std::string str, int pos)
{
	std::string line;

	line = syntax::getLine(str, pos);
	return (line.size() == 0 || line[0] == '}');
}

/**
 * @brief Check if brackets opened/closed is correct
 * 
 * @param config_string 
 * @return true 
 * @return false 
 */
bool			syntax::checkBrackets(std::string &config_string)
{
	std::stack<char>	bracket;
	std::string::iterator ite;
	ite = config_string.begin();
	for (;ite != config_string.end();ite++)
	{
		if (*ite == '{')
			bracket.push(*ite);
		if (*ite == '}')
		{
			if (bracket.empty() || bracket.top() != '{')
				return false;
			if (!bracket.empty() && bracket.top() == '{')
				bracket.pop();
		}
	}
	if (bracket.empty())
		return true;
	return false;
}

/**
 * @brief 
 * test if path to .conf is correct, testing
 * emptypath, extension, readable, if directory
 * trying to open file
 * @param path 
 */
void			syntax::testPath(const std::string &path)
{
	size_t ext_pos;
	std::ifstream file;
	
	if (path.empty())
		throw (EmptyConfPath());
	ext_pos = path.find(".conf");
	if (ext_pos == std::string::npos|| ext_pos != path.size() - 5)
		throw (BadExtensionConfFile());
	if (!fileExists(path.c_str()))
		throw (FileDoesNotExist());
	if (!fileRead(path.c_str()))
		throw (FileNotReadable());
	if (isDirectory(path.c_str()))
		throw (PathIsDir());
	file.open(path.c_str(), std::ios_base::in);
	if (!file) {
		throw (InvalidConfFilePath());
	}
}

/**
 * @brief gets a line and returns a line, trimming the first i lines
 * 
 * @param string 
 * @param position
 * @return std::string 
 */
std::string 	syntax::trimLineToI(std::string &str, size_t pos)
{
	int i = 0;
	size_t ct = 0;
	std::string temp;

	if (pos >= nbLines(str))
		return temp;
	while (ct < pos)
	{
		if (str[i++] =='\n')
			ct++;
	}
	temp = std::string(str, i);
	return (temp);
}

/**
 * @brief Finds the closing bracket line in the 
 * string where the first opening bracket has already been
 * removed: needs to checked pairs of included brackets
 * 
 * @param str 
 * @return int 
 */
int				syntax::findClosingBracket(std::string str)
{
	int line = 1;
	int count = 1;
	for (size_t i = 0; i < nbLines(str); i++)
	{
		if (getLine(str, i).find("{")!= std::string::npos)
			count +=1;
		if (getLine(str, i).find("}")!= std::string::npos)
		{
			if ((count -=1) == 0)
				return line;
		}
		line ++;
	}
	return (-1);
}

/**
 * @brief splits a string around a character in the given charset
 * 
 * @param str 
 * @param charset 
 * @return std::vector<std::string> 
 */
std::vector<std::string> syntax::splitString(std::string str, const std::string &charset)
{
	std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;

    while ((pos = str.find_first_of(charset)) != std::string::npos)
	{
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + 1);
    }
    tokens.push_back(str);
    return tokens;
}

std::string syntax::intToString(int num) {
  std::stringstream ss;
  ss << num;
  return ss.str();
}

/**
 * @brief makes sure the conf file lines finishes by ;
 * and { are isolated in one line
 * deleting the single \n
 * 
 * @param std::string &conf 
 */
void syntax::formatConfFile(std::string &conf)
{
	int i = 0;
	int j = conf.size();
	while (i < j){
		if (conf[i] == ';'){
			conf.replace(i, 1, ";\n");
			j++;
		}
		i++;
	}
	i = 0;
	j = conf.size();
	while (i < j){
		if (conf[i] == '{'){
			conf.replace(i, 1, "\n{\n");
			j +=2;
			i +=2;
		}
		else i++;
	}
	i = 0;
	j = conf.size();
	while (i < j){
		if (conf[i] == '}'){
			conf.replace(i, 1, "\n}\n");
			j+=2;
			i+=2;
		}
		else
			i++;
	}
	i = 0;
	j = conf.size();
	while (i < j){
		if (conf[i] == '\n' && conf[i+1] && conf[i+1] == '\n'){
			conf.replace(i, 2, "\n");
			j-=1;
			i-=1;
		}
		else
			i++;
	}
}

/**
 * @brief tool used to format properly the conf string
 * returning \n or " "
 * 
 * @param str 
 * @return char 
 */
char syntax::checkChar(std::string str)
{
		if (str[str.size()-1] == ';')
			return '\n';
		if (!str.compare("server") || !str.compare("{") || !str.compare("}") )
			return '\n';
		return (' ');
}

/**
	 * @brief Checks if the server directive are part of server or location block
	 * 
	 * @param token 
	 * @return true 
	 * @return false 
	 */
	int 	syntax::correctServerInstruction(std::vector<std::string> token)
	{
				int i = 0;
		// check if the token corresponds to a valid instruction in server block
		while (i < TOTAL_SERVER_INSTRUCTIONS)
		{
			if (!token[0].compare(syntax::server_instructions_tab[i].name))
				return i;
			i++;
		}
		if (syntax::isNothing(token[0]) || !token[0].compare("{"))
			return TOTAL_SERVER_INSTRUCTIONS;
		return -1;
}

/**
 * @brief Checks if the location directive are part of location block
 * 
 * @param token 
 * @return true 
 * @return false 
 */
int 	syntax::correctLocationInstruction(std::vector<std::string> token)
{
	int i = 0;
	// check if the token corresponds to a valid instruction in server block
	while (i < TOTAL_LOCATION_INSTRUCTIONS)
	{
		if (!token[0].compare(syntax::location_instructions_tab[i].name))
			return i;
		i++;
	}
	if (syntax::isNothing(token[0]) || !token[0].compare("{"))
		return TOTAL_LOCATION_INSTRUCTIONS;
	return -1;}

int 	syntax::correctMethodInstruction(std::vector<std::string> token)
{
	size_t i = 0;
	size_t j = 1;
	token[token.size() - 1] = token[token.size() - 1].erase(token[token.size() - 1].size() - 1);
	while (j < token.size())
	{
		i = 0;
		while (i < TOTAL_METHODS_INSTRUCTIONS)
		{
			if (!token[j].compare(syntax::method_tab[i].name))
				return j;
			i++;
		}
		j ++;
	}
	return -1;
}

/**
 * @brief lists all methods instructions
 * for use in the table of functions
 * 
 */
const syntax::method_tab_entry_t
syntax::method_tab[] = {
	{GET, "GET"},
	{HEAD, "HEAD"},
	{POST, "POST"},
	{PUT, "PUT"},
	{DELETE, "DELETE"},
	{CONNECT, "CONNECT"},
	{OPTIONS, "OPTIONS"},
	{TRACE, "TRACE"},
};

/**
 * @brief lists all server instructions
 * for use in the table of functions
 * 
 */
const syntax::server_instruction_tab_entry_t
syntax::server_instructions_tab[] = {
	{S_ROOT, "root"},
	{LISTEN, "listen"},
	{SERVER_NAME, "server_name"},
	{S_ERROR_PAGE, "error_page"},
	{S_INDEX, "index"},
	{S_AUTOINDEX, "autoindex"},
	{S_CLIENT_MAX_BODY_SIZE, "client_max_body_size"},
	{S_CGI, "cgi"},
	{LOCATION_INSTRUCTION, "location"}
};


/**
 * @brief lists all location instructions
 * for use in the table of functions
 * 
 */
const syntax::location_instruction_tab_entry_t
syntax::location_instructions_tab[] = {
	{L_ROOT, "root"},
	{METHODS, "methods"},
	{L_INDEX, "index"},
	{L_CGI, "cgi"},
	{L_AUTOINDEX, "autoindex"},
	{UPLOAD_DIR, "upload_dir"},
	{RETURN,"return"},
	{L_CLIENT_MAX_BODY_SIZE, "client_max_body_size"},
	{L_ERROR_PAGE, "error_page"},
	{URI, "uri"},
};

const syntax::request_header_tab_entry_t
syntax::request_header_tab[] = {
	{ACCEPT_CHARSET, "Accept-Charset"},
	{CONTENT_LENGTH, "Content-Length"},
	{AUTHORIZATION, "Authorization"},
	{CONTENT_TYPE, "Content-Type"},
	{DATE, "Date"},
	{HOST, "Host"},
	{REFERER, "Referer"},
	{TRANSFER_ENCODING, "Transfer-Encoding"},
	{USER_AGENT, "User-Agent"},
};

const syntax::answer_header_tab_entry_t
syntax::answer_header_tab[] = {
	{ALLOW, "Allow"},
	{CONTENT_LANGUAGE, "Content-Language"},
	{A_CONTENT_LENGTH, "Content-Length"},
	{CONTENT_LOCATION, "Content-Location"},
	{A_CONTENT_TYPE, "Content-Type"},
	{A_DATE, "Date"},
	{LAST_MODIFIED, "Last-Modified"},
	{LOCATION, "Location"},
	{RETRY_AFTER, "Retry-After"},
	{SERVER, "Server"},
	{A_TRANSFER_ENCODING, "Transfer-Encoding"},
	{WWW_AUTHENTICATE, "WWW-Authenticate"},
};
