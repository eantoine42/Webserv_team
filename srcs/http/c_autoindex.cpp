#include "../../includes/c_autoindex.hpp"
#include "../../includes/webserv.hpp"
autoindex::autoindex(const std::string &path) : _dirPath(""),
												_indexPage("")
{
	_dirPath += path;
	_generateIndexPage();
}

autoindex::autoindex(const autoindex &other) : _dirPath(other.getDirPath()),
											   _indexPage(other.getIndexPage())
{
	*this = other;
}

autoindex::~autoindex() {}

autoindex &autoindex::operator=(const autoindex &other)
{
	if (this != &other)
	{
		_dirPath = other.getDirPath();
		_indexPage = other.getIndexPage();
	}
	return (*this);
}

std::string autoindex::_getFileLink(const unsigned char fileType, std::string fileName)
{
	std::string fileLink;

	fileLink = "<a href=\"" + fileName;
	if (fileType == DT_DIR) // file is directory
		fileLink += "/";
	if (fileType == DT_DIR)
		fileLink += "\">📂 ";
	else 	if (fileType == DT_LNK)// file is link
		fileLink += "\">✍ ";
	else
		fileLink += "\">✉ ";
	fileLink += fileName + "</a>";
	_formatCell(&fileLink);
	return (fileLink);
}

// file link + file info
std::string autoindex::_generateHtmlLink(const unsigned char fileType, const std::string &fileName)
{
	struct stat fileInfos;
	std::string link;
	std::string filePath(_dirPath + fileName);

	if (fileName == "." || fileName == ".." || stat(filePath.c_str(), &fileInfos) != 0)
		return ("");
	link = "\t\t\t<tr>\n";
	link += _getFileLink(fileType, fileName);
	link += _getFileModTime(fileInfos);
	link += _getFileSize(fileInfos);
	link += "\t\t\t</tr>\n";
	return (link);
}

void autoindex::_generateIndexPage()
{
	DIR *dir;
	struct dirent *file;

	dir = opendir(_dirPath.c_str());
	if (!dir)
	{
		throw(FatalError("Error opening directory"));
	}
	_indexPage += _generateHtmlHeader();
	for (file = readdir(dir); file != NULL; file = readdir(dir))
	{
		_indexPage += _generateHtmlLink(file->d_type, std::string(file->d_name));
	}
	_indexPage+= _generateHtmlFooter();
	closedir(dir);
}

std::string autoindex::_generateHtmlFooter()
{
	std::string footer;

	footer = "\t\t\t</table>\r\n\
	</body>\r\n\
	</html>\r\n";
	return (footer);
}

std::string autoindex::_generateHtmlHeader()
{
	std::string header;

	header = "<!DOCTYPE html>\n\
    <html>\n\
        <head>\n\
            <title>Autoindex </title>\n\
			<meta charset=\"UTF-8\">\n\
        </head>\n\
		<style>\n\
			h1 {font-family: \"Times New Roman\";}\n\
			table {font-family: \"Courier New\";}\n\
			.border {text-align: start; border-bottom-style: solid; border-width: 1px;}\n\
		</style>\n\
        <body>\n\
        	<h1>Index of " +
			 _dirPath + "</h1>\n\
            <table style=\"width:100%\">\n\
				<colgroup span=\"20\"></colgroup>\n\
				<tr>\n\
					<th class=\"border\">Link</th>\n\
					<th class=\"border\">Modification Time</th>\n\
					<th class=\"border\">Size (in bytes)</th>";
	return (header);
}


void autoindex::_formatCell(std::string *data)
{
	*data = "\t\t\t\t<td class=\"border\">" + *data + "</td>\n";
}

std::string autoindex::_getFileSize(struct stat fileInfos)
{
	std::string size;

	if (fileInfos.st_mode & S_IFDIR) /* Is directory */
		size = "-";
	else
		size = syntax::intToString(fileInfos.st_size);
	_formatCell(&size);
	return (size);
}

std::string autoindex::_getFileModTime(struct stat fileInfos)
{
	std::string time;

	time = syntax::getFormattedDate(fileInfos.st_mtime);
	_formatCell(&time);
	return (time);
}


std::string autoindex::getDirPath() const
{
	return (_dirPath);
}

std::string autoindex::getIndexPage() const
{
	return (_indexPage);
}
