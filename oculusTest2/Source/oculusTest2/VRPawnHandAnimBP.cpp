// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawnHandAnimBP.h"

UVRPawnHandAnimBP::UVRPawnHandAnimBP(const FObjectInitializer& ObjectInitializer)
{
	//set any default values for your variables here
	Grip = 0.0f;
}

void UVRPawnHandAnimBP::SetGrip(float a_fGrip)
{
	Grip = a_fGrip;
}
