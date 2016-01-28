/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <iostream>
#include <chila/lib/node2/Container.hpp>

namespace clNode2 = chila::lib::node2;
namespace clMisc = chila::lib::misc;

template <typename Type>
struct TypedNode : public clNode2::Node
{
    Type data;

    TypedNode(Type data) : data(rvalue_cast(data)) {}

    void stream(std::ostream &out, unsigned indent) const override
    {
        out << data;
    }
};

int main(int argc, char **argv)
{
    clNode2::Container cont0, cont1;
    using String = TypedNode<std::string>;
    using Int = TypedNode<int>;

    cont0.add("name", String("test"));
    cont0.add("age", Int(2));

    cont1.add("str", String("dude"));
    cont1.add("int", Int(3));

    cont0.add("cont1", cont1);

    cont0.stream(std::cout, 0);

    auto cont0Copy = cont0;

//    auto &val = cont0Copy.get<clNode2::Container>("cont1").get<int>("int");
    cont0Copy.stream(std::cout, 0);

    return EXIT_SUCCESS;
}
