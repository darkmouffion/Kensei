// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ShinkenMotion.generated.h"

/**
 * 
 */
UCLASS()
class KENSEI_API UShinkenMotion : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Kenjutsu")
		static FString decodeTechnique(TArray<FString> sequence, float longN, float longE, float longS, float longW);

};
