/*
 * Unit Test
 */

#include "../src/Pool.hpp"
#include "../src/Manifest.hpp"

#include <gtest/gtest.h>
#include <vector>
#include <iostream>


class manifest_test : public ::testing::Test {
    protected:
        static void SetUpTestCase() {
            //manifest_list(4);
            std::cout << " SetUpTestCase." << std::endl;
        }

        static void TearDownTestCase() {
            std::cout << " TearDownTestCase." << std::endl;
        }
        
        std::vector<manifest> manifest_list = std::vector<manifest>(4);
        pool p = pool(100, 40);
        //pool p(100, 40);
};

// test manifest::set_status
TEST_F(manifest_test, set_status) {
    // std::vector<manifest> manifest_list(4);
    manifest_list[0].set_status(50, 40, 0, 10);
    manifest_list[1].set_status(60, 20, 20, 10);
    manifest_list[2].set_status(60, 20, 0, 10);
    manifest_list[3].set_status(70, 0, 10, 10);
    ASSERT_DOUBLE_EQ(manifest_list[0].get_r_max(), 50.0);
    ASSERT_DOUBLE_EQ(manifest_list[1].get_r_max(), 60.0);
    ASSERT_DOUBLE_EQ(manifest_list[2].get_r_max(), 60.0);
    ASSERT_DOUBLE_EQ(manifest_list[3].get_r_max(), 70.0);
}

// test manifest::cal_r_min
TEST_F(manifest_test, cal_r_min) {
    //std::vector<manifest> manifest_list(4);
    manifest_list[0].set_status(50, 40, 0, 10);
    manifest_list[1].set_status(60, 20, 20, 10);
    manifest_list[2].set_status(60, 20, 0, 10);
    manifest_list[3].set_status(70, 0, 10, 10);
    manifest_list[0].cal_r_min(manifest_list, p);
    manifest_list[1].cal_r_min(manifest_list, p);
    manifest_list[2].cal_r_min(manifest_list, p);
    manifest_list[3].cal_r_min(manifest_list, p);
    //std::cout << manifest_list[0].get_r_min() << "," << manifest_list[1].get_r_min() << "," << manifest_list[2].get_r_min() << "," << manifest_list[3].get_r_min() << std::endl;
    ASSERT_DOUBLE_EQ(manifest_list[0].get_r_min(), 9.0); 
    ASSERT_DOUBLE_EQ(manifest_list[1].get_r_min(), 10.0); 
    ASSERT_DOUBLE_EQ(manifest_list[2].get_r_min(), 10.0); 
    ASSERT_DOUBLE_EQ(manifest_list[3].get_r_min(), 12.0); 
}

// test manifest::cal_ideal_shared_SM
TEST_F(manifest_test, cal_ideal_shared_SM) {
    manifest_list[0].set_status(50, 40, 0, 10);
    manifest_list[1].set_status(60, 20, 20, 10);
    manifest_list[2].set_status(60, 20, 0, 10);
    manifest_list[3].set_status(70, 0, 10, 10);
    for (auto& m : manifest_list) {
	m.cal_r_min(manifest_list, p);
	m.cal_ideal_shared_SM();
    }
    //std::cout << manifest_list[0].get_ideal_shared_SM() << std::endl;
    //std::cout << manifest_list[1].get_ideal_shared_SM() << std::endl;
    //std::cout << manifest_list[2].get_ideal_shared_SM() << std::endl;
    //std::cout << manifest_list[3].get_ideal_shared_SM() << std::endl;
    ASSERT_DOUBLE_EQ(manifest_list[0].get_ideal_shared_SM(), 41.0); 
    ASSERT_DOUBLE_EQ(manifest_list[1].get_ideal_shared_SM(), 20.0); 
    ASSERT_DOUBLE_EQ(manifest_list[2].get_ideal_shared_SM(), 20.0); 
    ASSERT_DOUBLE_EQ(manifest_list[3].get_ideal_shared_SM(), 0.0); 
}


// test manifest::cal_shared_SM
TEST_F(manifest_test, cal_shared_SM) {
    manifest_list[0].set_status(50, 10, 20, 10);
    manifest_list[1].set_status(50, 10, 20, 10);
    manifest_list[2].set_status(50, 10, 20, 10);
    manifest_list[3].set_status(50, 10, 20, 10);
    for (auto& m : manifest_list) {
	m.cal_r_min(manifest_list, p);
	m.cal_ideal_shared_SM();
    }
    for (auto& m : manifest_list) {
	m.cal_shared_SM(manifest_list, p);
    }
    std::cout << manifest_list[0].get_shared_SM() << std::endl;
    std::cout << manifest_list[1].get_shared_SM() << std::endl;
    std::cout << manifest_list[2].get_shared_SM() << std::endl;
    std::cout << manifest_list[3].get_shared_SM() << std::endl;
    ASSERT_DOUBLE_EQ(manifest_list[0].get_shared_SM(), 5.0); 
    ASSERT_DOUBLE_EQ(manifest_list[1].get_shared_SM(), 5.0); 
    ASSERT_DOUBLE_EQ(manifest_list[2].get_shared_SM(), 5.0); 
    ASSERT_DOUBLE_EQ(manifest_list[3].get_shared_SM(), 5.0); 
}


