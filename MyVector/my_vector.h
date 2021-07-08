#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdexcept>
#include <cstddef>
#include <limits>
#include "my_allocator.h"
#include "my_construct.h"
#include "my_uninitialized.h"

namespace my {

template<typename ValueT, typename Alloc = alloc>
class vector {
public:
    using value_type        = ValueT;

    using reference         = ValueT&;
    using const_reference   = const ValueT&;

    using iterator          = ValueT*;
    using const_iterator    = const ValueT*;

    using size_type         = std::size_t;
    using difference_type   = std::ptrdiff_t;

private:
    using allocator = simple_alloc<ValueT, Alloc>;

private:
    iterator m_start;
    iterator m_finish;
    iterator m_end_of_storage;

private:
    template<typename... Args>
    void insert_aux(const_iterator pos, Args&&... args) {
        difference_type offset = pos - this->m_start;
        if(this->m_finish != this->m_end_of_storage) {
            this->m_finish = uninitialized_copy(this->m_start + offset, this->m_finish, this->m_start + offset + 1);
        }else {
            size_type old_size = size();
            size_type new_size = (old_size == 0 ? 1 : 2 * old_size);

            iterator new_start;
            if(old_size == 0) {
                new_start = allocator::allocate(new_size);
                this->m_finish = new_start + 1;
            }else {
                new_start = allocator::reallocate(this->m_start, old_size, new_size);
                this->m_finish = uninitialized_copy(this->m_start + offset, this->m_finish,
                        new_start + offset + 1);
                if(new_start != this->m_start) {
                    uninitialized_copy(this->m_start, this->m_start + offset, new_start);
                    allocator::deallocate(this->m_start, static_cast<size_type>(old_size));
                }
            }
            this->m_start = new_start;
            this->m_end_of_storage = this->m_start + new_size;
        }
        construct(this->m_start + offset, std::forward<Args>(args)...);
    }

public:
    constexpr
    vector() noexcept
    : m_start(), m_finish(), m_end_of_storage() {}

    ~vector() {
        destroy(m_start, m_finish);

        if(m_start)
            allocator::deallocate(m_start, static_cast<size_type>(m_finish - m_start));
    }

    vector(const vector& rhs) {
        allocator::allocate(this->m_start, static_cast<size_type>(rhs.m_end_of_storage - rhs.m_start));
        this->m_finish = uninitialized_copy(rhs.m_start, rhs.m_finish, this->m_start);
        this->m_end_of_storage = this->m_start + (rhs.m_end_of_storage - rhs.m_start);
    }

    vector(vector&& rhs) noexcept
    : m_start(rhs.m_start), m_finish(rhs.m_finish),
      m_end_of_storage(rhs.m_end_of_storage) {
        rhs.m_start = rhs.m_finish = rhs.m_end_of_storage = nullptr;
    }

    explicit vector(size_type size, const Alloc& alloc = Alloc()) {
        this->m_start = allocator::allocate(size);
        this->m_finish = this->m_end_of_storage = this->m_start + size;
        uninitialized_fill_n(this->m_start, size, ValueT());
    }

    vector(size_type size, const value_type& val, const Alloc& alloc = Alloc()) {
        this->m_start = allocator::allocate(size);
        this->m_finish = this->m_end_of_storage = this->m_start + size;
        uninitialized_fill_n(this->m_start, size, val);
    }
    
    vector& operator=(const vector& rhs) {
        if(&rhs != this) {
            size_type dest_capacity = this->m_end_of_storage - this->m_start;
            size_type src_capacity = rhs.m_end_of_storage - rhs.m_start;

            if(dest_capacity < src_capacity) {
                this->m_start = allocator::reallocate(this->m_start, dest_capacity, src_capacity);
                this->m_end_of_storage = this->m_start + src_capacity;
            }

            this->m_finish = std::copy(rhs.m_start, rhs.m_finish, this->m_start);
        }
        return *this;
    }

    vector& operator= (vector&& rhs) noexcept {
        this->m_start = rhs.m_start;
        this->m_finish = rhs.m_finish;
        this->m_end_of_storage = rhs.m_end_of_storage;

        rhs.m_start = rhs.m_finish = rhs.m_end_of_storage = nullptr;
    }

    // iterator
    iterator begin() noexcept {
        return this->m_start;
    }

    const_iterator begin() const noexcept {
        return this->m_start;
    }

    iterator end() noexcept {
        return this->m_finish;
    }

    const_iterator end() const noexcept {
        return this->m_finish;
    }

    // capacity
    bool empty() const noexcept {
        return this->begin() == this->end();
    }

    size_type size() const noexcept {
        return this->end() - this->begin();
    }

    size_type max_size() const noexcept {
        return std::numeric_limits<difference_type>::max();
    }
    
    /*
    void reserve(size_type new_cap) {
        
    }
    */

    size_type capacity() const noexcept {
        return this->m_end_of_storage - this->m_start;
    }

    // element access
    reference at(size_type pos) {
        if(!(pos < size())) {
            char buf[128];
            std::sprintf(buf, "my::vector: pos (which is %zu) >= this->size() (which is %zu)",
                         pos, size());

            throw std::out_of_range(buf);
        }
        return *(this->m_start + pos);
    }

    const_iterator at(size_type pos) const {
        if(!(pos < size())) {
            char buf[128];
            std::sprintf(buf, "my::vector: pos (which is %zu) >= this->size() (which is %zu)",
                    pos, size());

            throw std::out_of_range(buf);
        }
        return *(this->m_start + pos);
    }

    reference operator[] (size_type pos) {
        return *(this->m_start + pos);
    } 

    const_reference operator[] (size_type pos) const {
        return *(this->m_start + pos);
    }

    reference front() {
        return *this->begin();
    }
    
    const_reference front() const {
        return *this->begin();
    }

    reference back() {
        return *(this->end() - 1);
    }

    const_reference back() const {
        return *(this->end() - 1);
    }

    value_type* data() noexcept {
        return this->m_start;
    }

    const value_type* data() const noexcept {
        return this->m_start;
    }

    /*
    void shrink_to_fit() {

    }
    */

    // modifiers
    void clear() noexcept {
        this->erase(this->begin(), this->end());
    }

    iterator insert(const_iterator pos, const value_type& val) {
        insert_aux(pos, val);
    }

    iterator insert(const_iterator pos, value_type&& val) {
        insert_aux(pos, std::move(val));
    }

    /*
    iterator insert(const_iterator pos, size_type count, const value_type& val);

    template<class InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last);
    
    iterator insert( const_iterator pos, std::initializer_list<value_type> ilist );

    template< class... Args >
    iterator emplace( const_iterator pos, Args&&... args );
    */

    iterator erase(const_iterator pos) {
        iterator p = this->m_start + (pos - this->m_start);
        destroy(p);
        this->m_finish = uninitialized_copy(p + 1, this->m_finish, p);
        return pos;
    }

    iterator erase(const_iterator first, const_iterator last) {
        iterator f = this->m_start + (first - this->m_start),
                 l = this->m_start + (last - this->m_start);
        destroy(f, l);
        this->m_finish = uninitialized_copy(l, this->m_finish, f);
        return f;
    }

    void push_back(const value_type& val) {
        insert_aux(this->m_finish, val);
    }

    void push_back(value_type&& val) {
        insert_aux(this->m_finish, std::move(val));
    }

    template<class... Args>
    reference emplace_back(Args&&... args) {
        insert_aux(this->m_finish, std::forward<Args>(args)...);
    }

    void pop_back() {
        this->m_finish--;
        destroy(this->m_finish);
    }

    /*
    void resize(size_type new_size) {

    }

    void resize(size_type new_size, const value_type& val) {

    }

    void swap(vector& other) {

    }
    */
};

} // namespace my

#endif
