// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GA_Acceleration.h"
#include "VRProfAcceleration.h"

#include "GE_AccelerationStacker.generated.h"

/**
* GetGameplayEffectCount
*/
UCLASS()
class VRPROFACCELERATION_API UGE_AccelerationStacker : public UGameplayEffect
{
	GENERATED_BODY()
	UGE_AccelerationStacker()
	{
		DurationPolicy = EGameplayEffectDurationType::HasDuration;DurationPolicy = EGameplayEffectDurationType::HasDuration;
		FSetByCallerFloat SBCFDuration = FSetByCallerFloat();
		SBCFDuration.DataTag = FGameplayTag::RequestGameplayTag(FName("Ability.Duration"));
		DurationMagnitude = FGameplayEffectModifierMagnitude(SBCFDuration);

		StackingType = EGameplayEffectStackingType::AggregateByTarget;
		StackLimitCount = 0;
		StackDurationRefreshPolicy = EGameplayEffectStackingDurationPolicy::RefreshOnSuccessfulApplication;
		StackExpirationPolicy = EGameplayEffectStackingExpirationPolicy::ClearEntireStack;
		FGameplayAbilitySpecDef AbilitySpec = FGameplayAbilitySpecDef();
		AbilitySpec.Ability = UGA_Acceleration::StaticClass();
		GrantedAbilities.Add(AbilitySpec);
		// InheritableOwnedTagsContainer.Added = FGameplayTagContainer(TAG("Ability.Actor.Active"));
		// UpdateInheritedTagProperties();
	}
};
