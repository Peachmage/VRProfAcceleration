// Fill out your copyright notice in the Description page of Project Settings.


#include "VRProfAccelerationPC.h"


#include "AbilitySystemComponent.h"
#include "VRProfAccelerationCharacter.h"

void AVRProfAccelerationPC::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	AVRProfAccelerationCharacter* CharacterBase = Cast<AVRProfAccelerationCharacter>(P);
	if (CharacterBase)
	{
		CharacterBase->GetAbilitySystemComponent()->InitAbilityActorInfo(CharacterBase, CharacterBase);
	}
}
