#include "IO.hpp"
#include "Manifest.hpp"
#include "Pool.hpp"

#include <iostream>
#include <vector>

/*
 * 读取文件
 */
void read(const char* file_name, std::vector<double>& data_1, std::vector<std::vector<std::vector<double>>>& data_2)
{
	FILE* fp = nullptr;
	fp = fopen(file_name, "rb");
	// 判断文件是否打开失败
	if (fp == nullptr)
		std::cout << "open read file failed" << std::endl;
	// 读取数据，写入data_1
	fscanf(fp, "%lf,%lf", &data_1[0], &data_1[1]);
	// 读取数据，写入data_2
	// 周个数
	unsigned int week_count = 0;
	while (!feof(fp))
	{
		// 换行
		getc(fp);
		getc(fp);
		// 四个城市
		for (int i = 0; i < CITY_NUM; ++i) {
			fscanf(fp, "%lf,%lf,%lf,%lf", 
				&data_2[week_count][i][0], &data_2[week_count][i][1], &data_2[week_count][i][2], &data_2[week_count][i][3]);
			// 换行
			getc(fp);
			getc(fp);
		}
		++week_count;
	}
	data_2.resize(week_count-1);
}

/*
 * 写文件
 */
void write(const char* file_name, std::vector<std::vector<int>>& data_3)
{
	FILE* fp = nullptr;
	fp = fopen(file_name, "wb");
	// 判断文件是否打开失败
	if (fp == nullptr)
		std::cout << "open read file failed" << std::endl;
	for (auto& l : data_3) {
		for (int i = 0; i < CITY_NUM; ++i) {
			fprintf(fp, "%d", l[i]);
			std::cout << l[i];
			if (i < l.size() - 1)
			{
				fputc(',', fp);
				std::cout << ',';
			}
			else {
				fputc('\r', fp);
				fputc('\n', fp);
				std::cout << '\r' << '\n';
			}
		}
	}
	fclose(fp);
}
