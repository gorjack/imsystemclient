#ifndef UTILS_TTSINGLETONT_H
#define UTILS_TTSINGLETONT_H



namespace utils
{
    template <class T>
    class CSingletonT
    {
    public:
        static T *instance();

        static void release();

    protected:

        static T *s_pInstance;
    };

}

#endif
