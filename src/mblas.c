#include <erl_nif.h>
#include <string.h>


/*
-------------------------------------------------------------------------------------------------- -|
                        -----------------------------------------                                   |
                        |             HELPER VARIABLES          |                                   |
                        -----------------------------------------                                   |
----------------------------------------------------------------------------------------------------|
*/
ERL_NIF_TERM atom_vector;

/* 
-------------------------------------------------------------------------------------------------- -|
                        -----------------------------------------                                   |
                        |      HELPER FUNCTIONS / STRUCTS       |                                   |
                        -----------------------------------------                                   |
----------------------------------------------------------------------------------------------------|                                   
            LIST MANIP FUNCTIONS       |                                   
----------------------------------------                                   
*/


int list_length(ErlNifEnv* env, const ERL_NIF_TERM list, unsigned* length){
    if(!enif_get_list_length(env, list, length)){
        return 0;
    }
    return 1;
}

int list_to_binary(ErlNifEnv* env, ERL_NIF_TERM list, double* dest){
    ERL_NIF_TERM elem;
    for(int i=0; enif_get_list_cell(env, list, &elem, &list); i++)
        if(!enif_get_double(env, elem, dest + i))
            return 0;
    return 1;
}


/* 
-----------------------------------------
|            VECTOR                      |
-----------------------------------------
*/

typedef struct {
    int length;
    ErlNifBinary values;
    double* ptr;
} Vector;

int alloc_vector(int length, Vector* vector){
    vector->length = length;
    int result =  enif_alloc_binary(sizeof(double) * length, &vector->values);
    vector->ptr = (double*) vector->values.data; 
}

int term_to_vector(ErlNifEnv* env, const ERL_NIF_TERM record, Vector* vector){
    //Resulting vector cannot be modified... should change to const Vector** vector!
    int arity;
    const ERL_NIF_TERM* array;

    int result = enif_get_tuple(env, record, &arity, &array) 
        && enif_get_int(env, array[1], &vector->length)
        && enif_inspect_binary(env, array[2], &vector->values);

    vector->ptr = (double*) vector->values.data;
}

ERL_NIF_TERM vector_to_term(ErlNifEnv* env, Vector vector){
    ERL_NIF_TERM length_field = enif_make_int(env, vector.length);
    ERL_NIF_TERM values = enif_make_binary(env, &vector.values);

    return enif_make_tuple3(env, atom_vector, length_field, values); 
}

/*
-------------------------------------------------------------------------------------------------- -|
                        -----------------------------------------                                   |
                        |          NIFS IMPLEMENTATION          |                                   |
                        -----------------------------------------                                   |
----------------------------------------------------------------------------------------------------|
*/

ERL_NIF_TERM init(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]){
    atom_vector = enif_make_atom(env, "vector\0");
    return enif_make_atom(env, "ok\0");
}


ERL_NIF_TERM vector(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    Vector vector;
    
    if(list_length(env, argv[0], &vector.length)
        && enif_alloc_binary(sizeof(double) * vector.length, &vector.values)
        && list_to_binary(env, argv[0], (double*) vector.values.data)
        == 0)
            return enif_make_badarg(env);

    return vector_to_term(env, vector);
}


ERL_NIF_TERM to_list(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    Vector vector;

    if(!term_to_vector(env, argv[0], &vector)){
        return enif_make_badarg(env);
    }

    int i;

    ERL_NIF_TERM list[vector.length];
    for(i=0; i<vector.length; i++){
        list[i] = enif_make_double(env, vector.ptr[i]);
    }


    return enif_make_list_from_array(env, list, vector.length);
}


ERL_NIF_TERM dot(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    Vector v0, v1, res;

    if(term_to_vector(env, argv[0], &v0)
        && term_to_vector(env, argv[1], &v1)
        && alloc_vector(v0.length, &res)
        == 0){
            return enif_make_badarg(env);
    }

    for(int i=0; i<v0.length; i++){
        res.ptr[i] = v0.ptr[i] * v1.ptr[i];
    }
    return vector_to_term(env, res);
}


ErlNifFunc nif_funcs[] = {
    {"init_nif", 0, init},
    {"vector", 1, vector},
    {"to_list", 1, to_list},
    {"dot", 2, dot}
};

ERL_NIF_INIT(mblas, nif_funcs, NULL, NULL, NULL, NULL)