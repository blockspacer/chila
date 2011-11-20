/* Copyright 2011 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHILA_CONNECTIONTOOLS_LIB_OBJECTCONTAINER_HPP
#define	CHILA_CONNECTIONTOOLS_LIB_OBJECTCONTAINER_HPP

#include "fwd.hpp"
#include <chila/lib/misc/Path.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <iostream>
#include "exceptions.hpp"
#include <chila/lib/misc/macrosDef.hpp>


#define DEF_NAMESPACE   CHILA_LIB_MISC__DEF_NAMESPACE

#define libMisc chila::lib::misc


DEF_NAMESPACE(4, (chila,connectionTools,lib,tree))
{
    class ObjectContainer
    {
        protected:
            typedef boost::ptr_map<std::string, TreeElement> ObjectMap;

        private:
            ObjectMap objects;


        protected:
            const ObjectMap &getObjectMap() const { return objects; }

            template <typename Type>
            Type &setObject(std::auto_ptr<Type> object)
            {
                Type &ob = *object;

                const std::string &name = object->getName();
                std::pair<ObjectMap::iterator, bool> ret = objects.insert(name, object);
                assert(ret.second);
                return ob;
            }

            template <typename Type>
            Type &setObject(Type *object)
            {
                std::auto_ptr<Type> objectAPtr(object);
                return setObject(objectAPtr);
            }

            std::vector<const TreeElement*> getObjects() const
            {
                std::vector<const TreeElement*> ret;
                for (ObjectMap::const_iterator it = objects.begin(); it != objects.end(); ++it)
                {
                    ret.push_back(it->second);
                }

                return ret;
            }

            TreeElement &getObject(const std::string &name)
            {
                ObjectMap::iterator it = objects.find(name);
                if (it == objects.end())
                    throw chila::lib::misc::ElementNotFound();

                return *(it->second);
            }

            const TreeElement &getObject(const std::string &name) const
            {
                ObjectMap::const_iterator it = objects.find(name);
                if (it == objects.end())
                    throw chila::lib::misc::ElementNotFound();

                return *(it->second);
            }

            template <typename Type>
            Type &getObject(const std::string &name)
            {
                return dynamic_cast<Type&>(getObject(name));
            }

            template <typename Type>
            const Type &getObject(const std::string &name) const
            {
                return dynamic_cast<const Type&>(getObject(name));
            }

            template <typename Type>
            std::vector<const Type*> getObjects() const
            {
                std::vector<const Type*> ret;
                for (ObjectMap::const_iterator it = objects.begin(); it != objects.end(); ++it)
                    if (const Type *element = dynamic_cast<const Type*>(it->second))
                    {
                        ret.push_back(element);
                    }

                return ret;
            }

            void checkObjects() const
            {
                CheckErrorGroup checkErrorGroup;
                bool hasError = false;
                for (ObjectMap::const_iterator it = objects.begin(); it != objects.end(); ++it) try
                {
                    it->second->check();
                }
                catch (const CheckError &error)
                {
                    hasError = true;
                    checkErrorGroup.addError(error);
                }

                if (hasError) throw checkErrorGroup;
            }
    };
}}}}


#undef libMisc
#undef DEF_NAMESPACE

#include <chila/lib/misc/macrosUndef.hpp>
#endif

