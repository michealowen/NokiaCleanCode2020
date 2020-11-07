/*
 * 程序入口
 */

#include "Distribution_App.hpp"

int main() {
    const char* input_file_name = "case-2-input.txt";
    const char* output_file_name = "case-2-output.txt";
    distribution_app app(input_file_name, output_file_name);
    app.run();
    return 0;
}
