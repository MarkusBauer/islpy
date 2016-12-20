#include "custom_functions.h"
#include <iostream>

__isl_give isl_basic_set *isl_basic_set_ext_join(__isl_take isl_basic_set *set1, __isl_take isl_basic_set *set2){
	std::cout << "Hello World! " << __func__ << " is here!" << std::endl;
	isl_basic_set_free(set2);
	return set1;
}
