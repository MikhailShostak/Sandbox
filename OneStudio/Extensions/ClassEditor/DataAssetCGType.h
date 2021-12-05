#pragma once

#include "ClassCGType.h"

namespace LegacyClassGen
{

class DataAssetCGType : public LegacyClassGen::ClassCGType
{
public:
    void generate() override
    {
		String baseType;
		data.read("BaseType", baseType);
		String namespaceName;
		data.read("Namespace", namespaceName);

		String assetName = path.baseName();

		Array<String> globalDependencies = { "Experimental", "AssetManager.gen.h", };
		addDependencies(baseType, globalDependencies);

		pushBuffer();
		generateValues(this, "asset", globalDependencies);
		String values = popBuffer();

		pushBuffer();
		if(!namespaceName.empty())
		{
			write("namespace " + resolveType(namespaceName) + "{\n");
		}
		String assetType = "DynamicAsset<" + resolveType(baseType) + ">";
		String package = !namespaceName.empty() ? namespaceName + "." + assetName : assetName;
		write("inline ");
		generateField(assetType, assetName + "_Asset", assetType + "(\"" + package + "\", [](auto &asset){\n" + values + "})");
		if(!namespaceName.empty())
		{
			write("}\n");
		}
		String implementation = popBuffer();
		
		writeGeneratedFile2("h", {
			{ "Includes", [&]() {
				generateIncludes(globalDependencies);
			} },
			{ "Implementation",[&]() {
				write(implementation);
			} },
		});
	}
};

}
