/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "util.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    void showChildren(const QObject &object, unsigned indent)
    {
        for (const auto &child : object.children())
        {
            std::cout << textInd(indent) << "- " << child->objectName().toStdString() << " : " << typeid(*child).name() << std::endl;
            showChildren(*qobject_cast<QObject*>(child), indent + 1);
        }
    }
}
MY_NSP_END
