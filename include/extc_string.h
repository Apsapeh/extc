#include "extc_rint.h"
#include "extc_vec.h"

vector_template_def(__char, i8);

typedef struct string {
    usize size;
    i8* str;
    vec___char cstr_vec;
} string;

string string_new();
string string_from(const i8* str);
string string_from_n(const i8* str, usize n);
string stings_concat(string* self, string* vstr);
string string_concat_str(string* self, const i8* str);
void string_free(string* self);

#define string_template_impl() \
    vector_template_impl(__char, i8);
    string string_new() {\
        string r;\
        r.size = 0;\
        r.cstr_vec = vec___char_init();\
        r.str = r.cstr_vec.data;\
        return r;
    }\
    \
    string string_from(const i8* str) {\
        string r;\
        r.cstr_vec = vec___char_init();\
        vec___char_append_data(&r.cstr_vec, str, strlen(str));\
        r.size = r.cstr_vec.size;\
        r.str = r.cstr_vec.data;\
        return r;\
    }\
    string string_from_n(const i8* str, usize n) {\
        string r;\
        r.cstr_vec = vec___char_init();\
        vec___char_append_data(&r.cstr_vec, str, n);\
        r.size = r.cstr_vec.size;\
        r.str = r.cstr_vec.data;\
        return r;\
    }\
    \
    void string_free(string* self) {\
        vec___char_free(&self->cstr_vec);\
        self->size = 0;\
        self->str = NULL;\
        self = NULL;\
    }\
