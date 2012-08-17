CRoot
=====

a simple work-in-progress C-API binding to the C++ `ROOT` framework.

the structure is quite simple:

    //C++
    TRootClass::SomeMethod(...)

    /* CRoot */
    CRoot_RootClass_SomeMethod(...)

Constructors are named `CRoot_RootClass_new(...)` and destructors `CRoot_RootClass_delete(...)`

(Do *NOT* confuse them with the New/Delete methods which could exist for some classes !)

build instructions
------------------

    $ ./waf configure
    $ ./waf build
    $ ./waf install