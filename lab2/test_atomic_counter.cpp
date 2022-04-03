#include "atomic_counters.hpp"
#include "test_common.hpp"

#include <chrono>
#include <cstring>
#include <iostream>
#include <thread>

void usage(char *argv[]) {
    std::cerr << "Usage: " << argv[0] << " <TEST>\n\n"
              << "Where <TEST> can be:\n"
              << "\tnosync\n"
              << "\tlock\n"
              << "\tatomic_incdec\n"
              << "\tatomic_cas\n";
}

void increment_counter(atomic_counter *counter, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        counter->increment();
    }
}

void decrement_counter(atomic_counter *counter, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        counter->decrement();
    }
}

int main(int argc, char *argv[]) {
    // Check if the user has given us an argument
    if (argc != 2) {
        usage(argv);
        return -1;
    }

    // Find what that argument was and initialize the appropriate test
    std::unique_ptr<atomic_counter> counter = nullptr;
    if (strcmp(argv[1], "nosync") == 0) {
        counter.reset(new atomic_counter_nosync());
    } else if (strcmp(argv[1], "lock") == 0) {
        counter.reset(new atomic_counter_lock());
    } else if (strcmp(argv[1], "atomic_incdec") == 0) {
        counter.reset(new atomic_counter_atomic_incdec());
    } else if (strcmp(argv[1], "atomic_cas") == 0) {
        counter.reset(new atomic_counter_atomic_cas());
    } else {
        std::cerr << "Invalid <TEST> " << argv[1] << "\n";
        usage(argv);
        return -1;
    }

    // Test 1: Single threaded get and set
    std::cout << "\n#1: Singlethreaded tests\n\n";
    counter->set(1);
    auto v = counter->get();
    TEST_EQ(1, v, "counter->set(1)/get()");
    counter->set(2);
    v = counter->get();
    TEST_EQ(2, v, "counter->set(2)/get()");
    v = counter->increment();
    TEST_EQ(2, v, "counter->increment()");
    v = counter->increment();
    TEST_EQ(3, v, "counter->increment()");
    v = counter->decrement();
    TEST_EQ(4, v, "counter->decrement()");
    v = counter->decrement();
    TEST_EQ(3, v, "counter->decrement()");

    // Test 2: multithreaded increment and decrement
    std::cout << "\n#2: Multithreaded tests\n\n";
    const int iterations = 50000000;
    counter->set(0);
    auto start_time = std::chrono::high_resolution_clock::now();
    std::thread inc_thread(increment_counter, counter.get(), iterations);
    std::thread dec_thread(decrement_counter, counter.get(), iterations);

    inc_thread.join();
    dec_thread.join();
    auto end_time = std::chrono::high_resolution_clock::now();
    TEST_EQ(0, counter->get(), "equal inc/dec");
    std::chrono::duration<double> total_time = end_time - start_time;
    const int opss = iterations / total_time.count();
    std::cout << "--> Performance: " << opss << " ops/s\n";

    counter->set(0);
    std::thread inc_thread2(increment_counter, counter.get(), iterations * 2);
    std::thread dec_thread2(decrement_counter, counter.get(), iterations);

    inc_thread2.join();
    dec_thread2.join();
    TEST_EQ(iterations, counter->get(), "unequal inc/dec");

    std::cout << "All " << argv[1] << " tests finished successfully!\n\n";
}
