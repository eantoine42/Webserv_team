#ifndef CGI_HPP
#define CGI_HPP

#include <string>

class Cgi
{
	public:
		// Cannonical form
		Cgi(void);
		~Cgi(void);
		Cgi(Cgi const & copy);
		Cgi &	operator=(Cgi const & rhs);		
		
		// Constructors
		Cgi(const std::string pathBin, const std::string extension);

		// Members methods
		void execScript(const std::string filename);

	private:
		const std::string	_cgiBin;
		const std::string	_extension;

		bool isValidExtension(const std::string filename);


};

#endif
