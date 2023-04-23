#ifndef C_LOCATION_HPP
# define C_LOCATION_HPP

#include "webserv.hpp"



class   c_location {

		private:
		/*
		** Location attributes
		*/
		int									_port;
		int									_loc_index;
		std::string							_root;
		std::vector<std::string>			_allow_method;
		std::string							_index;
		std::map<std::string, std::string>	_cgi;
		bool								_autoindex;
		std::string							_upload_dir;
		std::string							_return;
		int									_client_body_size;
		std::string							_error_pages;
		std::string							_uri;
		

		/*
		** c_location setters
		*/
		void	set_uri(std::vector<std::string> token);
		void	set_autoindex(std::vector<std::string> token);
		void	set_index(std::vector<std::string> token);
		void	set_return(std::vector<std::string> token);
		void	set_allow_method(std::vector<std::string> token);
		void	set_root(std::vector<std::string> token);
		void	set_upload_dir(std::vector<std::string> token);
		void	set_cgi(std::vector<std::string> token);
		void	set_client_body_size(std::vector<std::string> token);
		void	set_error_pages(std::vector<std::string> token);
		int 	correct_location_instruction(std::vector<std::string> token);
		int 	correct_method_instruction(std::vector<std::string> token);

	public:
		c_location(int port, int loc_index, std::map<std::string, std::string>	cgi, bool autoindex, std::string index, std::string root, int client_body_size);
		c_location(const c_location &copy);
		c_location &operator=(const c_location &copy);
		~c_location();
		void	set_location(const std::string &str,  int &count);
		void	parse_location(std::string &line);
		
		/*
		** c_location getters
		*/
		int									const &get_loc_index() const;
		int									const &get_port() const;
		std::string							const &get_uri() const;
		bool								const &get_autoindex() const;
		std::string							const &get_index() const;
		std::string							const &get_return() const;
		std::vector<std::string>			const &get_allow_method() const;
		std::string							const &get_root() const;
		std::string							const &get_upload_dir() const;
		int									const &get_client_body_size() const;
		std::string							const &get_error() const;
		std::map<std::string, std::string>	const &get_cgi() const;
};



std::ostream    &operator<<(std::ostream &o, c_location const &i);
#endif
