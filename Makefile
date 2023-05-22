NAME = webserv

CXX = c++
COLOR = \0033[1;35m

# CXXFLAGS = -Wall -Werror -Wextra -std=c++98  -O3 -fsanitize=address
CXXFLAGS = -Wall -Werror -Wextra -std=c++98
#CXXFLAGS = -g -fPIE -std=c++98  -O3  --no-warnings

# DEBUG_PATH = debug/

# DEBUG_FILE = Debugger.cpp

FILE_DESCRIPTOR_SRCS = $(addprefix fileDescriptor/, AFileDescriptor.cpp SocketFd.cpp)

SRCS_PATH = srcs/

SRCS_FILE = main.cpp Server.cpp Request.cpp Debugger.cpp

SRCS_FILE += $(FILE_DESCRIPTOR_SRCS)

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILE))

OBJS = $(SRCS:.cpp=.o)

HEADER_PATH = includes/

HEADER_FILE = Request.hpp Debugger.hpp AFileDescriptor.hpp Server.hpp SocketFd.hpp

HEADER = $(addprefix $(HEADER_PATH), $(HEADER_FILE))

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
