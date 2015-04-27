template<typename T>
class Maybe
{
    bool _just;
    char _data[sizeof(T)];
public:
    Maybe():
        _just(false)
    {}
    Maybe(const T &val):
        _just(true)
    {
        new(_data) T(val);
    }
    Maybe(T &&val):
        _just(true)
    {
        //get() = static_cast<T &&>(val);
        new(_data) T(static_cast<T &&>(val));
    }
    explicit operator bool() const
    {
        return _just;
    }
    T &get()
    {
        //check if just?
        return *reinterpret_cast<T *>(_data);
    }

    const T &get() const
    {
        //check if just?
        return *reinterpret_cast<const T *>(_data);
    }
};
