// Copyright (c) 2009 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef UNITTEST_PIMPLE_HEADER_VB
#define UNITTEST_PIMPLE_HEADER_VB

#include <boost.xtra/pimpl.hpp>

struct singleton_type {};
struct pass_value_type {};
struct Foo {};

struct Test1 : public pimpl<Test1>::pointer_semantics
{
    // Pure interface.
    // The implementation is hidden in unittest_pimpl_implementation.cpp

    typedef std::string string;

    Test1 ();
    Test1 (int);
    Test1 (int, int);
    Test1 (Foo&);
    Test1 (Foo const&);
    Test1 (Foo const&, Foo const&);
    Test1 (Foo&, Foo const&);
    Test1 (Foo const&, Foo&);
    Test1 (Foo&, Foo&);
    Test1 (Foo*);
    Test1 (Foo const*);
    Test1 (singleton_type);
    Test1 (pass_value_type);

//    operator int() const { return true; }
//    bool operator==(int) const { return true; }

    int get() const;
    string const& trace() const;
    int id() const;

    private:

    friend class boost::serialization::access;
    template<class Archive> void serialize(Archive&, unsigned int);
};

struct Test2 : public pimpl<Test2>::value_semantics
{
    // Pure interface.
    // The implementation is hidden in unittest_pimpl_implementation.cpp

    typedef std::string string;

    Test2 ();
    Test2 (int);

    // Value-semantics Pimpl must explicitly define op==()
    // if it wants to be comparable. The same as normal classes do.
    bool operator==(Test2 const& that) const;
    bool operator!=(Test2 const& that) const { return !operator==(that); }

    int get() const;
    void set(int);
    string const& trace() const;
    int id() const;
};

struct Base : public pimpl<Base>::pointer_semantics
{
    void call_virtual(); // Note that the function itsels is not virtual.
    Base (int);
    std::string const& trace() const;
};

struct Derived1 : public Base
{
    Derived1 (int, int);
};

struct Derived2 : public Derived1
{
    Derived2 (int, int, int);
};


#endif // UNITTEST_PIMPLE_HEADER_XPEH
