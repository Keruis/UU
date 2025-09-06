#include <iostream>
#include "../Keruis/KString/K_StringCore.h"

int main()
{
    using MyString = Keruis::core::KString::K_core_string<char>;

    // 测试 SSO
    MyString sso_str("abc");
    std::cout << "SSO c_str: " << sso_str.c_str() << "\n";
    std::cout << "SSO length: " << static_cast<int>(sso_str.sso_size()) << "\n";
    std::cout << "SSO category: " << (sso_str.category() == MyString::Category::isSmall ? "Small" : "Large") << "\n";

    // 测试 Large
    const char* long_text = "This is a really long string to trigger Large mode";
    MyString large_str(long_text);
    std::cout << "Large c_str: " << large_str.c_str() << "\n";
    std::cout << "Large length: " << large_str.ds_size() << "\n";
    std::cout << "Large category: " << (large_str.category() == MyString::Category::isLarge ? "Large" : "Small") << "\n";

    // 测试拷贝构造
    MyString copy_str = sso_str;
    std::cout << "Copy c_str: " << copy_str.c_str() << "\n";
    std::cout << "Copy category: " << (copy_str.category() == MyString::Category::isSmall ? "Small" : "Large") << "\n";

    // 测试移动构造
    MyString move_str = std::move(large_str);
    std::cout << "Move c_str: " << move_str.c_str() << "\n";
    std::cout << "Move category: " << (move_str.category() == MyString::Category::isLarge ? "Large" : "Small") << "\n";

    return 0;
}