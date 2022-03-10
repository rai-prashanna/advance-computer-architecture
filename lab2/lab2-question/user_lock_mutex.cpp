#include "user_locks.hpp"

void user_lock_mutex::lock(int) {
    m_lock.lock();
}

void user_lock_mutex::unlock(int) {
    m_lock.unlock();
}
