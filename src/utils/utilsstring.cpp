#include "utilsstring.h"

namespace utils {

	std::string remove_spaces(std::string in)
	{
		std::string ret = "";
		for (size_t i = 0; i < in.size(); i++)
		{
			if (!(in[i] == ' ' || in[i] == '\t')) ret += in[i];
		}
		return ret;
	}

	size_t count_char(std::string in, char c)
	{
		size_t count = 0;
		for (size_t i = 0; i < in.size(); i++)
		{
			if (in[i] == c) count++;
		}
		return count;
	}

}
