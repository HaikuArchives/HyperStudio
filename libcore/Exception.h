/*
 * Copyright 2007 Pier Luigi Fiorini. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Pier Luigi Fiorini, pierluigi.fiorini@gmail.com
 */

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
