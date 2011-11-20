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

#define OBJECT_GROUP_DEF_GETTERS(ElementType, SingularName)                                                 \
        const ElementType &get##SingularName(const std::string &name) const try                             \
        {                                                                                                   \
            return getObject<ElementType>(name);                                                            \
        }                                                                                                   \
        catch (const chila::lib::misc::ElementNotFound &ex)                                \
        {                                                                                                   \
            throw ex << ErrorInfo::Path(this->getPath() + name);                                            \
        }                                                                                                   \
                                                                                                            \
        ElementType &get##SingularName(const std::string &name) try                                         \
        {                                                                                                   \
            return getObject<ElementType>(name);                                                            \
        }                                                                                                   \
        catch (const chila::lib::misc::ElementNotFound &ex)                                \
        {                                                                                                   \
            throw ex << ErrorInfo::Path(this->getPath() + name);                                            \
        }

#define OBJECT_GROUP_DEF_VEC_GETTER(ElementType, PluralName)                                                \
        ElementType##CVec get##PluralName() const { return getObjects<ElementType>(); }

#define OBJECT_GROUP_DEF_ORDERED_VEC_GETTER(ElementType, PluralName)                                        \
        ElementType##CVec get##PluralName() const                                                           \
        {                                                                                                   \
            const ObjectMap &objects = getObjectMap();                                                      \
            ElementType##CVec ret(objects.size());                                                          \
                                                                                                            \
            for (ObjectMap::const_iterator it = objects.begin(); it != objects.end(); ++it)                 \
            {                                                                                               \
                const ElementType *elem = dynamic_cast<const ElementType*>(it->second);                     \
                assert(elem);                                                                               \
                ret[elem->getPosition()] = elem;                                                            \
            }                                                                                               \
                                                                                                            \
            return ret;                                                                                     \
        }
