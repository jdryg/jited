#ifndef _ASSERT
#define _ASSERT

#ifdef NDEBUG
#define assert(ignore) ((void)0)
#else
void __jcc_assert(const char* message, const char* filename, unsigned int line, const char* func);
#define assert(x) (!(x) ? __jcc_assert(#x, __FILE__, __LINE__, __func__) : (void)0)
#endif

#define static_assert _Static_assert

#endif // _ASSERT
