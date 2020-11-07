/*
 * 算法
 */
#ifndef _ALGORITHM_H
#define _ALGORITHM_H

#include "Manifest.hpp"
#include "Pool.hpp"
#include <vector>

// 计算每个城市的总资金（取整）
void cal_city_num_int(std::vector<manifest>& manifest_list, pool& p);

// 轮询计算每个城市的总资金
void cal_city_sum(std::vector<manifest>& manifest_list, pool& p) ;

#endif // _ALGORITHM_H
