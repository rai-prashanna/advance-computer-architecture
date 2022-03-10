#include "test_common.hpp"
#include "user_locks.hpp"

#include <chrono>
#include <cstring>
#include <iostream>
#include <thread>

void usage(char *argv[]) {
    std::cerr << "Usage: " << argv[0] << " <TEST>\n\n"
              << "Where <TEST> can be:\n"
              << "\tmutex\n"
              << "\tdekker\n"
              << "\tclh\n";
}

void increment_value(user_lock *lock, int tid, int *v, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        lock->lock(tid);
        *v += 1;
        lock->unlock(tid);
    }
}

void decrement_value(user_lock *lock, int tid, int *v, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        lock->lock(tid);
        *v -= 1;
        lock->unlock(tid);
    }
}

int main(int argc, char *argv[]) {
    // Check if the user has given us an argument
    if (argc != 2) {
        usage(argv);
        return -1;
    }

    // Find what that argument was and initialize the appropriate test
    std::unique_ptr<user_lock> lock = nullptr;
    if (strcmp(argv[1], "mutex") == 0) {
        lock.reset(new user_lock_mutex());
    } else if (strcmp(argv[1], "dekker") == 0) {
        lock.reset(new user_lock_dekker());
    } else if (strcmp(argv[1], "clh") == 0) {
        lock.reset(new user_lock_clh());
    } else {
        std::cerr << "Invalid <TEST> " << argv[1] << "\n";
        usage(argv);
        return -1;
    }

    // Test 1: multithreaded increment and decrement
    std::cout << "\n#1: Multithreaded tests\n\n";
    const int iterations = 50000000;
    int value = 0;
    auto start_time = std::chrono::high_resolution_clock::now();
    std::thread inc_thread(increment_value, lock.get(), 0, &value, iterations);
    std::thread dec_thread(decrement_value, lock.get(), 1, &value, iterations);

    inc_thread.join();
    dec_thread.join();
    auto end_time = std::chrono::high_resolution_clock::now();
    TEST_EQ(0, value, "equal inc/dec");
    std::chrono::duration<double> total_time = end_time - start_time;
    const int opss = iterations / total_time.count();
    std::cout << "--> Performance: " << opss << " ops/s\n";

    value = 0;
    std::thread inc_thread2(increment_value, lock.get(), 0, &value,
                            iterations * 2);
    std::thread dec_thread2(decrement_value, lock.get(), 1, &value, iterations);

    inc_thread2.join();
    dec_thread2.join();
    TEST_EQ(iterations, value, "unequal inc/dec");

    std::cout << "All " << argv[1] << " tests finished successfully!\n\n";
}
