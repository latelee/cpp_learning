#include <cstdlib>
#include <cstdio>
#include <iostream>

int main(void)
{
    char* p1 = "192.168.1.10";
    std::string p = p1;
    p += std::to_string(123); // 这种形式方便累加字符，to_string是将数字转换成String
    std::cout<< p << std::endl;
    return 0;
}
