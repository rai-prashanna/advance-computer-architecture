#ifndef TEST_COMMON_HPP
#define TEST_COMMON_HPP

#define TEST_EQ(expected, actual, name)                                  \
    {                                                                    \
        if (expected == actual) {                                        \
            std::cout << name << ": SUCCESS\n";                          \
        } else {                                                         \
            std::cout << name << ": FAILED\n"                            \
                      << "\tExpected: " << expected << "\n"              \
                      << "\tActual  : " << actual << "\n"                \
                      << "\tat " << __FILE__ << ":" << __LINE__ << "\n"; \
            return -1;                                                   \
        }                                                                \
    }

#endif // TEST_COMMON_HPP
