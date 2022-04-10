#ifndef _MY_ALLOCATOR_H_
#define _MY_ALLOCATOR_H_

#include <new>
#include <cstdlib>
#include <cstddef>

namespace my {

template<int inst>
class _malloc_alloc_template {
private:
    static void* oom_malloc(size_t);
    static void* oom_realloc(void*, size_t);
    static void (* _malloc_alloc_oom_handler) ();

public:
    static void* allocate(size_t size) {
        void* tmp = malloc(size);
        if(tmp == nullptr)  tmp = oom_malloc(size);
        return tmp;
    }

    static void deallocate(void* p, size_t /* size */) {
        free(p);
    }

    static void* reallocate(void* p, size_t /* old_size */, size_t new_size) {
        void* tmp = realloc(p, new_size);
        if(tmp == nullptr)  tmp = oom_realloc(p, new_size);
        return tmp; 
    }

    static void (* set_malloc_handler(void (* new_malloc_handler) ())) () {
        void (* old_malloc_handler) () = _malloc_alloc_oom_handler;
        _malloc_alloc_oom_handler = new_malloc_handler;
        return old_malloc_handler;
    }
};

template<int inst>
void (* _malloc_alloc_template<inst>::_malloc_alloc_oom_handler) () = nullptr;

template<int inst>
void* _malloc_alloc_template<inst>::oom_malloc(size_t size) {
    void* tmp = nullptr;

    while(tmp == nullptr) {
        if(_malloc_alloc_oom_handler == nullptr)   throw std::bad_alloc();
        _malloc_alloc_oom_handler();        
        tmp = malloc(size);
    }

    return tmp;
}

template<int inst>
void* _malloc_alloc_template<inst>::oom_realloc(void* p, size_t size) {
    void* tmp = nullptr;

    while(tmp == nullptr) {
        if(_malloc_alloc_oom_handler == nullptr)   throw std::bad_alloc();
        _malloc_alloc_oom_handler();
        tmp = realloc(p, size);
    }

    return tmp;
}

typedef _malloc_alloc_template<0> malloc_alloc;
typedef malloc_alloc alloc;

template<typename ValueT, typename Alloc = alloc>
struct simple_alloc {
    static ValueT* allocate(size_t size) {
        return size == 0 ? nullptr : static_cast<ValueT*>(Alloc::allocate(size * sizeof(ValueT)));
    }

    static ValueT* allocate() {
        return static_cast<ValueT*>(Alloc::allocate(sizeof(ValueT)));
    }

    static ValueT* reallocate(ValueT* p, size_t old_size, size_t new_size) {
        return static_cast<ValueT*>(Alloc::reallocate(p,
                    old_size * sizeof(ValueT), new_size * sizeof(ValueT)));
    }

    static void deallocate(ValueT* p, size_t size) {
        if(size != 0) Alloc::deallocate(p, size * sizeof(ValueT));
    }

    static void deallocate(ValueT* p) {
        Alloc::deallocate(p, sizeof(ValueT));
    }
};

} // namespace my

#endif
