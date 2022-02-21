// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VRProfAccelerationPC.generated.h"

/**
 * 
 */
UCLASS()
class VRPROFACCELERATION_API AVRProfAccelerationPC : public APlayerController
{
	GENERATED_BODY()

	public:
		virtual void AcknowledgePossession(APawn* P) override;
};
