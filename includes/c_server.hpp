#ifndef C_SERVER_HPP
# define C_SERVER_HPP

#include "c_location.hpp"
class location;

class   server {

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
		std::vector<location>		_location;


		/*
		** Server setters
		*/
		void						setCgi(std::vector<std::string> token);
		void						setPort(std::vector<std::string> token);
		void						setRoot(std::vector<std::string> token);
		void						setIp(std::vector<std::string> token);
		void						setIndex(std::vector<std::string> token);
		void						setAutoindex(std::vector<std::string> token);
		void						setName(std::vector<std::string> token);
		void						setError(std::vector<std::string> token);
		void						setClientBodySize(std::vector<std::string> token);
		int							skipLocationBlock(std::string str, int count);
		void						parseServer(std::string str, int &count);
		int							getLocationBloc(std::string str, int &count);
		typedef void (server::*server_func)(std::vector<std::string> );
		void init_vector_server_fct(std::vector<server_func> &funcs);
	

	public:
		server(void);
		server(server const &src);
		server &operator=(server const &src);
		virtual ~server();

		void						addLocation(std::string str, int &count, int &server_ct);

		/*
		** Server getters
		*/
		int							const &getPort() const;
		std::string					const &getRoot() const;
		std::string					const &getName() const;
		std::string					const &getIp() const;
		std::string					const &getError() const;
		std::string					const &getIndex() const;
		bool						const &getAutoindex() const;
		int							const &getClientBodySize() const;
		std::vector<location>		const &getLocation() const;
		std::map<std::string, std::string>	const &getCgi() const;
		
		void						setServer(const std::string &str);
		void 						cleanNames(server &serv2);
		void 						cleanDupServer(std::vector<server> serverInfo);

		
};

std::ostream    &operator<<(std::ostream &o, server const &i);

std::ostream    &operator<<(std::ostream &o, std::vector<server>  const &srv);
#endif
