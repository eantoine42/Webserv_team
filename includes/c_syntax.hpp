#ifndef SYNTAX_HPP
# define SYNTAX_HPP
#include "webserv.hpp"
#include <fstream>

# define WHITESPACES " \n\r\t\f\v"


enum method_t {
	GET,
	HEAD,
	POST,
	PUT,
	DELETE,
	CONNECT,
	OPTIONS,
	TRACE,
	TOTAL_METHODS_INSTRUCTIONS
};

enum server_instruction_t {
	S_ROOT,
	LISTEN,
	SERVER_NAME,
	S_ERROR_PAGE,
	S_INDEX,
	S_AUTOINDEX,
	S_CLIENT_MAX_BODY_SIZE,
	S_CGI,
	LOCATION_INSTRUCTION,
	TOTAL_SERVER_INSTRUCTIONS
};

enum location_instruction_t {
	L_ROOT,
	METHODS,
	L_INDEX,
	L_CGI,
	L_AUTOINDEX,
	UPLOAD_DIR,
	RETURN,
	L_CLIENT_MAX_BODY_SIZE,
	L_ERROR_PAGE,
	URI,
	TOTAL_LOCATION_INSTRUCTIONS
};

enum request_header_name_t {
	ACCEPT_CHARSET,
	CONTENT_LENGTH,
	AUTHORIZATION,
	CONTENT_TYPE,
	DATE,
	HOST,
	REFERER,
	TRANSFER_ENCODING,
	USER_AGENT
};

enum answer_header_name_t {
	ALLOW,
	CONTENT_LANGUAGE,
	CONTENT_LENGTH,
	CONTENT_LOCATION,
	CONTENT_TYPE,
	DATE,
	LAST_MODIFIED,
	LOCATION,
	RETRY_AFTER,
	SERVER,
	TRANSFER_ENCODING,
	WWW_AUTHENTICATE
};

class c_syntax {
	public:
		~c_syntax();
		struct method_tab_entry_t 
		{
			method_t		method_index;
			std::string		name;
		};

		struct server_instruction_tab_entry_t
		{
			server_instruction_t	instruction_index;
			std::string 	name;
		};
		struct location_instruction_tab_entry_t 
		{
			location_instruction_t	instruction_index;
			std::string 	name;
		};

		struct request_header_tab_entry_t {
			request_header_name_t	header_index;
			std::string		name;
		};

		struct answer_header_tab_entry_t {
			answer_header_name_t	header_index;
			std::string		name;
		};

		static const method_tab_entry_t					method_tab[];
		static const server_instruction_tab_entry_t 	server_instructions_tab[];
		static const location_instruction_tab_entry_t 	location_instructions_tab[];
		static const request_header_tab_entry_t					request_header_tab[];
		static const answer_header_tab_entry_t					answer_header_tab[];

		static std::string	trimComments(const std::string &str);
		static std::string	trimWhitespaces(const std::string& str);
		static std::string  replaceConsecutiveSpaces(const std::string& str);
		static std::string  getLine(std::string str, size_t n);
		static size_t 		nbLines(std::string &str_config);
		static bool 		isNothing(std::string str, int pos = 0);
		static bool 		checkBrackets(std::string &config_string);
		static void 		testPath(const std::string &path);
		static std::string 	trimLineToI(std::string &str, size_t pos);
		static int			findClosingBracket(std::string str);
		static std::vector<std::string> splitString(std::string str, const std::string &charset = " ");
		static void 		formatConfFile(std::string &conf);
		static char 		checkChar(std::string str);
		static std::string 	intToString(int num);
		static int 	correctInstruction(std::vector<std::string> token, int type);

	private:
		c_syntax();
		c_syntax(const c_syntax& src);
		c_syntax& operator=(const c_syntax& rhs);
};
		
#endif
