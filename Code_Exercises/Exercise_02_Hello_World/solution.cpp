#define CATCH_CONFIG_MAIN
#include <CL/sycl.hpp>
// #include <catch2/catch.hpp>

class hello_world;

int main() {
    // class hello_world; // show what happens when defined as a local class

    auto defaultQueue { sycl::queue {} };

    defaultQueue
        .submit(
            [&](sycl::handler& cgh)
            {
                auto outputStream { sycl::stream { 128, 128, cgh } };

                cgh.single_task<hello_world>([=]() { outputStream << "Hello World!\n"; });
            })
        .wait();

    return 0;
}

// TEST_CASE("hello_world", "hello_world_solution") {
// auto defaultQueue = sycl::queue {};

// defaultQueue.submit([&](sycl::handler& cgh)
//         {
//             auto os = sycl::stream { 128, 128, cgh };
//
//             cgh.single_task<hello_world>([=]() { os << "Hello World!\n"; });
//         }).wait();

// }
