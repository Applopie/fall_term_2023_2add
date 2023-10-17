#include <iostream>
#include <vector>

using u64 = uint64_t;

/*template<class T>
class Vector{
public:
    void PushBack(const T& ne){
        if(size_ + 1 >= alloc_){
            ReAllocFor_(alloc_*2);
        }

        new (buffer_ + size_*sizeof(T)) T(ne);
        ++size_;
    }
    void PopBack(){
        delete static_cast<T*> (buffer_ + size_ * sizeof(T));
        --size_;
    }
    size_t Size() const {return size_;}

    T& operator[](size_t index){
        return *(static_cast<T*>(buffer_ + index*sizeof(T)));
    };
    const T& operator[](size_t index) const {
        return *(static_cast<T*>(buffer_ + index*sizeof(T)));
    }

    Vector() : size_(0), alloc_(0), buffer_(nullptr){
        ReAllocFor_(4);
    }

    ~Vector(){
        T*cur = reinterpret_cast<T*>(buffer_);
        for(size_t i=0;i<alloc_; i++){
            cur->~T();
            ++cur;
        }
        delete[] buffer_;
    }

    void Reserve(size_t n){
        ReAllocFor_(n);
    }

private:
    void ReAllocFor_(size_t n) {
        if (alloc_ >= n) return;
        size_t need_bytes = n*sizeof(T);
        std::byte * new_buf = new std::byte[need_bytes];

        for(size_t i=0; i<size_; ++i){
            T * current = reinterpret_cast<T*>(buffer_+ i * sizeof(T));
            T * new_cur = reinterpret_cast<T*>(new_buf + i * sizeof(T));

            new (new_cur) T (std::move(*current));
            current->~T();
        }

        delete[] buffer_;
        buffer_ = new_buf;
        alloc_ = n;
    }

    std::byte * buffer_;
    size_t size_, alloc_;
};*/

struct Noizy
{
    Noizy() { std::cerr << "Noizy::Noizy()\n"; }
    ~Noizy() { std::cerr << "Noizy::~Noizy() -dtor\n"; }
    Noizy(const Noizy &) { std::cerr << "COPY CTOR\n"; }
    Noizy &operator=(const Noizy &)
    {
        std::cerr << "move CTOR\n";
        return *this;
    }
    Noizy(Noizy &&) noexcept { std::cerr << "move CTOR\n"; }
    Noizy &operator=(Noizy &&) noexcept
    {
        std::cerr << "move assgn\n";
        return *this;
    }

    uint64_t dummy;
};

int main()
{
    std::vector<Noizy> v;
    for (size_t i = 0; i < 10; ++i)
    {
        std::cerr << "=====\n";
        Noizy n;
        std::cerr << "-----\n";
        v.push_back(n);
        std::cerr << "=====\n";
    }
    std::cerr << "===== DONE =====";
}
