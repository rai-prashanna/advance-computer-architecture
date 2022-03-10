#ifndef USER_LOCKS_HPP
#define USER_LOCKS_HPP

#include <atomic>
#include <mutex>

/*******************************************************************************
 *                               Base Lock Class                               *
 ******************************************************************************/

class user_lock {

public:
    virtual void lock(int thread_id) = 0;
    virtual void unlock(int thread_id) = 0;

    virtual ~user_lock(){};
};

/*******************************************************************************
 *                            std::mutex based lock                            *
 ******************************************************************************/

class user_lock_mutex : public user_lock {
private:
    std::mutex m_lock;

public:
    void lock(int thread_id) override;
    void unlock(int thread_id) override;
};

/*******************************************************************************
 *                      Lock based on Dekker's algorithm                       *
 ******************************************************************************/

class user_lock_dekker : public user_lock {
private:
    // TODO: Change the types as necessary
    // NOTE: The lock supports only two threads
    bool m_flag[2];
    bool m_turn;

public:
    user_lock_dekker();

    void lock(int thread_id) override;
    void unlock(int thread_id) override;
};

/*******************************************************************************
 *                            CHL Queue based lock                             *
 ******************************************************************************/

class user_lock_clh : public user_lock {
private:
    using cell = std::atomic<bool>;

    // The lock supports only two threads. Here we allocate the cells we will be
    // using statically. Note that this SHOULD NOT be indexed based on the
    // thread_id. We allocate one cell for each lock and one extra cell to be
    // used as the initial unlocked tail.
    cell m_cells[3];

    // This struct keeps track of the information that is local to each thread
    struct local_l {
        // Pointer to our own cell
        cell *local_cell;
        // Pointer to the previous node in the queue
        cell *previous;
    };

    // The lock supports only two threads. Here we allocate the local
    // information we will be using statically. Each thread can access its local
    // information using m_local[thread_id].
    local_l m_local[2];

    // This pointer stores the tail of the lock
    std::atomic<cell *> m_tail;

public:
    user_lock_clh();

    void lock(int thread_id) override;
    void unlock(int thread_id) override;
};

#endif // USER_LOCKS_HPP
