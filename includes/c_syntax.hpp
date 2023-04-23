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

		static const method_tab_entry_t					method_tab[];
		static const server_instruction_tab_entry_t 	server_instructions_tab[];
		static const location_instruction_tab_entry_t 	location_instructions_tab[];

		static std::string	trim_comments(const std::string &str);
		static std::string	trim_whitespaces(const std::string& str);
		static std::string  replaceConsecutiveSpaces(const std::string& str);
		static std::string  get_line(std::string str, size_t n);
		static size_t 		nb_lines(std::string &str_config);
		static bool 		is_nothing(std::string str, int pos = 0);
		static bool 		check_brackets(std::string &config_string);
		static void 		test_path(const std::string &path);
		static std::string 	trim_line_to_i(std::string &str, size_t pos);
		static int			find_closing_bracket(std::string str);
		static std::vector<std::string> split_string(std::string str, const std::string &charset = " ");
		static void 		format_conf_file(std::string &conf);
		static char 		check_char(std::string str);
		static std::string 	intToString(int num);

	private:
		c_syntax();
		c_syntax(const c_syntax& src);
		c_syntax& operator=(const c_syntax& rhs);
};
		
#endif
