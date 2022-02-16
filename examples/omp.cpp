#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

#include <omp.h>

#include <Tracy.hpp>

using namespace std::literals::chrono_literals;

thread_local int tid;

void critical_step() {
    #pragma omp critical
    {
        ZoneScoped
        std::this_thread::sleep_for((tid+1)*2us);
    }
}

void concurrent_step() {
    ZoneScoped
    std::this_thread::sleep_for((tid+1)*1us);
}

int main() {
    using namespace std::chrono_literals;

    #pragma omp parallel
    {
        tid = omp_get_thread_num();
        std::cout << "thread " << tid << "\n";
    }

    // time stepping loop
    for (auto step=0; step<100; ++step) {
        FrameMark
        #pragma omp parallel
        {
            critical_step();
            #pragma omp barrier
            concurrent_step();
        }
    }

    return 0;
}
