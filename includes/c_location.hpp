#ifndef location_HPP
# define location_HPP

#include "webserv.hpp"



class   location {

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
		long int							_client_body_size;
		std::string							_error_pages;
		std::string							_uri;
		

		/*
		** location setters
		*/
		void	setUri(std::vector<std::string> token);
		void	setAutoindex(std::vector<std::string> token);
		void	setIndex(std::vector<std::string> token);
		void	setReturn(std::vector<std::string> token);
		void	setAllowMethod(std::vector<std::string> token);
		void	setRoot(std::vector<std::string> token);
		void	setUploadDir(std::vector<std::string> token);
		void	setCgi(std::vector<std::string> token);
		void	setClientBodySize(std::vector<std::string> token);
		void	setErrorPages(std::vector<std::string> token);
		typedef void (location::*loc_func)(std::vector<std::string> );
		void init_vector_loc_fct(std::vector<loc_func> &funcs);

	public:
		location(int port, int loc_index, std::map<std::string, std::string>	cgi, bool autoindex, std::string index, std::string root, int client_body_size);
		location(const location &copy);
		location &operator=(const location &copy);
		~location();
		void	setLocation(const std::string &str,  int &count);
		void	parseLocation(std::string &line);
		
		/*
		** location getters
		*/
		int									const &getLocIndex() const;
		int									const &getPort() const;
		std::string							const &getUri() const;
		bool								const &getAutoindex() const;
		std::string							const &getIndex() const;
		std::string							const &getReturn() const;
		std::vector<std::string>			const &getAllowMethod() const;
		std::string							const &getRoot() const;
		std::string							const &getUploadDir() const;
		long int							const &getClientBodySize() const;
		std::string							const &getError() const;
		std::map<std::string, std::string>	const &getCgi() const;
};



std::ostream    &operator<<(std::ostream &o, location const &i);
#endif
