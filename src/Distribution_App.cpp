#include "Distribution_App.hpp"
#include "IO.hpp"
#include "Pool.hpp"
#include "Manifest.hpp"
#include "Algorithm"

#include <vector>
#include <iostream>

/*
 * 程序入口
 */
void distribution_app::run() const
{
    /* 读取数据  存入data_1, data_2 */
    std::vector<double> data_1(2);
    std::vector<std::vector<std::vector<double>>> data_2(100, std::vector<std::vector<double>>(CITY_NUM, std::vector<double>(4)));
    //std::cout << data_2.size() << "," << data_2[0].size() << "," << data_2[0][0].size() << std::endl;
    read(input_file_name, data_1, data_2);
    
    /* 主逻辑 */
    pool p(data_1[0], data_1[1]);
    std::vector<manifest> manifest_list(CITY_NUM);
    std::vector<std::vector<int>> data_3(data_2.size());
    for (int i = 0; i < data_2.size(); ++i) {
        // 四个城市
        for (int j = 0; j < CITY_NUM; ++j) {
            // 设置状态 r_max, load_sm_prev, load_dis_prev, load_other_prev
            manifest_list[j].set_status(
                data_2[i][j][0],
                data_2[i][j][1],
                data_2[i][j][2],
                data_2[i][j][3]
            );
            manifest_list[i % CITY_NUM].set_O_other(OVER_BOOK_FACTOR_OTHER);
        }
        // 计算每个城市总资金的整数部分
        cal_city_num_int(manifest_list, p);
        // 轮询分配剩余资金
        cal_city_sum(manifest_list, p);
        // 存入data_3
        for (int k = 0; k < CITY_NUM; ++k) {
            data_3[i].push_back(int(manifest_list[k].get_sum()));
            // 更新状态
            manifest_list[k].update_status();
        }
    }

    /* 写入数据 */
    write(output_file_name, data_3);
    //std::cout << "ok" << std::endl;
}
