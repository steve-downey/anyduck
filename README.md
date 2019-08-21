# AnyDuck #

Cheap Type Erasure with std::any

Using std::any as the storage for a type erased object matching an interface, and capturing the de-erasure with a lambda where the underlying type is known seems to be very inexpensive and well visible to the compiler for optimization.


The general technique is grabbing the type to be any_cast, when the type is known, to initialize a function pointer, using the decay of a non-capturing lambda to erase the type used in any_cast.

``` c++
[](std::any const& d, int i) {
                    return std::any_cast<std::remove_reference_t<Duck>>(&d)->quack(
                        i);
                }
```

This can be done directly for the holding type erasing object, at the cost of space for each member function, or the vtbl construction can be delegated to a templated function instantiating a static identical for each duck type.

For comparison:

Using any as the store and unwrapping via lambda

    3: ---------------------------------------------------------------------------------------
    3: Benchmark                                             Time             CPU   Iterations
    3: ---------------------------------------------------------------------------------------
    3: Benchmark_Construct_AnyDuck                        2.36 ns         2.36 ns      6341642
    3: Benchmark_Construct_AnyDuck_LValue                 2.78 ns         2.78 ns      6154584
    3: Benchmark_Construct_AnyDuck_Temp                   3.64 ns         3.64 ns      3686884
    3: Benchmark_Construct_HiddenAnyDuck_LValue           8.36 ns         8.36 ns      1678108
    3: Benchmark_Construct_HiddenAnyDuck_Temp             8.09 ns         8.09 ns      1796347
    3: Benchmark_Construct_AnyDuckVtbl                    3.81 ns         3.81 ns      3659894
    3: Benchmark_Construct_AnyDuckVtbl_LValue             3.82 ns         3.82 ns      3712408
    3: Benchmark_Construct_AnyDuckVtbl_Temp               4.45 ns         4.45 ns      3142312
    3: Benchmark_Construct_HiddenAnyDuckVtbl_LValue       8.10 ns         8.11 ns      1697762
    3: Benchmark_Construct_HiddenAnyDuckVtbl_Temp         8.15 ns         8.16 ns      1740605


"Traditional" Type erasure Parent Style (hidden inheritance)

    6: ------------------------------------------------------------------------------------
    6: Benchmark                                          Time             CPU   Iterations
    6: ------------------------------------------------------------------------------------
    6: Benchmark_Construct_TEPSDuck                    11.6 ns         11.6 ns      1361988
    6: Benchmark_Construct_TEPSDuck_LValue             14.4 ns         14.4 ns      1155166
    6: Benchmark_Construct_TEPSDuck_Temp               13.9 ns         13.9 ns      1023115
    6: Benchmark_Construct_HiddenTEPSDuck_LValue       24.0 ns         24.0 ns       644624
    6: Benchmark_Construct_HiddenTEPSDuck_Temp         22.0 ns         22.0 ns       681301


Actual use of inheritance

    9: ---------------------------------------------------------------------------------
    9: Benchmark                                       Time             CPU   Iterations
    9: ---------------------------------------------------------------------------------
    9: Benchmark_Construct_IDuck                    12.6 ns         12.6 ns      1226115
    9: Benchmark_Construct_IDuck_LValue             15.4 ns         15.4 ns      1014344
    9: Benchmark_Construct_IDuck_Temp               16.7 ns         16.7 ns       829242
    9: Benchmark_Construct_HiddenIDuck_LValue       20.0 ns         20.0 ns       702076
    9: Benchmark_Construct_HiddenIDuck_Temp         20.8 ns         20.8 ns       708747
