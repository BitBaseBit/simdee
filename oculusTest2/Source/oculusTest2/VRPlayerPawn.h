// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"
#include "VRPawnHandAnimBP.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "VRPlayerPawn.generated.h"

UCLASS()
class OCULUSTEST2_API AVRPlayerPawn : public APawn 
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPlayerPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* VRRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* VRCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMotionControllerComponent* LeftHandController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMotionControllerComponent* RightHandController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* LeftHandMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* RightHandMesh;

	UVRPawnHandAnimBP* LeftHandAnimBP;
	UVRPawnHandAnimBP* RightHandAnimBP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USplineComponent* Arc;

	bool TeleportActive;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Arc variables
	FPredictProjectilePathResult Result;
	bool HitResult;
	UStaticMesh* beamMesh;
	TArray<USplineMeshComponent*> SplineMeshes;
	TArray<FVector> SplinePoints;
	float ArcVelocity = 900.0f;
	USplineMeshComponent* SplineMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//BlueprintNativeEvent: Function which has a C++ implementation,
	//but can be overriden by Blueprints.
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void GripLeftHand_Pressed();

	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void GripRightHand_Pressed();

	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void GripLeftHand_Released();

	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void GripRightHand_Released();
	FPredictProjectilePathPointData* result;

	void TeleportLeft();
	void TeleportLeftReleased();
	void TeleportRight();
	void TeleportRightReleased();

	void DrawArc();
	void ClearArc();

	void TeleportToLocation();
};
