NAME = webserv

CXX = c++
COLOR = \0033[1;35m

CXXFLAGS = -Wall -Werror -Wextra -std=c++98 -O3 -fsanitize=address
# CXXFLAGS = -Wall -Werror -Wextra -O3
#CXXFLAGS = -g -fPIE -std=c++98  -O3  --no-warnings


# PARSE_CONF_PATH = parse_conf/
#
# PARSE_CONF_FILE = c_location.cpp c_server.cpp parse_conf.cpp c_syntax.cpp
#
# DEBUG_PATH = debug/
#
# DEBUG_FILE = Debugger.cpp
#
# HTTP_PATH = http/
#
# HTTP_FILE = response.cpp
#
# SRCS_PATH = srcs/
#
# SRCS_FILE = main.cpp utils.cpp
#
# SRCS_FILE += $(addprefix $(PARSE_CONF_PATH), $(PARSE_CONF_FILE))
# SRCS_FILE += $(addprefix $(DEBUG_PATH), $(DEBUG_FILE))
#
# SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILE))
#
SRCS = main.cpp Server.cpp AHTTPMessage.cpp Request.cpp Response.cpp Connection.cpp

OBJS = $(SRCS:.cpp=.o)

# HEADER_FILE = webserv.hpp c_debugger.hpp c_location.hpp c_server.hpp \
#  parse_conf.hpp exception.hpp utils.hpp c_syntax.hpp response.hpp
HEADER = Server.hpp AHTTPMessage.hpp Request.hpp Response.cpp Connection.hpp

HEADER_PATH = ./

# HEADER = $(addprefix $(HEADER_PATH), $(HEADER_FILE))

all : $(NAME)
	echo "Compile OK"

$(NAME) : $(OBJS)
	@echo "$(COLOR)Creating :\t\0033[0;32m$@\0033[1;37m" 
	$(CXX) $(CXXFLAGS) -I $(HEADER_PATH) $(OBJS) -o $(NAME)
	@echo "$(COLOR)Created :\t\0033[0;32m$@\0033[1;37m"

%.o : %.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) -I $(HEADER_PATH) -c $< -o $@

clean :
	rm -rf $(OBJS)
	@echo "$(COLOR)Objects \033[100D\033[40C\0033[1;31m[Removed]\0033[1;37m"

fclean : clean
	rm -rf $(NAME)
	@echo "$(COLOR)$(NAME) \033[100D\033[40C\0033[1;31m[Removed]\0033[1;37m"


re : fclean all

.PHONY: all clean fclean re

.SILENT :

$(OBJS): $(MAKEFILE_LIST)
