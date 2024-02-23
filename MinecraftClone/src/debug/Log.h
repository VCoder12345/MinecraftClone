#pragma once

#include <iostream>
#include <string>

class Log {
public:
	template<class... Args>
	void log(Args... args) {
		logNL(args...);
		std::cout << std::endl;
	}


private:

	template<class T, class... Rest>
	void logNL(T t, Rest... rest) {
		logNL(t);
		logNL(rest...);
	}

	template<class T>
	void logNL(T msg) {
		std::cout << msg;
	}
};

