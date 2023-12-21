template <class T>
class UniquePtr
{
public:
    UniquePtr() : uptr() {}

    UniquePtr(const UniquePtr &o) = delete;
    UniquePtr &operator=(const UniquePtr &o) = delete;

    UniquePtr(UniquePtr &&o) = default;

    UniquePtr &operator=(UniquePtr &&o) noexcept
    {
        unclaim(o.claim());
        return *this;
    }

    UniquePtr(T *p) : uptr(p) {}

    T *operator->() { return uptr; }

    T &operator*() { return *uptr; }

    ~UniquePtr() noexcept
    {
        delete (uptr);
    }

private:
    T *uptr;

    T *claim() noexcept
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
};

// ================================================
struct RefCntBlock
{
    size_t strong, weak;
};

template <class T>
class WeakPtr;

template <class T>
class SharedPtr
{
    friend class WeakPtr<T>;

public:
    SharedPtr() noexcept : uptr(), ccount() {}
    SharedPtr(const SharedPtr &o) noexcept : uptr(o.uptr), ccount(o.ccount)
    {
        increase();
    }
    SharedPtr &operator=(const SharedPtr &o) noexcept
    {
        if (ccount != o.ccount)
        {
            Eraser();
        }

        uptr = o.uptr;
        ccount = o.ccount;
        increase();
        return *this;
    }

    SharedPtr(SharedPtr &&o) noexcept : uptr(o.uptr), ccount(o.ccount)
    {
        increase();
        o.Reset();
    }

    SharedPtr &operator=(SharedPtr &&o) noexcept
    {
        if (ccount != o.ccount)
        {
            Eraser();
        }
        uptr = o.uptr;
        ccount = o.ccount;
        increase();
        o.Reset();
        return *this;
    }

    SharedPtr(T *p) noexcept : uptr(p), ccount(new RefCntBlock)
    {
        ccount->strong++;
    }

    // Implementation below
    SharedPtr(const WeakPtr<T> &o) noexcept;

    // Replaces pointer with nullptr
    void Reset() noexcept
    {
        Eraser();
        uptr = nullptr;
        ccount = nullptr;
    }

    T *operator->() { return uptr; }

    T &operator*() { return *uptr; }

    ~SharedPtr()
    {
        Eraser();
    }

private:
    T *uptr;
    RefCntBlock *ccount;

    void increase()
    {
        if (ccount != nullptr)
        {
            ccount->strong++;
        }
    }

    void Eraser()
    {
        if (ccount != nullptr)
        {
            ccount->strong--;
            if (ccount->strong == 0)
            {
                delete uptr;

                if (ccount->weak == 0)
                {
                    delete ccount;
                }
            }
        }
    }
};

template <class T>
class WeakPtr
{
    friend class SharedPtr<T>;

public:
    WeakPtr() noexcept : ccount() {}
    WeakPtr(const WeakPtr &pt) noexcept : uptr(pt.uptr), ccount(pt.ccount)
    {
        increase();
    }
    WeakPtr &operator=(const WeakPtr &pt) noexcept
    {
        if (ccount != pt.ccount)
        {
            Eraser();
        }

        uptr = pt.uptr;
        ccount = pt.ccount;
        increase();
        return *this;
    }

    WeakPtr(WeakPtr &&o) noexcept : uptr(o.uptr), ccount(o.ccount)
    {
        increase();
        o.Reset();
    }

    WeakPtr &operator=(WeakPtr &&o) noexcept
    {
        if (ccount != o.ccount)
        {
            Eraser();
        }

        uptr = o.uptr;
        ccount = o.ccount;
        increase();
        o.Reset();
        return *this;
    }

    WeakPtr(const SharedPtr<T> &o) noexcept : uptr(o.uptr), ccount(o.ccount)
    {
        increase();
    }

    WeakPtr &operator=(const SharedPtr<T> &o) noexcept
    {
        if (ccount != ccount)
        {
            Eraser();
        }

        uptr = o.uptr;
        ccount = o.ccount;
        increase();
        return *this;
    }

    // Replaces pointer with nullptr
    void Reset()
    {
        Eraser();

        uptr = nullptr;
        ccount = nullptr;
    }

    bool Expired() const noexcept
    {
        return (ccount == nullptr || ccount->strong == 0);
    }

    SharedPtr<T> Lock() noexcept
    {
        return SharedPtr<T>(*this);
    }

    ~WeakPtr()
    {
        Eraser();
    }

private:
    T *uptr;
    RefCntBlock *ccount;

    void increase()
    {
        if (ccount != nullptr)
        {
            ccount->weak++;
        }
    }

    void Eraser()
    {
        if (ccount != nullptr)
        {
            ccount->weak--;
            if (ccount->weak == 0 & ccount->strong == 0)
            {
                delete ccount;
            }
        }
    }
};

template <class T>
SharedPtr<T>::SharedPtr(const WeakPtr<T> &o) noexcept : uptr(o.uptr), ccount(o.ccount)
{
    increase();
}