#ifndef C_SERVER_HPP
# define C_SERVER_HPP

#include "c_location.hpp"
class c_location;

class   c_server {

		private:
		/*
		** Server attributes
		*/
		std::string					_root;
		int							_port;
		std::string					_server_name;
		std::string					_IP;
		std::string					_error_pages;
		std::string					_index;
		bool						_autoindex;
		int							_client_body_size;
		std::map<std::string, std::string>	_cgi;
		std::vector<c_location>		_location;


		/*
		** Server setters
		*/
		void						set_cgi(std::vector<std::string> token);
		void						set_port(std::vector<std::string> token);
		void						set_root(std::vector<std::string> token);
		void						set_IP(std::vector<std::string> token);
		void						set_index(std::vector<std::string> token);
		void						set_autoindex(std::vector<std::string> token);
		void						set_name(std::vector<std::string> token);
		void						set_error(std::vector<std::string> token);
		void						set_client_body_size(std::vector<std::string> token);
		int 						correct_server_instruction(std::vector<std::string> token);
		int							skip_location_block(std::string str, int count);
		void						parse_server(std::string str, int &count);
		int							get_location_bloc(std::string str, int &count);

	

	public:
		c_server(void);
		c_server(c_server const &src);
		c_server &operator=(c_server const &src);
		virtual ~c_server();

		void						add_location(std::string str, int &count, int &server_ct);

		/*
		** Server getters
		*/
		int							const &get_port() const;
		std::string					const &get_root() const;
		std::string					const &get_name() const;
		std::string					const &get_IP() const;
		std::string					const &get_error() const;
		std::string					const &get_index() const;
		bool						const &get_autoindex() const;
		int							const &get_client_body_size() const;
		std::vector<c_location>		const &get_location() const;
		std::map<std::string, std::string>	const &get_cgi() const;
		
		void						set_server(const std::string &str);
		void 						clean_names(c_server &serv2);
		void 						clean_dup_server(std::vector<c_server> server_info);

		
};

std::ostream    &operator<<(std::ostream &o, c_server const &i);

std::ostream    &operator<<(std::ostream &o, std::vector<c_server>  const &srv);
#endif
