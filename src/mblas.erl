-module(mblas).
-export([vector/1, to_list/1, dot/2]).
-on_load(init/0).

-record(vector, {length, values}).



default() ->
    exit(nif_library_not_loaded).

init_nif() ->
    default().

init()->
    erlang:load_nif("./mblas_nif", 0),
    init_nif().

vector(L) ->
    default().

matrix(L) ->
    default().

to_list(V) ->
    default().

dot(V1, V2) ->
    default().

