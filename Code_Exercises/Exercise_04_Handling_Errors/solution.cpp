#include <CL/sycl.hpp>

class scalar_add;

int main() {
    int a { 18 };
    int b { 24 };
    int r { 0 };
    std::cout << "The value of the result buffer before the kernel execution is: " << r << '\n';

    try {
        auto asyncHandler = [&](sycl::exception_list exceptionList)
        {
            for (auto& e : exceptionList) {
                std::rethrow_exception(e);
            }
        };

        auto bufA { sycl::buffer { &a, sycl::range { 1 } } };
        auto bufB { sycl::buffer { &b, sycl::range { 1 } } };
        auto bufR { sycl::buffer { &r, sycl::range { 1 } } };

        // auto defaultQueue { sycl::queue() };
        auto defaultQueue { sycl::queue { asyncHandler } };
        defaultQueue
            .submit(
                [&](sycl::handler& cgh)
                {
                    auto accA { sycl::accessor { bufA, cgh, sycl::read_only } };
                    auto accB { sycl::accessor { bufB, cgh, sycl::read_only } };
                    auto accR { sycl::accessor { bufR, cgh, sycl::write_only } };

                    cgh.single_task<scalar_add>([=]() { accR[0] = accA[0] + accB[0]; });
                })
            .wait();

        defaultQueue.throw_asynchronous();
    } catch (const sycl::exception& e) {
        std::cout << "SYCL asynchronous exception caught: " << e.what() << '\n';
    } catch (...) {
        std::cout << "SYCL synchronous exception caught!" << '\n';
    }

    std::cout << "The value of the result buffer after kernel execution is: " << r << '\n';

    return 0;
}
