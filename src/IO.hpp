#ifndef _IO_HPP_
#define _IO_HPP_

#include <vector>

/*
 * 读文件
 */
void read(const char* file_name, std::vector<double>& data_1, std::vector<std::vector<std::vector<double>>>& data_2);

/*
 * 写文件
 */
void write(const char* file_name, std::vector<std::vector<int>>& data_3);

#endif // _IO_HPP_


