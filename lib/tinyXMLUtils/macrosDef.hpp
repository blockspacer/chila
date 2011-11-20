/* Copyright 2011 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define CHILA_LIB_TINYXMLUTILS__PUSH_TAG(path, name) const XMLPath::Push pp_##name(path, #name);
#define CHILA_LIB_TINYXMLUTILS__CHECK_TAG_AND_PUSH(path, elem, name) \
    path.checkTag(elem, #name); CHILA_LIB_TINYXMLUTILS__PUSH_TAG(path, name)

#define CHILA_LIB_TINYXMLUTILS__TIXML_ITERATE_ELEMENTS(root, cur) \
    for (const TiXmlElement *cur = root->FirstChildElement(); cur; cur = cur->NextSiblingElement())
