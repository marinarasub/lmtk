#include "file.h"

namespace utils{

	// gets file extension without dot
	std::string file_extension(std::string path)
	{
		size_t dot_pos = path.find_last_of(".");
		if (dot_pos == std::string::npos) return "";
		return path.substr(dot_pos + 1, path.length() - (dot_pos + 1));
	}

}