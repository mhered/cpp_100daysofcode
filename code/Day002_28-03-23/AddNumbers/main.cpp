#include <iostream>

int addUp(int num) {
    int result=0;

	for(int i=1; i<=num; i++){
        result+=i;
    }
    return result;
}

int main()
{
    std::cout << addUp(1) << std::endl;   // 1
    std::cout << addUp(4) << std::endl;   // 10
    std::cout << addUp(13) << std::endl;  // 91
    std::cout << addUp(600) << std::endl; // 180300

    return 0;
}