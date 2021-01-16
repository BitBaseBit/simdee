// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPlayerPawn.h"
//#include "Kismet/GameplayStaticsTypes.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AVRPlayerPawn::AVRPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent
	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	RootComponent = VRRoot;

	//HMD Camera
	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(RootComponent);

	//Left Hand Controller
	LeftHandController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftHandController"));
	LeftHandController->SetTrackingSource(EControllerHand::Left);
	LeftHandController->SetupAttachment(RootComponent);

	//Right Hand Controller
	RightHandController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightHandController"));
	RightHandController->SetTrackingSource(EControllerHand::Right);
	RightHandController->SetupAttachment(RootComponent);

	//Left Hand Mesh
	LeftHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHandMesh"));
	LeftHandMesh->SetAutoActivate(true);
	LeftHandMesh->SetVisibility(true);
	LeftHandMesh->SetHiddenInGame(false);
	LeftHandMesh->SetupAttachment(LeftHandController);

	//Right Hand Mesh
	RightHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHandMesh"));
	RightHandMesh->SetAutoActivate(true);
	RightHandMesh->SetVisibility(true);
	RightHandMesh->SetHiddenInGame(false);
	RightHandMesh->SetupAttachment(RightHandController);

	//Arc
	Arc = CreateDefaultSubobject<USplineComponent>(TEXT("Arc"));
	Arc->SetupAttachment(RightHandMesh);

	beamMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("BeamMesh"));

	TeleportActive = false;

}

// Called when the game starts or when spawned
void AVRPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	//Cache Left and Right hand animation BPs
	//LeftHandAnimBP = Cast<UVRPawnHandAnimBP>(LeftHandMesh->GetAnimInstance());
	//RightHandAnimBP = Cast<UVRPawnHandAnimBP>(RightHandMesh->GetAnimInstance());

}

// Called every frame
void AVRPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Arc && !TeleportActive)
	{
		ClearArc();
	}
	if (TeleportActive)
	{
		DrawArc();
	}
	if (!TeleportActive && HitResult)
	{
		TeleportToLocation();
	}
}

void AVRPlayerPawn::DrawArc()
{
	FVector ArcLocation = RightHandMesh->GetComponentLocation();

	FPredictProjectilePathParams Params = FPredictProjectilePathParams(0.0f, ArcLocation, RightHandMesh->GetForwardVector() * ArcVelocity, 2.0f);
	Params.bTraceWithCollision = true;
	Params.bTraceComplex = false;
	Params.TraceChannel = ECollisionChannel::ECC_WorldStatic;

	HitResult = UGameplayStatics::PredictProjectilePath(GetWorld(), Params, Result);

	//If we hit something
	if (HitResult)
	{
		for (FPredictProjectilePathPointData _result : Result.PathData)
		{
			SplinePoints.Add(_result.Location);
			Arc->AddSplinePoint(_result.Location, ESplineCoordinateSpace::World);
			result = &_result;
		}
	}

	if (Arc)
	{
		Arc->SetSplinePointType(Result.PathData.Num() - 1, ESplinePointType::CurveClamped);

		for (int32 i = 0; i < SplinePoints.Num() - 2; i++)
		{
			SplineMesh = NewObject<USplineMeshComponent>();
			SplineMesh->RegisterComponentWithWorld(GetWorld());
			SplineMesh->SetStaticMesh(beamMesh);
			SplineMeshes.Add(SplineMesh);

			FVector Start = SplinePoints[i];
			FVector End = SplinePoints[i + 1];
			FVector sTan = FVector::ZeroVector;
			FVector eTan = FVector::ZeroVector;

			SplineMesh->SetStartAndEnd(Start, sTan, End, eTan);
		}
	}

}


void AVRPlayerPawn::ClearArc() 
{
	Arc->ClearSplinePoints();
	SplinePoints.Empty();

	for (int32 i = SplineMeshes.Num() - 1; i >= 0; i--)
	{
		if (SplineMeshes[i])
			SplineMeshes[i]->DestroyComponent();
	}

	SplineMesh->DestroyComponent();

}

void AVRPlayerPawn::TeleportToLocation()
{
	RightHandController->SetWorldLocation(result->Location);
	HitResult = false;
}

//NOTE: BlueprintNativeEvent functions need the _Implementation suffix!

void AVRPlayerPawn::GripLeftHand_Pressed_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Grip Left Hand Pressed"));
	LeftHandAnimBP->SetGrip(1.0f);
}

void AVRPlayerPawn::GripRightHand_Pressed_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Grip Right Hand Pressed"));
	RightHandAnimBP->SetGrip(1.0f);
}

void AVRPlayerPawn::GripLeftHand_Released_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Grip Left Hand Released"));
	LeftHandAnimBP->SetGrip(0.0f);
}

void AVRPlayerPawn::GripRightHand_Released_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Grip Right Hand Released"));
	RightHandAnimBP->SetGrip(0.0f);
}

void AVRPlayerPawn::TeleportLeft()
{
	UE_LOG(LogTemp, Log, TEXT("Teleport Left Pressed"));
}

void AVRPlayerPawn::TeleportLeftReleased()
{
	UE_LOG(LogTemp, Log, TEXT("Teleport Left Released"));
}

void AVRPlayerPawn::TeleportRight()
{
	TeleportActive = true;
}

void AVRPlayerPawn::TeleportRightReleased()
{
	TeleportActive = false;
}

// Called to bind functionality to input
void AVRPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind Grab Left and Right actions
	//PlayerInputComponent->BindAction("GrabLeft", IE_Pressed, this, &AVRPlayerPawn::GripLeftHand_Pressed);
	//PlayerInputComponent->BindAction("GrabLeft", IE_Released, this, &AVRPlayerPawn::GripLeftHand_Released);
	//PlayerInputComponent->BindAction("GrabRight", IE_Pressed, this, &AVRPlayerPawn::GripRightHand_Pressed);
	//PlayerInputComponent->BindAction("GrabRight", IE_Released, this, &AVRPlayerPawn::GripRightHand_Released);

	//Bind Teleport Left and Right actions
	PlayerInputComponent->BindAction("TeleportLeft", IE_Pressed, this, &AVRPlayerPawn::TeleportLeft);
	PlayerInputComponent->BindAction("TeleportLeft", IE_Released, this, &AVRPlayerPawn::TeleportLeftReleased);
	PlayerInputComponent->BindAction("TeleportRight", IE_Pressed, this, &AVRPlayerPawn::TeleportRight);
	PlayerInputComponent->BindAction("TeleportRight", IE_Released, this, &AVRPlayerPawn::TeleportRightReleased);

}

