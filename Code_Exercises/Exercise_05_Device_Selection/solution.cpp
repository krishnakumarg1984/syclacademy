#include <CL/sycl.hpp>

// Looks for an Intel GPU
class intel_gpu_selector : public sycl::device_selector {
  public:
    int operator()(const sycl::device& dev) const override {
        if (dev.has(sycl::aspect::gpu)) {
            auto vendorName = dev.get_info<sycl::info::device::vendor>();
            std::cout << "Vendor: " << vendorName << '\n';
            auto deviceName = dev.get_info<sycl::info::device::name>();
            std::cout << "Device: " << deviceName << '\n';
            if (vendorName.find("Intel") != std::string::npos) {
                // std::cout << "Intel GPU is present!\n";
                return 1;
            }
        }
        // std::cout << "NO Intel GPU detected!\n";
        return -1;
    }
};

class scalar_add;
// class hello_world;

int main() {
    int a { 18 };
    int b { 24 };
    int r { 0 };
    std::cout << "The value of the result buffer before the kernel execution is: " << r << '\n';

    try {
        // auto asyncHandler = [&](sycl::exception_list exceptionList)
        // {
        //     for (auto& e : exceptionList) {
        //         std::rethrow_exception(e);
        //     }
        // };

        auto bufA { sycl::buffer { &a, sycl::range { 1 } } };
        auto bufB { sycl::buffer { &b, sycl::range { 1 } } };
        auto bufR { sycl::buffer { &r, sycl::range { 1 } } };

        // auto defaultQueue { sycl::queue() };
        // auto defaultQueue { sycl::queue { asyncHandler } };
        auto defaultQueue { sycl::queue { intel_gpu_selector {} } };
        // auto defaultQueue { sycl::queue { intel_gpu_selector {}, asyncHandler } };

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
