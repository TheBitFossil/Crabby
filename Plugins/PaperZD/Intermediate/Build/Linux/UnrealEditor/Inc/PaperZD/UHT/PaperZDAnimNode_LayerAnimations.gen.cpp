// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PaperZD/Public/AnimNodes/PaperZDAnimNode_LayerAnimations.h"
#include "PaperZD/Public/AnimNodes/PaperZDAnimNode_Base.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePaperZDAnimNode_LayerAnimations() {}

// Begin Cross Module References
PAPERZD_API UScriptStruct* Z_Construct_UScriptStruct_FPaperZDAnimDataLink();
PAPERZD_API UScriptStruct* Z_Construct_UScriptStruct_FPaperZDAnimNode_Base();
PAPERZD_API UScriptStruct* Z_Construct_UScriptStruct_FPaperZDAnimNode_LayerAnimations();
UPackage* Z_Construct_UPackage__Script_PaperZD();
// End Cross Module References

// Begin ScriptStruct FPaperZDAnimNode_LayerAnimations
static_assert(std::is_polymorphic<FPaperZDAnimNode_LayerAnimations>() == std::is_polymorphic<FPaperZDAnimNode_Base>(), "USTRUCT FPaperZDAnimNode_LayerAnimations cannot be polymorphic unless super FPaperZDAnimNode_Base is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_PaperZDAnimNode_LayerAnimations;
class UScriptStruct* FPaperZDAnimNode_LayerAnimations::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_PaperZDAnimNode_LayerAnimations.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_PaperZDAnimNode_LayerAnimations.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FPaperZDAnimNode_LayerAnimations, (UObject*)Z_Construct_UPackage__Script_PaperZD(), TEXT("PaperZDAnimNode_LayerAnimations"));
	}
	return Z_Registration_Info_UScriptStruct_PaperZDAnimNode_LayerAnimations.OuterSingleton;
}
template<> PAPERZD_API UScriptStruct* StaticStruct<FPaperZDAnimNode_LayerAnimations>()
{
	return FPaperZDAnimNode_LayerAnimations::StaticStruct();
}
struct Z_Construct_UScriptStruct_FPaperZDAnimNode_LayerAnimations_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Sets the animations in different weighted layers, running parallel and independent to each other.\n */" },
#endif
		{ "ModuleRelativePath", "Public/AnimNodes/PaperZDAnimNode_LayerAnimations.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Sets the animations in different weighted layers, running parallel and independent to each other." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AnimationLayer_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/* Animation entry. */" },
#endif
		{ "ModuleRelativePath", "Public/AnimNodes/PaperZDAnimNode_LayerAnimations.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Animation entry." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LayerWeight_MetaData[] = {
		{ "Category", "Input" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/* Weights for each layer. */" },
#endif
		{ "ModuleRelativePath", "Public/AnimNodes/PaperZDAnimNode_LayerAnimations.h" },
		{ "ShowPinByDefault", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Weights for each layer." },
#endif
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_AnimationLayer_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_AnimationLayer;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LayerWeight_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_LayerWeight;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FPaperZDAnimNode_LayerAnimations>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FPaperZDAnimNode_LayerAnimations_Statics::NewProp_AnimationLayer_Inner = { "AnimationLayer", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FPaperZDAnimDataLink, METADATA_PARAMS(0, nullptr) }; // 4293149857
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FPaperZDAnimNode_LayerAnimations_Statics::NewProp_AnimationLayer = { "AnimationLayer", nullptr, (EPropertyFlags)0x0010000000000041, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPaperZDAnimNode_LayerAnimations, AnimationLayer), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AnimationLayer_MetaData), NewProp_AnimationLayer_MetaData) }; // 4293149857
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FPaperZDAnimNode_LayerAnimations_Statics::NewProp_LayerWeight_Inner = { "LayerWeight", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FPaperZDAnimNode_LayerAnimations_Statics::NewProp_LayerWeight = { "LayerWeight", nullptr, (EPropertyFlags)0x0010000000000041, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPaperZDAnimNode_LayerAnimations, LayerWeight), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LayerWeight_MetaData), NewProp_LayerWeight_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FPaperZDAnimNode_LayerAnimations_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPaperZDAnimNode_LayerAnimations_Statics::NewProp_AnimationLayer_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPaperZDAnimNode_LayerAnimations_Statics::NewProp_AnimationLayer,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPaperZDAnimNode_LayerAnimations_Statics::NewProp_LayerWeight_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPaperZDAnimNode_LayerAnimations_Statics::NewProp_LayerWeight,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPaperZDAnimNode_LayerAnimations_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FPaperZDAnimNode_LayerAnimations_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_PaperZD,
	Z_Construct_UScriptStruct_FPaperZDAnimNode_Base,
	&NewStructOps,
	"PaperZDAnimNode_LayerAnimations",
	Z_Construct_UScriptStruct_FPaperZDAnimNode_LayerAnimations_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPaperZDAnimNode_LayerAnimations_Statics::PropPointers),
	sizeof(FPaperZDAnimNode_LayerAnimations),
	alignof(FPaperZDAnimNode_LayerAnimations),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPaperZDAnimNode_LayerAnimations_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FPaperZDAnimNode_LayerAnimations_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FPaperZDAnimNode_LayerAnimations()
{
	if (!Z_Registration_Info_UScriptStruct_PaperZDAnimNode_LayerAnimations.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_PaperZDAnimNode_LayerAnimations.InnerSingleton, Z_Construct_UScriptStruct_FPaperZDAnimNode_LayerAnimations_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_PaperZDAnimNode_LayerAnimations.InnerSingleton;
}
// End ScriptStruct FPaperZDAnimNode_LayerAnimations

// Begin Registration
struct Z_CompiledInDeferFile_FID_Games_epic_drive_c_users_tbf_Documents_Unreal_Projects_GDTV_CrustyPirate_Project_Plugins_PaperZD_Source_PaperZD_Public_AnimNodes_PaperZDAnimNode_LayerAnimations_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FPaperZDAnimNode_LayerAnimations::StaticStruct, Z_Construct_UScriptStruct_FPaperZDAnimNode_LayerAnimations_Statics::NewStructOps, TEXT("PaperZDAnimNode_LayerAnimations"), &Z_Registration_Info_UScriptStruct_PaperZDAnimNode_LayerAnimations, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FPaperZDAnimNode_LayerAnimations), 2565907054U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Games_epic_drive_c_users_tbf_Documents_Unreal_Projects_GDTV_CrustyPirate_Project_Plugins_PaperZD_Source_PaperZD_Public_AnimNodes_PaperZDAnimNode_LayerAnimations_h_3703789235(TEXT("/Script/PaperZD"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Games_epic_drive_c_users_tbf_Documents_Unreal_Projects_GDTV_CrustyPirate_Project_Plugins_PaperZD_Source_PaperZD_Public_AnimNodes_PaperZDAnimNode_LayerAnimations_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Games_epic_drive_c_users_tbf_Documents_Unreal_Projects_GDTV_CrustyPirate_Project_Plugins_PaperZD_Source_PaperZD_Public_AnimNodes_PaperZDAnimNode_LayerAnimations_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
