/*
 * 城市详细清单头文件
 */
#ifndef _MENIFEST_HPP_
#define _MENIFEST_HPP_

#define CITY_NUM 4
#define OVER_BOOK_FACTOR_SM_DEFAULT 1
#define OVER_BOOK_FACTOR_DIS_DEFAULT 1
#define OVER_BOOK_FACTOR_OTHER_DEFAULT 1
#define OVER_BOOK_FACTOR_SM 1.5
#define OVER_BOOK_FACTOR_DIS 1.5
#define OVER_BOOK_FACTOR_OTHER 1.5

#include "Pool.hpp"

#include <vector>

class manifest
{
public:

    /*
     * 默认构造函数
     * 上一次的总资金 0 ， 上一次的口罩超额因子 1， 上一次的消毒液超额因子1
     */
    manifest()
        :r_sum_prev(0), O_SM_prev(OVER_BOOK_FACTOR_SM_DEFAULT), O_Dis_prev(OVER_BOOK_FACTOR_DIS_DEFAULT)
    {};
    
    ~manifest()
    {};

    /*
     * 获取本周最大需求
     */
    double get_r_max() const ;

    /*
     * 获取本周最小资金
     */
    double get_r_min() const;

    /*
     * 获取该城市的理想口罩共享资金
     */
    double get_ideal_shared_SM() const ;

    /*
     * 获取该城市的理想消毒液共享资金
     */
    double get_ideal_shared_Dis() const ;

    /*
     * 获取该城市的共享口罩资金
     */
    double get_shared_SM() const ;

    /*
     * 获取该城市的共享消毒液资金
     */
    double get_shared_Dis() const ;

    /*
     * 获取该城市上周其他物资消耗
     */
    double get_load_other_prev() const;

    /*
     * 获取该城市本周的其他物资超额因子
     */
    double get_O_other() const;

    /*
     * 获取分配给该城市的总资金
     */
    double get_sum() const;

    /*
     * 计算该城市本周的最小分配资金
     */
    void cal_r_min(const std::vector<manifest>& manifest_list, const pool& p) ;

    /*
     * 计算口罩理想共有资金
     */
    void cal_ideal_shared_SM() ;

    /*
     * 计算口罩共享资金
     */
    void cal_shared_SM(const std::vector<manifest>& ml, const pool& p) ;

    /*
     * 计算消毒液理想共有资金
     */
    void cal_ideal_shared_Dis() ;

    /*
     * 计算消毒液共享资金
     */
    void cal_shared_Dis(const std::vector<manifest>& ml, const pool& p) ;

    /*
     * 计算其他物资共享资金
     */
    void cal_shared_other(const std::vector<manifest>& ml, const pool& p) ;

    /*
     * 计算分配给该城市的总资金
     */
    void cal_sum();

    /*
     * 设置分配给该城市的总资金
     */
    void set_sum(const double s) ;

    /*
     * 通过输入设置状态
     * r_max, load_sm_prev, load_dis_prev, load_other_prev
     */
    void set_status(const double r_max, const double lsp, const double ldp, const double lop);

    /*
     * 设置本周其他物资超额因子
     */
    void set_O_other(const double ot);

    /*
     * 更新状态
     * 当前周的状态变为前一周的状态
     */
    void update_status();

private:

    // 上周口罩的实际消耗(输入)
    double load_SM_prev;
    // 上周口罩超额因子
    double O_SM_prev;
    // 本周口罩超额因子
    double O_SM;
    // 本周口罩专有资金
    double r_dedicated_SM;
    // 本周口罩理想共享资金
    double r_ideal_shared_SM;
    // 本周口罩共享资金
    double r_shared_SM;

    // 上周消毒液的实际消耗(输入)
    double load_Dis_prev;
    // 上周消毒液超额因子
    double O_Dis_prev;
    // 本周消毒液超额因子
    double O_Dis;
    // 本周消毒液专有资金
    double r_dedicated_Dis;
    // 本周消毒液理想共享资金
    double r_ideal_shared_Dis;
    // 本周消毒液共享资金
    double r_shared_Dis;

    // 上周其他物资的实际消耗(输入)
    double load_other_prev;
    // 其他物资最大共享资金
    double r_max_shared_other;
    // 其他物资超额因子
    double O_other;
    // 其他物资共享资金
    double r_shared_other;

    // 本周最大需求(输入)
    double r_max;
    // 本周最小资金
    double r_min;
    // 上周分配的总资金
    double r_sum_prev;
    // 本周分配的总资金
    double r_sum;

    /*
     * 计算该城市本周的口罩超额因子
     */
    void cal_OSM();

    /*
     * 计算口罩专有资金
     */
    void cal_dedicated_SM();

    /*
     * 计算本周的消毒液超额因子
     */
    void cal_ODis();

    /*
     * 计算消毒液专有资金
     */
    void cal_dedicated_Dis();

    /*
     * 计算其他物资最大共享资金
     */
    void cal_max_shared_other();
};

#endif // _MENIFEST_HPP_

