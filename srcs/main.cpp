#include "../includes/webserv.hpp"
extern volatile bool g_run;




static int  printUsage(char const *const prog_name) {
    std::cerr << "Usage: " << prog_name << " [-v] [file.conf]" << std::endl;
    return (1);
}

int     main(int argc, const char **argv) {
    std::vector<c_server> serverlist;
	argc = 1;
    if (argv[argc] && !std::strcmp(argv[argc], "-v"))
	{
        DEBUG_START(true);
		argc++;
	}
    if (argv[argc] == NULL)
        argv[argc] = "conf/default.conf";
    else if (argv[argc + 1] != NULL)
        return (printUsage(argv[0]));
    try {
        serverlist = parseConfFile(argv[argc]);
	//	std::cout << serverlist << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Error config: " << e.what() << std::endl;
        return (1);
    }
    return (0);
}
