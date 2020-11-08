#include "Manifest.hpp"

#include <math.h>
#include <algorithm>

/*
 * 获取本周最大需求
 */
double manifest::get_r_max() const{
    return r_max;
}

/*
 * 获取本周最小资金
 */
double manifest::get_r_min() const 
{
    return r_min;
}

/*
 * 获取该城市的理想口罩共享资金
 */
double manifest::get_ideal_shared_SM() const 
{
    return r_ideal_shared_SM;
}

/*
 * 获取该城市的理想消毒液共享资金
 */
double manifest::get_ideal_shared_Dis() const
{
    return r_ideal_shared_Dis;
}

/*
 * 获取该城市的共享口罩资金
 */
double manifest::get_shared_SM() const 
{
    return r_shared_SM;
}

/*
 * 获取该城市的共享消毒液资金
 */
double manifest::get_shared_Dis() const 
{
    return r_shared_Dis;
}

/*
 * 获取该城市上周其他物资消耗
 */
double manifest::get_load_other_prev() const
{
    return load_other_prev;
}

/*
 * 获取该城市本周的其他物资超额因子
 */
double manifest::get_O_other() const
{
    return O_other;
}

/*
 * 获取分配给该城市的总资金
 */
double manifest::get_sum() const
{
    return r_sum;
}

/*
 * 计算该城市的最小分配资金
 */
void manifest::cal_r_min(const std::vector<manifest>& ml, const pool& p)
{
    // 计算所有城市最大分配的和
    double sum_r_max = 0;
    for (auto& m : ml) {
        sum_r_max += m.get_r_max();
    }
    r_min = std::min(
        ceil(p.get_r_pool() * p.get_pool_min_rate() / 100 * r_max / sum_r_max),
        r_max
    );
}

/*
 * 计算本周的口罩超额因子
 */
void manifest::cal_OSM() {
    if (load_SM_prev * O_SM_prev < r_sum_prev)
        O_SM = 1;
    else
        O_SM = 1.5;
}

/*
 * 计算口罩专有资金
 */
void manifest::cal_dedicated_SM()
{
    cal_OSM();
    r_dedicated_SM =  std::min(O_SM * load_SM_prev, r_min);
}

/*
 * 计算口罩理想共享资金
 */
void manifest::cal_ideal_shared_SM()
{
    cal_dedicated_SM();
    r_ideal_shared_SM = std::max(
        std::min(
            O_SM * load_SM_prev - r_dedicated_SM,
            r_max - r_min),
        0.0);
}

/*
 * 计算口罩共享资金
 */
void manifest::cal_shared_SM(const std::vector<manifest>& ml, const pool& p)
{
    // 计算所有城市的口罩理想共享资金之和
    double sum_ideal_shared_SM = 0;
    for (auto& m : ml) {
        sum_ideal_shared_SM += m.get_ideal_shared_SM();
    }
    // 计算所有城市的最小资金之和
    double sum_r_min = 0;
    for (auto& m : ml) {
        sum_r_min += m.get_r_min();
    }
    r_shared_SM =  std::min(
        r_ideal_shared_SM, 
        r_ideal_shared_SM / sum_ideal_shared_SM * (p.get_r_pool() - sum_r_min)
    );
}

/*
 * 计算本周的消毒液超额因子
 * 公式
 */
void manifest::cal_ODis() {
    if (load_Dis_prev * O_Dis_prev < r_sum_prev)
        O_Dis = 1;
    else
        O_Dis = 1.5;
}

/*
 * 计算消毒液专有资金
 */
void manifest::cal_dedicated_Dis()
{
    r_dedicated_Dis = std::min(
        O_Dis * load_Dis_prev,
        r_min - r_dedicated_SM
    );
}

/*
 * 计算消毒液理想共有资金
 */
void manifest::cal_ideal_shared_Dis()
{
    cal_ODis();
    cal_dedicated_Dis();
    r_ideal_shared_Dis = std::max(
        std::min(
            O_Dis * load_Dis_prev - r_dedicated_Dis,
            r_max - r_min - r_shared_SM),
        0.0);
}

/*
 * 计算消毒液共享资金
 */
void manifest::cal_shared_Dis(const std::vector<manifest>& ml, const pool& p)
{
    // 计算所有城市的消毒液理想共享资金之和
    double sum_ideal_shared_Dis = 0;
    for (auto& m : ml) {
        sum_ideal_shared_Dis += m.get_ideal_shared_Dis();
    }
    // 计算所有城市的最小资金之和
    double sum_r_min = 0;
    for (auto& m : ml) {
        sum_r_min += m.get_r_min();
    }
    // 计算所有城市的口罩共享资金之和
    double sum_shared_SM = 0;
    for (auto& m : ml) {
        sum_shared_SM += m.get_shared_SM();
    }
    // 公式部分
    r_shared_Dis = std::min(
        r_ideal_shared_Dis,
        r_ideal_shared_Dis / sum_ideal_shared_Dis * (p.get_r_pool() - sum_r_min - sum_shared_SM)
    );
}

/*
 * 计算其他物资最大共享资金
 */
void manifest::cal_max_shared_other() 
{
    r_max_shared_other = r_max - r_min - r_shared_SM - r_shared_Dis;
}

/*
 * 计算其他物资共享资金
 */
void manifest::cal_shared_other(const std::vector<manifest>& ml, const pool& p)
{
    cal_max_shared_other();
    // 计算所有城市的其他物资乘超额因子之和
    double sum_shared_other = 0;
    for (auto& m : ml) {
        sum_shared_other += m.get_load_other_prev() * m.get_O_other();
    }
    // 计算所有城市的最小资金之和
    double sum_r_min = 0;
    for (auto& m : ml) {
        sum_r_min += m.get_r_min();
    }
    // 计算所有城市的口罩共享资金之和
    double sum_shared_SM = 0;
    for (auto& m : ml) {
        sum_shared_SM += m.get_shared_SM();
    }
    // 计算所有城市的消毒液共享资金之和
    double sum_shared_Dis = 0;
    for (auto& m : ml) {
        sum_shared_Dis += m.get_shared_Dis();
    }

    // 公式部分
    r_shared_other = std::min(
        r_max_shared_other, 
        load_other_prev * O_other / sum_shared_other * (p.get_r_pool() - sum_r_min - sum_shared_SM - sum_shared_Dis)
    );
}

/*
 * 计算分配给该城市的总资金
 */
void manifest::cal_sum()
{
    r_sum = floor(r_min + r_shared_SM + r_shared_Dis + r_shared_other);
}

/*
 * 设置分配给该城市的总资金
 */
void manifest::set_sum(const double s)
{
    r_sum = s;
}

/*
 * 通过输入设置状态
 * r_max, load_sm_prev, load_dis_prev, load_other_prev
 */
void manifest::set_status(const double rm, const double lsp, const double ldp, const double lop)
{
    r_max = rm;
    load_SM_prev = lsp;
    load_Dis_prev = ldp;
    load_other_prev = lop;
    O_other = OVER_BOOK_FACTOR_OTHER_DEFAULT;
}

/*
 * 设置本周其他物资超额因子
 */
void manifest::set_O_other(const double ot)
{
    O_other = ot;
}

/*
 * 更新状态
 * 当前周的状态变为前一周的状态
 */
void manifest::update_status()
{
    O_SM_prev = O_SM;
    O_Dis_prev = O_Dis;
    r_sum_prev = r_sum;
}
