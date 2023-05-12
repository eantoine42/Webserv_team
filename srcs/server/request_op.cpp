#include "../../includes/request_op.hpp"

int	read_request(std::map<int, ClientInfo>::iterator &it)
{
	int	ret = 0;
	int	len;
	std::string str;

	while (1)
	{
		char	buf[BUFFER_SIZE];
		len = recv(it->first, buf, BUFFER_SIZE - 1, 0);
		if (len <= 0)
			break ;
		ret += len;
		buf[len] = 0;
		str += buf;
	}
	if (ret > 0)
		it->second.add_request(str);
	return ret;
}


