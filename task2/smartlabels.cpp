template <class T>
class uniqueptr
{
private:
    T *uptr;

    void claim() noexcept
    {
        T *p = uptr;
        uptr = nullptr;
        return p;
    }

    void unclaim(T *p) noexcept
    {
        T *pt = uptr;
        uptr = p;
        if (pt != uptr)
        {
            delete (pt);
        }
    }

    void Delete(T *pt) const noexcept
    {
        if (pt != nullptr)
        {
            delete (pt);
        }
    }

public:
    uniqueptr() : uptr() {}
    uniqueptr(T *p) : uptr(p) {}

    \\конструктор копирования и присваивание копированием
    uniqueptr(const uniqueptr &o) = delete;
    uniqueptr &operator=(const uniqueptr &o) = delete;

    \\конструктор перемещения и присвавание перемещением
    uniquePtr(uniqueptr &&) = default;
    uniqueptr &operator=(uinqueptr &&o) noexcept
    {
        unclaim(o.claim());
        return *this;
    }

    ~uniqueptr() noexcept
    {
        delete (uptr);
    }

    T *operator->() { return uptr; }
    T &operator*() { return *uptr; }
};
class sharedptr class weakptr