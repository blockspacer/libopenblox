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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with OpenBlox.	 If not, see <https://www.gnu.org/licenses/>.
 */

#include "oblibconfig.h"

#if HAVE_PUGIXML
#include "instance/Instance.h"
#endif

#include <string>
#include <map>

#ifndef OB_OBSERIALIZER
#define OB_OBSERIALIZER

// We're on version 1 of the XML format
#define OB_SERIALIZER_XML_CURRENT_VERSION_ID 1

namespace OB{
	class OBEngine;
	
	class OBSerializer{
		public:
			OBSerializer(OBEngine* eng);
			
			#if HAVE_PUGIXML
			shared_ptr<Instance::Instance> LoadModel(std::string resURI);
			shared_ptr<Instance::Instance> Load(std::string resURI);
		    bool SaveModel(shared_ptr<Instance::Instance> model, std::string file);
			std::string SaveModelInMemory(shared_ptr<Instance::Instance> model);
			bool Save(std::string file);
			std::string SaveInMemory();
			#endif

			std::string GetID(shared_ptr<Instance::Instance> inst);
			void SetID(shared_ptr<Instance::Instance> inst, std::string newId);
			
		private:
			OBEngine* eng;
			
			std::map<shared_ptr<Instance::Instance>, std::string> instanceMap;
			int dynamic_instance_count;
	};
}

#endif // OB_OBSERIALIZER

// Local Variables:
// mode: c++
// End: