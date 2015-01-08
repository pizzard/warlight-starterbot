#ifndef STRING_MANIPULATION_H_INCLUDED
#define STRING_MANIPULATION_H_INCLUDED

// stl
#include <vector>
#include <string>
#include <sstream>

namespace string {

inline std::vector<std::string> &split(std::vector<std::string> &elems, const std::string &s, char delim = ',')
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		if (!item.empty())
		elems.push_back(item);
	}
	return elems;
}

inline std::string join(const std::vector<std::string> &elems,  char delim = ',')
{
	std::string res = elems.front();
	for(std::vector<std::string>::const_iterator it = ++elems.begin(); it != elems.end(); ++it)
	{
		res += delim + *it;
	}
	return res;
}

}
#endif
