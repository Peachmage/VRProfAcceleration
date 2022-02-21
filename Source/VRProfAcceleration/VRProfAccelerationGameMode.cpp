// Copyright Epic Games, Inc. All Rights Reserved.

#include "VRProfAccelerationGameMode.h"
#include "VRProfAccelerationCharacter.h"
#include "UObject/ConstructorHelpers.h"

AVRProfAccelerationGameMode::AVRProfAccelerationGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
