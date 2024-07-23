// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PaperZDEditor/Private/Graphs/Nodes/PaperZDAnimGraphNode_SetDirectionality.h"
#include "PaperZD/Public/AnimNodes/PaperZDAnimNode_SetDirectionality.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePaperZDAnimGraphNode_SetDirectionality() {}

// Begin Cross Module References
PAPERZD_API UScriptStruct* Z_Construct_UScriptStruct_FPaperZDAnimNode_SetDirectionality();
PAPERZDEDITOR_API UClass* Z_Construct_UClass_UPaperZDAnimGraphNode_Base();
PAPERZDEDITOR_API UClass* Z_Construct_UClass_UPaperZDAnimGraphNode_SetDirectionality();
PAPERZDEDITOR_API UClass* Z_Construct_UClass_UPaperZDAnimGraphNode_SetDirectionality_NoRegister();
UPackage* Z_Construct_UPackage__Script_PaperZDEditor();
// End Cross Module References

// Begin Class UPaperZDAnimGraphNode_SetDirectionality
void UPaperZDAnimGraphNode_SetDirectionality::StaticRegisterNativesUPaperZDAnimGraphNode_SetDirectionality()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UPaperZDAnimGraphNode_SetDirectionality);
UClass* Z_Construct_UClass_UPaperZDAnimGraphNode_SetDirectionality_NoRegister()
{
	return UPaperZDAnimGraphNode_SetDirectionality::StaticClass();
}
struct Z_Construct_UClass_UPaperZDAnimGraphNode_SetDirectionality_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Sets the directionality data for multi-directional sequence rendering.\n */" },
#endif
		{ "IncludePath", "Graphs/Nodes/PaperZDAnimGraphNode_SetDirectionality.h" },
		{ "ModuleRelativePath", "Private/Graphs/Nodes/PaperZDAnimGraphNode_SetDirectionality.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Sets the directionality data for multi-directional sequence rendering." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AnimNode_MetaData[] = {
		{ "Category", "Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/* Runtime node. */" },
#endif
		{ "ModuleRelativePath", "Private/Graphs/Nodes/PaperZDAnimGraphNode_SetDirectionality.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Runtime node." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_AnimNode;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UPaperZDAnimGraphNode_SetDirectionality>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UPaperZDAnimGraphNode_SetDirectionality_Statics::NewProp_AnimNode = { "AnimNode", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPaperZDAnimGraphNode_SetDirectionality, AnimNode), Z_Construct_UScriptStruct_FPaperZDAnimNode_SetDirectionality, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AnimNode_MetaData), NewProp_AnimNode_MetaData) }; // 762056205
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UPaperZDAnimGraphNode_SetDirectionality_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPaperZDAnimGraphNode_SetDirectionality_Statics::NewProp_AnimNode,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UPaperZDAnimGraphNode_SetDirectionality_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UPaperZDAnimGraphNode_SetDirectionality_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UPaperZDAnimGraphNode_Base,
	(UObject* (*)())Z_Construct_UPackage__Script_PaperZDEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UPaperZDAnimGraphNode_SetDirectionality_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UPaperZDAnimGraphNode_SetDirectionality_Statics::ClassParams = {
	&UPaperZDAnimGraphNode_SetDirectionality::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UPaperZDAnimGraphNode_SetDirectionality_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UPaperZDAnimGraphNode_SetDirectionality_Statics::PropPointers),
	0,
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UPaperZDAnimGraphNode_SetDirectionality_Statics::Class_MetaDataParams), Z_Construct_UClass_UPaperZDAnimGraphNode_SetDirectionality_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UPaperZDAnimGraphNode_SetDirectionality()
{
	if (!Z_Registration_Info_UClass_UPaperZDAnimGraphNode_SetDirectionality.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UPaperZDAnimGraphNode_SetDirectionality.OuterSingleton, Z_Construct_UClass_UPaperZDAnimGraphNode_SetDirectionality_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UPaperZDAnimGraphNode_SetDirectionality.OuterSingleton;
}
template<> PAPERZDEDITOR_API UClass* StaticClass<UPaperZDAnimGraphNode_SetDirectionality>()
{
	return UPaperZDAnimGraphNode_SetDirectionality::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UPaperZDAnimGraphNode_SetDirectionality);
UPaperZDAnimGraphNode_SetDirectionality::~UPaperZDAnimGraphNode_SetDirectionality() {}
// End Class UPaperZDAnimGraphNode_SetDirectionality

// Begin Registration
struct Z_CompiledInDeferFile_FID_Games_epic_drive_c_users_tbf_Documents_Unreal_Projects_GDTV_CrustyPirate_Project_Plugins_PaperZD_Source_PaperZDEditor_Private_Graphs_Nodes_PaperZDAnimGraphNode_SetDirectionality_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UPaperZDAnimGraphNode_SetDirectionality, UPaperZDAnimGraphNode_SetDirectionality::StaticClass, TEXT("UPaperZDAnimGraphNode_SetDirectionality"), &Z_Registration_Info_UClass_UPaperZDAnimGraphNode_SetDirectionality, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UPaperZDAnimGraphNode_SetDirectionality), 1888736817U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Games_epic_drive_c_users_tbf_Documents_Unreal_Projects_GDTV_CrustyPirate_Project_Plugins_PaperZD_Source_PaperZDEditor_Private_Graphs_Nodes_PaperZDAnimGraphNode_SetDirectionality_h_1205459094(TEXT("/Script/PaperZDEditor"),
	Z_CompiledInDeferFile_FID_Games_epic_drive_c_users_tbf_Documents_Unreal_Projects_GDTV_CrustyPirate_Project_Plugins_PaperZD_Source_PaperZDEditor_Private_Graphs_Nodes_PaperZDAnimGraphNode_SetDirectionality_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Games_epic_drive_c_users_tbf_Documents_Unreal_Projects_GDTV_CrustyPirate_Project_Plugins_PaperZD_Source_PaperZDEditor_Private_Graphs_Nodes_PaperZDAnimGraphNode_SetDirectionality_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
