#ifndef ISL_EXT_CUSTOM_FUNCTIONS
#define ISL_EXT_CUSTOM_FUNCTIONS

#include <isl/set.h>

#if defined(__cplusplus)
extern "C" {
#endif


__isl_give isl_basic_set *isl_basic_set_ext_join(__isl_take isl_basic_set *set1, __isl_take isl_basic_set *set2);


#if defined(__cplusplus)
}
#endif

#endif
