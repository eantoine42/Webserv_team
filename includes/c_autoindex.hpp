#ifndef C_AUTOINDEX_HPP
# define C_AUTOINDEX_HPP
#include "webserv.hpp"
class autoindex
{
	private:
			std::string     _dirPath;
			std::string     _indexPage;

	public:

			autoindex(const std::string& path);
			autoindex(const autoindex& other);
			~autoindex();
			autoindex&      operator=(const autoindex& other);

			std::string     getIndexPage() const;
			std::string     getDirPath() const;

	private:

        void            _generateIndexPage();
		std::string		_generateHtmlLink(const unsigned char fileType, const std::string& fileName);
		std::string	    _generateHtmlHeader();
        std::string	    _generateHtmlFooter();
		std::string		_getFileLink(const unsigned char fileType, std::string fileName);

		void			_formatCell(std::string* data);
		std::string		_getFileSize(struct stat s);
		std::string		_getFileModTime(struct stat s);
};
#endif