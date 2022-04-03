#include "atomic_counters.hpp"

atomic_counter_nosync::atomic_counter_nosync()
    : atomic_counter()
    , m_value(0) {
}

int atomic_counter_nosync::increment() {
    int prev_value = m_value;
    m_value = m_value + 1;
    return prev_value;
}

int atomic_counter_nosync::decrement() {
    int prev_value = m_value;
    m_value = m_value - 1;
    return prev_value;
}

void atomic_counter_nosync::set(int value) {
    m_value = value;
}

int atomic_counter_nosync::get() {
    return m_value;
}
