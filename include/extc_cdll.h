/* Cross Dynamic Library Loader */

#ifndef EXTC_CDL_GUARD_H
#define EXTC_CDL_GUARD_H

#if defined (__WIN32__) || defined (__WIN64__)
    #include <windows.h>
    #define 
#else
    #include <dlfcn.h>
#endif

typedef struct {
    void* handle;
} cdll;

cdll cdll_load(const char* path);
cdll cdll_load_no_autopath(const char* path);
cdll cdll_unload(cdll* cdll);

void* cdll_symbol(cdll* cdll, const char* symbol);

#define cdll_impl() \
    cdll cdll_load(const char* path) {\
        cdll r;\

#endif /* EXTC_CDL_GUARD_H */
