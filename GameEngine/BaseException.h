#ifndef _BASEEXCEPTION_H_
#define _BASEEXCEPTION_H_

#include <exception>
#include <string>

class BaseException : public std::exception
{

public:
	BaseException(const char* file, int line) noexcept;
	const char* what() const noexcept override;

	virtual const char* getType() const noexcept;
	const std::string getFile() const noexcept;
	const int getLine() const noexcept;
	std::string getFormattedString() const noexcept;

private:
	std::string file;
	int line;

protected:
	mutable std::string buffer;
};

#endif

