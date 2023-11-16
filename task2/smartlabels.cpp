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
    size_t st, wk;
};

template <class T>
class weakptr;

class sharedptr
{
    friend class weakptr<T>;

private:
    T *uptr;
    csys ccount;

    void increase()
    {
        if (ccount != nullptr)
        {
            ccount->st++;
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
    sharedptr(const sharedptr &pt) noexcept : uptr(pt.uptr), ccount(pt.ccount)
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
        ccount = pt.ccount;
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

    sharedptr(T *pt) noexcept : uptr(pt), ccount(new csys)
    {
        ccount->st++;
    }

    SharedPtr(const weakptr<T> &o) noexcept;

    ~sharedptr()
    {
        if (ccount != nullptr)
        {
            ccount->st--;
            if (ccount->st == 0)
            {
                delete uptr;

                if (ccount->wk == 0)
                {
                    delete ccount;
                }
            }
        }
    }

    T *operator->() { return uptr; }
    T &operator*() { return *uptr; }
};

// tbf the last or the least idc anymore
template <class T>
class weakptr
{
    friend class sharedptr<T>;

private:
    T *uptr;
    csys ccount;

    void increase()
    {
        if (ccount != nullptr)
        {
            ccount->wk++;
        }
    }

    void unclaim()
    {
        this->~weakptr();

        uptr = nullptr;
        ccount = nullptr;
    }

public:
    weakptr() noexcept : ccount() {}
    weakptr(const weakptr &pt) noexcept : uptr(pt.uptr), ccount(pt.ccount)
    {
        increase();
    }
    weakptr &operator=(const weakptr &pt) noexcept
    {
        if (ccount != pt.ccount)
        {
            this->~weakptr();
        }

        uptr = pt.uptr;
        ccount = pt.ccount;
        increase();
        return *this;
    }

    weakptr(weakptr &&pt) noexcept : uptr(pt.uptr), ccount(pt.ccount)
    {
        increase();
        pt.unclaim();
    }
    weakptr &operator=(weakptr &&pt) noexcept
    {
        if (ccount != pt.ccount)
        {
            this->~weakptr();
        }

        uptr = pt.uptr;
        ccount = pt.ccount;
        increase();
        pt.unclaim();
        return *this;
    }
};