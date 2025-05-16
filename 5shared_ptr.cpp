#include <iostream>
#include <functional>

template<typename T, typename Deleter = std::function<void(T*)>>
class shared_ptr {
private:
    T* ptr;
    int* refCount;
    Deleter deleter;

    void release() {
        if (ptr && refCount) {
            (*refCount)--;
            if (*refCount == 0) {
                deleter(ptr);
                delete refCount;
            }
            ptr = nullptr;
            refCount = nullptr;
        }
    }

public:
    shared_ptr() : ptr(nullptr), refCount(nullptr), deleter([](T* p) { delete p; }) {}

    explicit shared_ptr(T* p) : ptr(p), deleter([](T* p) { delete p; }) {
        if (ptr) {
            refCount = new int(1);
        } else {
            refCount = nullptr;
        }
    }

    shared_ptr(T* p, Deleter d) : ptr(p), deleter(d) {
        if (ptr) {
            refCount = new int(1);
        } else {
            refCount = nullptr;
        }
    }

    shared_ptr(const shared_ptr& other) : ptr(other.ptr), refCount(other.refCount), deleter(other.deleter) {
        if (refCount) {
            (*refCount)++;
        }
    }

    shared_ptr(shared_ptr&& other) noexcept : ptr(other.ptr), refCount(other.refCount), deleter(std::move(other.deleter)) {
        other.ptr = nullptr;
        other.refCount = nullptr;
    }

    shared_ptr& operator=(const shared_ptr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            refCount = other.refCount;
            deleter = other.deleter;
            if (refCount) {
                (*refCount)++;
            }
        }
        return *this;
    }

    shared_ptr& operator=(shared_ptr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            refCount = other.refCount;
            deleter = std::move(other.deleter);
            other.ptr = nullptr;
            other.refCount = nullptr;
        }
        return *this;
    }

    ~shared_ptr() {
        release();
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    T* get() const {
        return ptr;
    }

    int use_count() const {
        return refCount ? *refCount : 0;
    }

    void reset(T* p = nullptr) {
        release();
        ptr = p;
        if (ptr) {
            refCount = new int(1);
        } else {
            refCount = nullptr;
        }
    }

    void reset(T* p, Deleter d) {
        release();
        ptr = p;
        deleter = d;
        if (ptr) {
            refCount = new int(1);
        } else {
            refCount = nullptr;
        }
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }
};