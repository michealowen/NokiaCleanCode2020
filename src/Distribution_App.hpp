#ifndef _DISTRIBUTION_HPP
#define _DISTRIBUTION_HPP

#include "Algorithm.hpp"
#include "Pool.hpp"
#include "IO.hpp"
#include "Manifest.hpp"

class distribution_app
{
public:
	distribution_app(const char* ifn, const char* ofn)
		:input_file_name(ifn), output_file_name(ofn)
	{}

	/*
	 * 程序运行入口
	 */
	void run() const;
private:
	const char* input_file_name;
	const char* output_file_name;
};

#endif // !_DISTRIBUTION_HPP

