/*
 * 程序入口
 */

#include "Distribution_App.hpp"

#include <iostream>
#include <string>

int main(int argv, char* argc[]) {
    std::string in(argc[1]);
    //std::cout << argv << "," << argc[1] << std::endl;
    distribution_app app(in.c_str());
    app.run();
    return 0;
}
