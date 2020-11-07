#include "Algorithm.hpp"
#include "Manifest.hpp"
#include "Pool.hpp"
#include <algorithm>

// 计算每个城市的总资金（取整）
void cal_city_num_int(std::vector<manifest>& manifest_list, pool& p)
{
	// 分别计算最小分配资金和口罩理想共享资金
	for (auto& m : manifest_list) {
		m.cal_r_min(manifest_list, p);
		m.cal_ideal_shared_SM();
	}
	// 分别计算口罩共享资金
	for (auto& m : manifest_list) {
		m.cal_shared_SM(manifest_list, p);
	}
	// 分别计算消毒液理想共享资金
	for (auto& m : manifest_list) {
		m.cal_ideal_shared_Dis();
	}
	// 分别计算消毒液共享资金
	for (auto& m : manifest_list) {
		m.cal_shared_Dis(manifest_list, p);
	}
	// 分别计算其他物资的最大共享资金
	for (auto& m : manifest_list) {
		m.cal_shared_other(manifest_list, p);
	}
	// 分别计算其他城市的总资金
	for (auto& m : manifest_list) {
		m.cal_sum();
	}
}

// 轮询计算每个城市的总资金
void cal_city_sum(std::vector<manifest>& manifest_list, pool& p)
{
	// 计算总剩余资金
	double r_remain = p.get_r_pool();
	for (auto& m : manifest_list) {
		r_remain -= m.get_sum();
	}
	// 轮询分配资金
	for (int k = 0; k < CITY_NUM && r_remain > 0; ++k) {
		double r_sum_intpart = manifest_list[k].get_sum();
		manifest_list[k].set_sum(
			std::min(
				r_remain + r_sum_intpart,
				manifest_list[k].get_r_max()
			)
		);
		r_remain -= manifest_list[k].get_sum() - r_sum_intpart;
	}
}

