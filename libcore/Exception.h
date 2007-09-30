
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <typeinfo>
#include <string>

namespace Hyperion {
	class Exception : public std::exception {
	public:
		Exception(const std::string &msg)
			: fMessage(msg) {
		}

		virtual const char* what() const throw() {
			return fMessage.c_str();
		}

	private:
		std::string fMessage;
	};
};

#endif // EXCEPTION_H
