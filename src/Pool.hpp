/*
 * 资金池类
 */
#ifndef _POOL_H
#define _POOL_H

class pool
{
public:
	pool(const double rp, const double pmr)
		: r_pool(rp), pool_min_rate(pmr)
	{};

	double get_r_pool() const ;

	double get_pool_min_rate() const ;

private:
	// 资金池最大值
	double r_pool;
	// 分配最小资金的比例
	double pool_min_rate;
};

#endif // _POOL_H


