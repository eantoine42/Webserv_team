#include <iostream>
#include <map>
#include <string>

int main(void)
{
	std::map<int, std::string> map;
	map[0] = "lolo";

	std::cout << "At map[0] => " << map[0] << std::endl;

	map[0] = "test";
	std::cout << "At map[0] => " << map[0] << std::endl;

	return (0);
}
