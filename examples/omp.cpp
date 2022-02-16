#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

#include <omp.h>

#include <tracey/tracey.hpp>

int main() {
    using namespace std::chrono_literals;
    tracey::context ctx;

    #pragma omp parallel
    {
        std::cout << "thread " << omp_get_thread_num() << "\n";
    }

    auto id_foo = ctx.id("foo");
    auto id_foo1 = ctx.id("foo-1");
    auto id_foo2 = ctx.id("foo-2");
    auto id_run = ctx.id("run");
    #pragma omp parallel
    {
        #pragma omp critical
        {
            ctx.begin_event(id_foo);
            auto tid = omp_get_thread_num();

            ctx.begin_event(id_foo1);
            std::this_thread::sleep_for((tid+1)*1ms);
            ctx.end_event();

            ctx.begin_event(id_foo2);
            std::this_thread::sleep_for((tid+1)*2ms);
            ctx.end_event();

            ctx.end_event();
        }
    }

    #pragma omp parallel
    {
        ctx.begin_event(id_run);
        auto tid = omp_get_thread_num();
        std::this_thread::sleep_for((tid+1)*1ms);
        ctx.end_event();
    }

    auto fid = std::ofstream("omp-prof.json");
    ctx.to_json(fid);
    fid.close();

    return 0;
}
