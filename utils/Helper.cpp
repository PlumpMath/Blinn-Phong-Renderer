# include "Helper.h"

namespace Helper
{
	void log_error(const char* msg)
	{
		fprintf(stderr, "Error : %s\n", msg);
		exit(-1);
	}
	void log_error(const std::string msg)
	{
		fprintf(stderr, "Error : %s\n", msg);
		exit(-1);
	}
}