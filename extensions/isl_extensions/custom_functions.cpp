#include "custom_functions.h"
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <isl/constraint.h>

using namespace std;


__isl_give isl_basic_set *isl_basic_set_ext_join(__isl_take isl_basic_set *set1, __isl_take isl_basic_set *set2){
	unsigned int dimA = isl_basic_set_dim(set1, isl_dim_set);
    unsigned int dimB = isl_basic_set_dim(set2, isl_dim_set);
	map<string, int> varsA; // contains all variables from A
    vector<string> varsNew; // contains all variables from B but not from A
    vector<int> oldPosToNewPosB(dimB); // "maps" old indices (of B's vars) to new indices (in result)
    for (unsigned i = 0; i < dimA; i++){
        const char* buffer = isl_basic_set_get_dim_name(set1, isl_dim_set, i);
        varsA[string(buffer)] = i;
    }
    for (unsigned i = 0; i < dimB; i++){
        const char* buffer = isl_basic_set_get_dim_name(set2, isl_dim_set, i);
        map<string, int>::iterator newpos = varsA.find(string(buffer));
        if (newpos == varsA.end()) {
            oldPosToNewPosB[i] = dimA + varsNew.size();
            varsNew.push_back(string(buffer));
        }else{
            oldPosToNewPosB[i] = newpos->second;
        }
    }

    // create set AxB with A's constraints
    isl_basic_set* result = isl_basic_set_add_dims(set1, isl_dim_set, (unsigned int) varsNew.size());
    unsigned int pos = varsA.size();
    for (vector<string>::iterator it = varsNew.begin(); it != varsNew.end(); it++) {
        result = isl_basic_set_set_dim_name(result, isl_dim_set, pos++, it->c_str());
    }

    // add b's constraints to A
    isl_constraint_list* constraints = isl_basic_set_get_constraint_list(set2);
    for (signed int i = isl_constraint_list_n_constraint(constraints)-1; i >= 0; i--){
        isl_constraint* cB = isl_constraint_list_get_constraint(constraints, i);
        isl_constraint* cResult = isl_constraint_is_equality(cB)
                             ? isl_constraint_alloc_equality(isl_basic_set_get_local_space(result))
                             : isl_constraint_alloc_inequality(isl_basic_set_get_local_space(result));
        cResult = isl_constraint_set_constant_val(cResult, isl_constraint_get_constant_val(cB));
        for (unsigned i = 0; i < dimB; i++){
            cResult = isl_constraint_set_coefficient_val(cResult, isl_dim_set, oldPosToNewPosB[i],
                                                         isl_constraint_get_coefficient_val(cB, isl_dim_set, i));
        }
        result = isl_basic_set_add_constraint(result, cResult);
        isl_constraint_free(cB);
    }
    isl_constraint_list_free(constraints);

    // finished
    isl_basic_set_free(set2);
	return result;
}
