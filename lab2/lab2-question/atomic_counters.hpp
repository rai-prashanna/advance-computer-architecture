#ifndef ATOMIC_COUNTERS_HPP
#define ATOMIC_COUNTERS_HPP

#include <atomic>
#include <mutex>

/*******************************************************************************
 *                             Base Abstract Class                             *
 ******************************************************************************/

class atomic_counter {
public:
    /**
     * This function atomically increments the counter and returns the value
     * just before it was incremented. E.g.:
     *
     * atomic_counter.set(1);
     * prev = atomic_counter.increment();
     * prev == 1;
     * atomic_counter.get() == 2;
     *
     * Arguments:
     *	No arguments
     *
     * Returns:
     *	The value of the counter just before it was incremented.
     */
    virtual int increment() = 0;

    /**
     * This function atomically decrements the counter and returns the value
     * just before it was decremented. E.g.:
     *
     * atomic_counter.set(1);
     * prev = atomic_counter.decrement();
     * prev == 1;
     * atomic_counter.get() == 0;
     *
     * Arguments:
     *	No arguments
     *
     * Returns:
     *	The value of the counter just before it was decremented.
     */
    virtual int decrement() = 0;

    /**
     * This function atomically sets the counter to the given value. E.g.:
     *
     * atomic_counter.set(2);
     * atomic_counter.get() == 2;
     *
     * Arguments:
     *	value: The value to set the counter to.
     *
     * Returns:
     *	Nothing
     */
    virtual void set(int value) = 0;

    /**
     * This function atomically gets the counter value.
     *
     * Arguments:
     *	No arguments
     *
     * Returns:
     *	The value of the counter (m_value).
     */
    virtual int get() = 0;

    virtual ~atomic_counter(){};
};

/*******************************************************************************
 *                             No Synchronization                              *
 ******************************************************************************/

class atomic_counter_nosync : public atomic_counter {
private:
    int m_value;

public:
    atomic_counter_nosync();

    int increment() override;
    int decrement() override;

    void set(int value) override;
    int get() override;
};

/*******************************************************************************
 *                         Lock-based Synchronization                          *
 ******************************************************************************/

class atomic_counter_lock : public atomic_counter {
private:
    int m_value;
    std::mutex m_lock;

public:
    atomic_counter_lock();

    int increment() override;
    int decrement() override;

    void set(int value) override;
    int get() override;
};

/*******************************************************************************
 *              Atomic Increment/Decrement-based Synchronization               *
 ******************************************************************************/

class atomic_counter_atomic_incdec : public atomic_counter {
private:
    int m_value; // TODO: Change type

public:
    atomic_counter_atomic_incdec();

    int increment() override;
    int decrement() override;

    void set(int value) override;
    int get() override;
};

/*******************************************************************************
 *                      Atomic CAS-based Synchronization                       *
 ******************************************************************************/

class atomic_counter_atomic_cas : public atomic_counter {
private:
    int m_value; // TODO: Change type

public:
    atomic_counter_atomic_cas();

    int increment() override;
    int decrement() override;

    void set(int value) override;
    int get() override;
};

#endif // ATOMIC_COUNTERS_HPP
