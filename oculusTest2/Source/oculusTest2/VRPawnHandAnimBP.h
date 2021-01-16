// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "VRPawnHandAnimBP.generated.h"

/**
 * 
 */
UCLASS()
class OCULUSTEST2_API UVRPawnHandAnimBP : public UAnimInstance
{
	GENERATED_BODY()
	public:
		UVRPawnHandAnimBP(const FObjectInitializer& ObjectInitializer);
		UFUNCTION()
		virtual void SetGrip(float a_fGrip);
	protected:
		float Grip;
	
};
