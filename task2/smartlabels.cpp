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

// let's go next one
template <class T>
struct csys
{
    size_t cnt, exs;
};

class sharedptr
{
private:
    T *uptr;
    csys ccount;

    void increase()
    {
        if (ccount != nullptr)
        {
            ccount->cnt++;
        }
    }

    void unclaim() noexcept
    {
        this->~sharedptr();

        uptr = nullptr;
        ccount = nullptr;
    }

public:
    sharedptr() noexcept : uptr(), ccount() {}
    sharedptr(const sharedptr &pt) noexcept : uptr(pt.uptr), ccount(pt.count)
    {
        increase();
    }
    sharedptr &operator=(const sharedptr &pt) noexcept
    {
        if (ccount != pt.ccount)
        {
            this->~sharedptr();
        }

        uptr = pt.uptr;
        count = pt.ccount;
        increase();
        return *this;
    }

    sharedptr(sharedptr &&pt) noexcept : uptr(pt.uptr), ccount(pt.ccount)
    {
        increase();
        pt.unclaim();
    }
    sharedptr &operator=(sharedptr &&pt) noexcept
    {
        if (ccount != pt.ccount)
        {
            this->~sharedptr();
        }
        uptr = pt.uptr;
        ccount = pt.ccount;
        increase();
        pt.reset();
        return *this;
    }

    sharedptr(T *pt) noexcept : uptr(pt)
};

// tbf the last or the least idc anymore
class weakptr