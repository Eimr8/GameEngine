#include "BaseException.h"
#include <sstream>

BaseException::BaseException(const char* file, int line) noexcept
	:
	file(file),
	line(line)
{

}

const char* BaseException::what() const noexcept
{
	std::ostringstream oss;
	oss << getType() << "\n" << getFormattedString();
	buffer = oss.str();

	return buffer.c_str();
}

const char* BaseException::getType() const noexcept
{
	return "Base Exception";
}

const std::string BaseException::getFile() const noexcept
{
	return file;
}

const int BaseException::getLine() const noexcept
{
	return line;
}

std::string BaseException::getFormattedString() const noexcept
{
	std::ostringstream oss;
	oss << "File: " << file << "\n"
		<< "Line: " << line;

	return oss.str();
}
