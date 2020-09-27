-module(mblas_tests).
-include_lib("eunit/include/eunit.hrl").

load_nif_test() ->
    mblas:vector([1.0, 2.0, 3.0]).

create_vector_test() ->
    V0 = mblas:vector([1.0, 2.0, 3.0]).


