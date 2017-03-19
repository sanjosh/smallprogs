#pragma once

#include <atomic>
#include <iostream>

template <class N>
struct SmartPtr : public std::atomic<N>
{
    typedef std::atomic<N> base_type;
    const int SHIFT_LEN = 48;

    bool compare_exchange_strong(N& oldptr, N newval, bool oldf, bool newf)
    {
       uintptr_t old = uintptr_t(oldptr) | (uintptr_t(oldf) << SHIFT_LEN);
       uintptr_t newv = uintptr_t(newval) | (uintptr_t(newf) << SHIFT_LEN);
       N oldn = N(old);
       return base_type::compare_exchange_strong(oldn, N(newv));
    }

    N load(bool& flag) const noexcept
    {
        N x = base_type::load();
        flag = (uintptr_t(x) >> SHIFT_LEN);
        return x;
    }

    N load() const noexcept
    {
        return base_type::load();
    }

    void store(N n) noexcept
    {
        base_type::store(n);
    }

    void store(N n, bool flag) noexcept
    {
        uintptr_t newv = uintptr_t(n) | (uintptr_t(flag) << SHIFT_LEN);
        base_type::store(N(newv));
    }

    SmartPtr() noexcept = default;
    ~SmartPtr() noexcept = default;
    SmartPtr(const SmartPtr& ) = delete;
    SmartPtr& operator = (const SmartPtr&) = delete;
    SmartPtr& operator = (const SmartPtr&) volatile = delete;

    SmartPtr(N i) noexcept : base_type(i) {}

    bool is_lock_free() const noexcept 
    {
        return base_type::is_lock_free();
    }
};

struct Node
{
    int64_t key = 0;
    SmartPtr<Node*> next {nullptr};

    Node(const int64_t key) : key(key) {}
};

struct Set
{
    std::atomic<Node*> head {nullptr};
    std::atomic<Node*> tail {nullptr};

    Set();

    struct Bound {
       Node* pred = nullptr; 
       Node* curr = nullptr;

       Bound(Node* p, Node* c) : pred(p), curr(c) {}
    };

    private:
    Bound find(Node* head, int64_t key);

    public:

    bool insert(int64_t key);
    bool remove(int64_t key);
    bool contains(int64_t key);
};
