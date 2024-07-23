// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PaperZD/Public/AnimSequences/PaperZDAnimSequence.h"
#include "Serialization/ArchiveUObjectFromStructuredArchive.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePaperZDAnimSequence() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
PAPER2D_API UClass* Z_Construct_UClass_UPaperFlipbook_NoRegister();
PAPERZD_API UClass* Z_Construct_UClass_UPaperZDAnimationSource_NoRegister();
PAPERZD_API UClass* Z_Construct_UClass_UPaperZDAnimBP_NoRegister();
PAPERZD_API UClass* Z_Construct_UClass_UPaperZDAnimNotify_Base_NoRegister();
PAPERZD_API UClass* Z_Construct_UClass_UPaperZDAnimSequence();
PAPERZD_API UClass* Z_Construct_UClass_UPaperZDAnimSequence_NoRegister();
PAPERZD_API UScriptStruct* Z_Construct_UScriptStruct_FPaperZDAnimTrackMetadata();
UPackage* Z_Construct_UPackage__Script_PaperZD();
// End Cross Module References

// Begin ScriptStruct FPaperZDAnimTrackMetadata
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_PaperZDAnimTrackMetadata;
class UScriptStruct* FPaperZDAnimTrackMetadata::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_PaperZDAnimTrackMetadata.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_PaperZDAnimTrackMetadata.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FPaperZDAnimTrackMetadata, (UObject*)Z_Construct_UPackage__Script_PaperZD(), TEXT("PaperZDAnimTrackMetadata"));
	}
	return Z_Registration_Info_UScriptStruct_PaperZDAnimTrackMetadata.OuterSingleton;
}
template<> PAPERZD_API UScriptStruct* StaticStruct<FPaperZDAnimTrackMetadata>()
{
	return FPaperZDAnimTrackMetadata::StaticStruct();
}
struct Z_Construct_UScriptStruct_FPaperZDAnimTrackMetadata_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Stores the meta-information of a track used to display AnimNotify information in an orderly manner.\n */" },
#endif
		{ "ModuleRelativePath", "Public/AnimSequences/PaperZDAnimSequence.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Stores the meta-information of a track used to display AnimNotify information in an orderly manner." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Color_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/* Color used to display the track visually. */" },
#endif
		{ "ModuleRelativePath", "Public/AnimSequences/PaperZDAnimSequence.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Color used to display the track visually." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/* Editor name for the track. */" },
#endif
		{ "ModuleRelativePath", "Public/AnimSequences/PaperZDAnimSequence.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Editor name for the track." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Color;
	static const UECodeGen_Private::FNamePropertyParams NewProp_DisplayName;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FPaperZDAnimTrackMetadata>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FPaperZDAnimTrackMetadata_Statics::NewProp_Color = { "Color", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPaperZDAnimTrackMetadata, Color), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Color_MetaData), NewProp_Color_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FPaperZDAnimTrackMetadata_Statics::NewProp_DisplayName = { "DisplayName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FPaperZDAnimTrackMetadata, DisplayName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayName_MetaData), NewProp_DisplayName_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FPaperZDAnimTrackMetadata_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPaperZDAnimTrackMetadata_Statics::NewProp_Color,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPaperZDAnimTrackMetadata_Statics::NewProp_DisplayName,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPaperZDAnimTrackMetadata_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FPaperZDAnimTrackMetadata_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_PaperZD,
	nullptr,
	&NewStructOps,
	"PaperZDAnimTrackMetadata",
	Z_Construct_UScriptStruct_FPaperZDAnimTrackMetadata_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPaperZDAnimTrackMetadata_Statics::PropPointers),
	sizeof(FPaperZDAnimTrackMetadata),
	alignof(FPaperZDAnimTrackMetadata),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPaperZDAnimTrackMetadata_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FPaperZDAnimTrackMetadata_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FPaperZDAnimTrackMetadata()
{
	if (!Z_Registration_Info_UScriptStruct_PaperZDAnimTrackMetadata.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_PaperZDAnimTrackMetadata.InnerSingleton, Z_Construct_UScriptStruct_FPaperZDAnimTrackMetadata_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_PaperZDAnimTrackMetadata.InnerSingleton;
}
// End ScriptStruct FPaperZDAnimTrackMetadata

// Begin Class UPaperZDAnimSequence Function GetFramesPerSecond
struct Z_Construct_UFunction_UPaperZDAnimSequence_GetFramesPerSecond_Statics
{
	struct PaperZDAnimSequence_eventGetFramesPerSecond_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AnimSequence" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/* Frames per second, used to show the grid on the AnimSequence editor */" },
#endif
		{ "ModuleRelativePath", "Public/AnimSequences/PaperZDAnimSequence.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Frames per second, used to show the grid on the AnimSequence editor" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UPaperZDAnimSequence_GetFramesPerSecond_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PaperZDAnimSequence_eventGetFramesPerSecond_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UPaperZDAnimSequence_GetFramesPerSecond_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPaperZDAnimSequence_GetFramesPerSecond_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UPaperZDAnimSequence_GetFramesPerSecond_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UPaperZDAnimSequence_GetFramesPerSecond_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UPaperZDAnimSequence, nullptr, "GetFramesPerSecond", nullptr, nullptr, Z_Construct_UFunction_UPaperZDAnimSequence_GetFramesPerSecond_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UPaperZDAnimSequence_GetFramesPerSecond_Statics::PropPointers), sizeof(Z_Construct_UFunction_UPaperZDAnimSequence_GetFramesPerSecond_Statics::PaperZDAnimSequence_eventGetFramesPerSecond_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UPaperZDAnimSequence_GetFramesPerSecond_Statics::Function_MetaDataParams), Z_Construct_UFunction_UPaperZDAnimSequence_GetFramesPerSecond_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UPaperZDAnimSequence_GetFramesPerSecond_Statics::PaperZDAnimSequence_eventGetFramesPerSecond_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UPaperZDAnimSequence_GetFramesPerSecond()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UPaperZDAnimSequence_GetFramesPerSecond_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UPaperZDAnimSequence::execGetFramesPerSecond)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetFramesPerSecond();
	P_NATIVE_END;
}
// End Class UPaperZDAnimSequence Function GetFramesPerSecond

// Begin Class UPaperZDAnimSequence Function GetTotalDuration
struct Z_Construct_UFunction_UPaperZDAnimSequence_GetTotalDuration_Statics
{
	struct PaperZDAnimSequence_eventGetTotalDuration_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AnimSequence" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/* Total duration of this Sequence, should be overridden */" },
#endif
		{ "ModuleRelativePath", "Public/AnimSequences/PaperZDAnimSequence.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Total duration of this Sequence, should be overridden" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UPaperZDAnimSequence_GetTotalDuration_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PaperZDAnimSequence_eventGetTotalDuration_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UPaperZDAnimSequence_GetTotalDuration_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPaperZDAnimSequence_GetTotalDuration_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UPaperZDAnimSequence_GetTotalDuration_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UPaperZDAnimSequence_GetTotalDuration_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UPaperZDAnimSequence, nullptr, "GetTotalDuration", nullptr, nullptr, Z_Construct_UFunction_UPaperZDAnimSequence_GetTotalDuration_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UPaperZDAnimSequence_GetTotalDuration_Statics::PropPointers), sizeof(Z_Construct_UFunction_UPaperZDAnimSequence_GetTotalDuration_Statics::PaperZDAnimSequence_eventGetTotalDuration_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UPaperZDAnimSequence_GetTotalDuration_Statics::Function_MetaDataParams), Z_Construct_UFunction_UPaperZDAnimSequence_GetTotalDuration_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UPaperZDAnimSequence_GetTotalDuration_Statics::PaperZDAnimSequence_eventGetTotalDuration_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UPaperZDAnimSequence_GetTotalDuration()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UPaperZDAnimSequence_GetTotalDuration_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UPaperZDAnimSequence::execGetTotalDuration)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetTotalDuration();
	P_NATIVE_END;
}
// End Class UPaperZDAnimSequence Function GetTotalDuration

// Begin Class UPaperZDAnimSequence
void UPaperZDAnimSequence::StaticRegisterNativesUPaperZDAnimSequence()
{
	UClass* Class = UPaperZDAnimSequence::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetFramesPerSecond", &UPaperZDAnimSequence::execGetFramesPerSecond },
		{ "GetTotalDuration", &UPaperZDAnimSequence::execGetTotalDuration },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UPaperZDAnimSequence);
UClass* Z_Construct_UClass_UPaperZDAnimSequence_NoRegister()
{
	return UPaperZDAnimSequence::StaticClass();
}
struct Z_Construct_UClass_UPaperZDAnimSequence_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * The AnimSequence is the class responsible of handling how a given Animation source plays on the registered RenderComponent and handling meta info like AnimNotifies. \n */" },
#endif
		{ "IncludePath", "AnimSequences/PaperZDAnimSequence.h" },
		{ "ModuleRelativePath", "Public/AnimSequences/PaperZDAnimSequence.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The AnimSequence is the class responsible of handling how a given Animation source plays on the registered RenderComponent and handling meta info like AnimNotifies." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AnimSource_MetaData[] = {
		{ "Category", "Animation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/* Animation source that owns this sequence. */" },
#endif
		{ "ModuleRelativePath", "Public/AnimSequences/PaperZDAnimSequence.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Animation source that owns this sequence." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AnimNotifies_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/* The list of the AnimNotifies linked to this animation. */" },
#endif
		{ "ModuleRelativePath", "Public/AnimSequences/PaperZDAnimSequence.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The list of the AnimNotifies linked to this animation." },
#endif
	};
#if WITH_EDITORONLY_DATA
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AnimBP_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/* DEPRECATED: Points to the AnimBP that owned this AnimSequence before the creation of AnimSources. */" },
#endif
		{ "ModuleRelativePath", "Public/AnimSequences/PaperZDAnimSequence.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "DEPRECATED: Points to the AnimBP that owned this AnimSequence before the creation of AnimSources." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AnimTrackData_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/* Track meta information for editor display. */" },
#endif
		{ "ModuleRelativePath", "Public/AnimSequences/PaperZDAnimSequence.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Track meta information for editor display." },
#endif
	};
#endif // WITH_EDITORONLY_DATA
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[] = {
		{ "ModuleRelativePath", "Public/AnimSequences/PaperZDAnimSequence.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PaperFlipbook_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//@Deprecated\n" },
#endif
		{ "ModuleRelativePath", "Public/AnimSequences/PaperZDAnimSequence.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "@Deprecated" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDirectionalSequence_MetaData[] = {
		{ "Category", "AnimSequence" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * If true, multiple animations sources can be added to this sequence at different angles.\n\x09 * Used for when the sequence needs to represent multiple rotations of the same animation (i.e. top-down and isometric games).\n\x09 */" },
#endif
		{ "DisplayName", "Multi-Directional Sequence" },
		{ "ModuleRelativePath", "Public/AnimSequences/PaperZDAnimSequence.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, multiple animations sources can be added to this sequence at different angles.\nUsed for when the sequence needs to represent multiple rotations of the same animation (i.e. top-down and isometric games)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DirectionalAngleOffset_MetaData[] = {
		{ "Category", "AnimSequence" },
		{ "ClampMax", "45.0" },
		{ "ClampMin", "-45.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Offset applied to all the animations on the directional map.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/AnimSequences/PaperZDAnimSequence.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Offset applied to all the animations on the directional map." },
#endif
		{ "UIMax", "45.0" },
		{ "UIMin", "-45.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Category_MetaData[] = {
		{ "Category", "AnimSequence" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/* The category of this sequence, displayed on the tree view on the AnimSequence editor. */" },
#endif
		{ "ModuleRelativePath", "Public/AnimSequences/PaperZDAnimSequence.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The category of this sequence, displayed on the tree view on the AnimSequence editor." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AnimSource;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AnimNotifies_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_AnimNotifies;
#if WITH_EDITORONLY_DATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AnimBP;
	static const UECodeGen_Private::FStructPropertyParams NewProp_AnimTrackData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_AnimTrackData;
#endif // WITH_EDITORONLY_DATA
	static const UECodeGen_Private::FNamePropertyParams NewProp_DisplayName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PaperFlipbook;
	static void NewProp_bDirectionalSequence_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDirectionalSequence;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DirectionalAngleOffset;
	static const UECodeGen_Private::FNamePropertyParams NewProp_Category;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UPaperZDAnimSequence_GetFramesPerSecond, "GetFramesPerSecond" }, // 340825692
		{ &Z_Construct_UFunction_UPaperZDAnimSequence_GetTotalDuration, "GetTotalDuration" }, // 716292394
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UPaperZDAnimSequence>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_AnimSource = { "AnimSource", nullptr, (EPropertyFlags)0x0144010000020001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPaperZDAnimSequence, AnimSource), Z_Construct_UClass_UPaperZDAnimationSource_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AnimSource_MetaData), NewProp_AnimSource_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_AnimNotifies_Inner = { "AnimNotifies", nullptr, (EPropertyFlags)0x0104000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UPaperZDAnimNotify_Base_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_AnimNotifies = { "AnimNotifies", nullptr, (EPropertyFlags)0x0144000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPaperZDAnimSequence, AnimNotifies), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AnimNotifies_MetaData), NewProp_AnimNotifies_MetaData) };
#if WITH_EDITORONLY_DATA
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_AnimBP = { "AnimBP", nullptr, (EPropertyFlags)0x0040010820000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPaperZDAnimSequence, AnimBP_DEPRECATED), Z_Construct_UClass_UPaperZDAnimBP_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AnimBP_MetaData), NewProp_AnimBP_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_AnimTrackData_Inner = { "AnimTrackData", nullptr, (EPropertyFlags)0x0000000800000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FPaperZDAnimTrackMetadata, METADATA_PARAMS(0, nullptr) }; // 3767701936
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_AnimTrackData = { "AnimTrackData", nullptr, (EPropertyFlags)0x0040000800000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPaperZDAnimSequence, AnimTrackData), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AnimTrackData_MetaData), NewProp_AnimTrackData_MetaData) }; // 3767701936
#endif // WITH_EDITORONLY_DATA
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_DisplayName = { "DisplayName", nullptr, (EPropertyFlags)0x0010000020000000, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPaperZDAnimSequence, DisplayName_DEPRECATED), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayName_MetaData), NewProp_DisplayName_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_PaperFlipbook = { "PaperFlipbook", nullptr, (EPropertyFlags)0x0010000020000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPaperZDAnimSequence, PaperFlipbook_DEPRECATED), Z_Construct_UClass_UPaperFlipbook_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PaperFlipbook_MetaData), NewProp_PaperFlipbook_MetaData) };
void Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_bDirectionalSequence_SetBit(void* Obj)
{
	((UPaperZDAnimSequence*)Obj)->bDirectionalSequence = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_bDirectionalSequence = { "bDirectionalSequence", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UPaperZDAnimSequence), &Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_bDirectionalSequence_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDirectionalSequence_MetaData), NewProp_bDirectionalSequence_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_DirectionalAngleOffset = { "DirectionalAngleOffset", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPaperZDAnimSequence, DirectionalAngleOffset), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DirectionalAngleOffset_MetaData), NewProp_DirectionalAngleOffset_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010010000000015, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPaperZDAnimSequence, Category), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Category_MetaData), NewProp_Category_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UPaperZDAnimSequence_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_AnimSource,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_AnimNotifies_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_AnimNotifies,
#if WITH_EDITORONLY_DATA
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_AnimBP,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_AnimTrackData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_AnimTrackData,
#endif // WITH_EDITORONLY_DATA
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_DisplayName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_PaperFlipbook,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_bDirectionalSequence,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_DirectionalAngleOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPaperZDAnimSequence_Statics::NewProp_Category,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UPaperZDAnimSequence_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UPaperZDAnimSequence_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_PaperZD,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UPaperZDAnimSequence_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UPaperZDAnimSequence_Statics::ClassParams = {
	&UPaperZDAnimSequence::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UPaperZDAnimSequence_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UPaperZDAnimSequence_Statics::PropPointers),
	0,
	0x001000A1u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UPaperZDAnimSequence_Statics::Class_MetaDataParams), Z_Construct_UClass_UPaperZDAnimSequence_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UPaperZDAnimSequence()
{
	if (!Z_Registration_Info_UClass_UPaperZDAnimSequence.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UPaperZDAnimSequence.OuterSingleton, Z_Construct_UClass_UPaperZDAnimSequence_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UPaperZDAnimSequence.OuterSingleton;
}
template<> PAPERZD_API UClass* StaticClass<UPaperZDAnimSequence>()
{
	return UPaperZDAnimSequence::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UPaperZDAnimSequence);
UPaperZDAnimSequence::~UPaperZDAnimSequence() {}
IMPLEMENT_FSTRUCTUREDARCHIVE_SERIALIZER(UPaperZDAnimSequence)
// End Class UPaperZDAnimSequence

// Begin Registration
struct Z_CompiledInDeferFile_FID_Games_epic_drive_c_users_tbf_Documents_Unreal_Projects_GDTV_CrustyPirate_Project_Plugins_PaperZD_Source_PaperZD_Public_AnimSequences_PaperZDAnimSequence_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FPaperZDAnimTrackMetadata::StaticStruct, Z_Construct_UScriptStruct_FPaperZDAnimTrackMetadata_Statics::NewStructOps, TEXT("PaperZDAnimTrackMetadata"), &Z_Registration_Info_UScriptStruct_PaperZDAnimTrackMetadata, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FPaperZDAnimTrackMetadata), 3767701936U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UPaperZDAnimSequence, UPaperZDAnimSequence::StaticClass, TEXT("UPaperZDAnimSequence"), &Z_Registration_Info_UClass_UPaperZDAnimSequence, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UPaperZDAnimSequence), 1768216682U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Games_epic_drive_c_users_tbf_Documents_Unreal_Projects_GDTV_CrustyPirate_Project_Plugins_PaperZD_Source_PaperZD_Public_AnimSequences_PaperZDAnimSequence_h_607784398(TEXT("/Script/PaperZD"),
	Z_CompiledInDeferFile_FID_Games_epic_drive_c_users_tbf_Documents_Unreal_Projects_GDTV_CrustyPirate_Project_Plugins_PaperZD_Source_PaperZD_Public_AnimSequences_PaperZDAnimSequence_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Games_epic_drive_c_users_tbf_Documents_Unreal_Projects_GDTV_CrustyPirate_Project_Plugins_PaperZD_Source_PaperZD_Public_AnimSequences_PaperZDAnimSequence_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Games_epic_drive_c_users_tbf_Documents_Unreal_Projects_GDTV_CrustyPirate_Project_Plugins_PaperZD_Source_PaperZD_Public_AnimSequences_PaperZDAnimSequence_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Games_epic_drive_c_users_tbf_Documents_Unreal_Projects_GDTV_CrustyPirate_Project_Plugins_PaperZD_Source_PaperZD_Public_AnimSequences_PaperZDAnimSequence_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
