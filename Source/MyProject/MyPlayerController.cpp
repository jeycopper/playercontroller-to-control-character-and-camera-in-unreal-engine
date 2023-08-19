// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "MyProjectCharacter.h"

void AMyPlayerController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// GetPawn will return the pawn this controller possesses (in this case it will be the player)
	APawn* PossessedPawn = GetPawn();
	// We are possessing a player character, so we can cast the possessed pawn to AMyProjectCharacter so that we can use the methods of that class
	AMyProjectCharacter* PlayerCharacter = CastChecked<AMyProjectCharacter>(PossessedPawn);
	// Call the Move method of the player character while passing the input which tells in what direction to move
	PlayerCharacter->Move(MovementVector);
}

void AMyPlayerController::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// GetPawn will return the pawn this controller possesses (in this case it will be the player)
	APawn* PossessedPawn = GetPawn();
	// We are possessing a player character, so we can cast the possessed pawn to AMyProjectCharacter so that we can use the methods of that class
	AMyProjectCharacter* PlayerCharacter = CastChecked<AMyProjectCharacter>(PossessedPawn);
	// Call the Look method of the player character while passing the input which tells how to rotate the camera
	PlayerCharacter->Look(LookAxisVector);
}

void AMyPlayerController::SetupInputComponent()
{
	// Make sure the code from the base class is executed (it is important because it performs necessary setup)
	Super::SetupInputComponent();

	// Set up action bindings
	// we don't have a PlayerInputComponent argument, but we have access to the global InputComponent variable which we can use here
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent) {
		GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, "MOVE");
		// For simplicity, we won't implement jump functionality here
		//Jumping
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Look);
	}
}

void AMyPlayerController::BeginPlay()
{
	// Make sure the code from the base class is executed (it is important because it performs necessary setup)
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, "MOVE");
	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}
