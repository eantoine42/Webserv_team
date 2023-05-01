#include "../../includes/webserv.hpp"




/**
 * @brief 
 * Parse server info in vector<server>
 * server_info is updated with correct info
 * @param std::vector<server> server_info 
 * @param std::string str_config 
 */
static void parseServers(std::vector<server> &server_info, std::string str_config){
	size_t i = 0;
	if (DEBUG_STATUS)
	{
		//DEBUG_COUT("conf file nb lines :" + syntax::intToString(syntax::nb_lines(str_config)));
		//DEBUG_COUT("\n****Server to parse without line server {****  \n\n" + str_config);
	}
	while (i < syntax::nbLines(str_config))
	{
		if (!syntax::isNothing(str_config, i))
		{
			std::string	line = syntax::getLine(str_config, i);
			if (!line.compare(0, 6, "server") && line.size() == 6)
			{
				i++;
				std::string	line = syntax::getLine(str_config, i);
				if (line.compare("{"))
					throw(ConfFileParseError("Invalid Server Header"));
				server temp_server;
				temp_server.setServer( syntax::trimLineToI(str_config, i + 1));
				temp_server.cleanDupServer(server_info);
				server_info.push_back(temp_server);
			}
		}
		i++;
	}

	if (DEBUG_STATUS)
		std::cout<<server_info<<std::endl;
}

/**
 * @brief 
 *	gets the file .conf transformed in a single string 
 *	with #comments removed, whitespaces begin and end removed
 *	and many whitespaces reduced to a space
 *	return : std::string
 * @param std::string const &path 
 * @return std::string 
 */
static std::string getStringConf(std::string const &path)
{
	std::string content;
	std::string line;
	std::vector<std::string> tokens;
	std::ifstream file;
    file.open(path.c_str(), std::ifstream::in);
	if (!file)
    	throw (CantOpenConfFile());
	while (std::getline(file, line))
	{
		std::string temp;

		temp = syntax::trimComments(line);
		temp = syntax::trimWhitespaces(temp);
		content += temp;
		content +="\n";
	}
	if (!content.empty())
		content.erase(content.end() - 1);
//	if (DEBUG_STATUS)
  //  	std::cout << content << std::endl;
	file.close();
	if (!syntax::checkBrackets(content))
		throw ConfFileParseError("Error in the backets");
	return content;
}

/**
 * @brief gets infor from conffile
 *	parse to a vector of server
 * 
 * @param std::string path 
 * @return std::vector<server> 
 */
std::vector<server> parseConfFile(std::string const &path)
{
	std::vector<server> server_list;
	std::string conf_string;
	std::string conf_string_formated = "";
	std::string temp;

	syntax::testPath(path);
	conf_string = getStringConf(path);
	syntax::formatConfFile(conf_string);
	int j = syntax::nbLines(conf_string);
	for (int i = 0; i < j; i++){
		temp = syntax::trimWhitespaces(syntax::getLine(conf_string, i));
		conf_string_formated += temp + syntax::checkChar(temp);
	}
	syntax::formatConfFile(conf_string_formated);
	conf_string_formated.erase(conf_string_formated.size() - 1);
	parseServers(server_list, conf_string_formated);
	return (server_list);
}
