#include <iostream>
#include <thread>

void func(int x);

int main(int argc, char **argv) {
    std::thread th1(&func, 100);
    std::thread th2(&func, 200);
    th1.join();
    std::cout << "Outside thread" << std::endl;
    th2.join();
    return 0;
}

void func(int x) {
    std::cout << "Inside thread " << x << std::endl;
    std::thread::id this_id = std::this_thread::get_id();
    std::cout << "This is thread_id: " << this_id << std::endl;
}
