#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

void func(double x, int nsecs);

int main(int argc, char **argv) {
    const int secs = std::atoi(argv[1]);
    std::thread th1(&func, 100, secs);
    std::thread th2(&func, 200, secs);
    std::thread th3(&func, 300, secs);
    th1.join();
    std::cout << "Outside thread" << std::endl;
    th2.join();
    th3.join();
    return 0;
}

void func(double x, int nsecs) {
    std::cout << "Inside thread " << x << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds(nsecs)); // make this sleep, does not consume a lot of resources
    for (int ii = 0; ii < 100000000; ++ii) {
        x += std::fabs(x*std::sin(x) + std::sqrt(x)/3.4455)/(ii+1);
    }
    std::cout << "Getting out of thread " << x << std::endl;
}
