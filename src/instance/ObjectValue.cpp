/*
 * Copyright (C) 2017 John M. Harris, Jr. <johnmh@openblox.org>
 *
 * This file is part of OpenBlox.
 *
 * OpenBlox is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenBlox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with OpenBlox. If not, see <https://www.gnu.org/licenses/>.
 */

#include "instance/ObjectValue.h"

#include "instance/NetworkReplicator.h"
#include "instance/NetworkServer.h"

namespace OB{
	namespace Instance{
		DEFINE_CLASS(ObjectValue, true, false, BaseValue){
			registerLuaClass(eng, LuaClassName, register_lua_metamethods, register_lua_methods, register_lua_property_getters, register_lua_property_setters, register_lua_events);
		}

		ObjectValue::ObjectValue(OBEngine* eng) : BaseValue(eng){
			Name = ClassName;

			Value = NULL;
		}

		ObjectValue::~ObjectValue(){}

		shared_ptr<Instance> ObjectValue::getValue(){
			return Value;
		}

		void ObjectValue::setValue(shared_ptr<Instance> value){
			if(Value != value){
				Value = value;

				REPLICATE_PROPERTY_CHANGE(Value);
				propertyChanged("Value");
			}
		}

		shared_ptr<Instance> ObjectValue::cloneImpl(){
			shared_ptr<ObjectValue> ov = make_shared<ObjectValue>(eng);
			ov->Archivable = Archivable;
			ov->Name = Name;
			ov->ParentLocked = ParentLocked;

			ov->Value = Value;

			return ov;
		}

#if HAVE_ENET
		void ObjectValue::replicateProperties(shared_ptr<NetworkReplicator> peer){
			Instance::replicateProperties(peer);

			peer->sendSetPropertyPacket(netId, "Value", make_shared<Type::VarWrapper>(Value));
		}
#endif

		std::map<std::string, _PropertyInfo> ObjectValue::getProperties(){
			std::map<std::string, _PropertyInfo> propMap = Instance::getProperties();
			propMap["Value"] = {"Instance", false, true, true};

			return propMap;
		}

		void ObjectValue::setProperty(std::string prop, shared_ptr<Type::VarWrapper> val){
			if(prop == "Value"){
				setValue(val->asInstance());
				return;
			}

			Instance::setProperty(prop, val);
		}

		shared_ptr<Type::VarWrapper> ObjectValue::getProperty(std::string prop){
			if(prop == "Value"){
				return make_shared<Type::VarWrapper>(getValue());
			}

			return Instance::getProperty(prop);
		}

		int ObjectValue::lua_setValue(lua_State* L){
			shared_ptr<Instance> inst = checkInstance(L, 1, false);

			if(inst){
				shared_ptr<ObjectValue> instIV = dynamic_pointer_cast<ObjectValue>(inst);
				if(instIV){
					shared_ptr<Instance> newV = checkInstance(L, 2, false);
					instIV->setValue(newV);
				}
			}

			return 0;
		}

		int ObjectValue::lua_getValue(lua_State* L){
			shared_ptr<Instance> inst = checkInstance(L, 1, false);

			if(inst){
				shared_ptr<ObjectValue> instIV = dynamic_pointer_cast<ObjectValue>(inst);
				if(instIV){
					shared_ptr<Instance> tV = instIV->getValue();
					if(tV){
						tV->wrap_lua(L);
					}else{
						lua_pushnil(L);
					}
					return 1;
				}
			}

			lua_pushnil(L);
			return 1;
		}

		void ObjectValue::register_lua_property_setters(lua_State* L){
			Instance::register_lua_property_setters(L);

			luaL_Reg properties[] = {
				{"Value", lua_setValue},
				{NULL, NULL}
			};
			luaL_setfuncs(L, properties, 0);
		}

		void ObjectValue::register_lua_property_getters(lua_State* L){
			Instance::register_lua_property_getters(L);

			luaL_Reg properties[] = {
				{"Value", lua_getValue},
				{NULL, NULL}
			};
			luaL_setfuncs(L, properties, 0);
		}
	}
}
