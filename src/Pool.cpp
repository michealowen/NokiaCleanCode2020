#include "Pool.hpp"


/*
 * 获取资金池最大值
 */
double pool::get_r_pool() const {
    return r_pool;
}

/*
 * 获取最小资金比例
 */
double pool::get_pool_min_rate() const {
    return pool_min_rate;
}
