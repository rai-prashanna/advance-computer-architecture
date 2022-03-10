#include "atomic_counters.hpp"

atomic_counter_atomic_incdec::atomic_counter_atomic_incdec()
    : atomic_counter()
    , m_value(0) {
}

int atomic_counter_atomic_incdec::increment() {
    // TODO: Modify this code using atomic fetch_add operations
    int prev_value = m_value;
    m_value = m_value + 1;
    return prev_value;
}

int atomic_counter_atomic_incdec::decrement() {
    // TODO: Modify this code using atomic fetch_sub operations
    int prev_value = m_value;
    m_value = m_value - 1;
    return prev_value;
}

void atomic_counter_atomic_incdec::set(int value) {
    // TODO: Modify this code using atomic store operations
    m_value = value;
}

int atomic_counter_atomic_incdec::get() {
    // TODO: Modify this code using atomic load operations
    return m_value;
}
