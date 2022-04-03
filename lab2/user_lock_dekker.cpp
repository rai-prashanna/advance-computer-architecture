#include "user_locks.hpp"

user_lock_dekker::user_lock_dekker()
    : user_lock() {
    m_flag[0] = m_flag[1] = false;
    m_turn = false;
}

void user_lock_dekker::lock(int thread_id) {
    // TODO: Implement the lock acquire part of the Dekker algorithm here
    m_flag[thread_id] = true;
    while (m_flag[!thread_id])
    {
        if (m_turn != thread_id)
        {
            m_flag[thread_id] = false;
            while (m_turn != thread_id);
            m_flag[thread_id] = true;
        }
    }
}

void user_lock_dekker::unlock(int thread_id) {
    // TODO: Implement the lock release part of the Dekker algorithm here
    m_turn = !thread_id;
    m_flag[thread_id] = false;
}
