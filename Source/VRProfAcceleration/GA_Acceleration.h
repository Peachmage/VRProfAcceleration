// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Acceleration.generated.h"

/**
 * 
 */
UCLASS()
class VRPROFACCELERATION_API UGA_Acceleration : public UGameplayAbility
{
	GENERATED_BODY()
	
	UFUNCTION()
	void UpdateMoveSpeed(int32 Stacks = -1);
	UFUNCTION()
	void OnStackChange(FActiveGameplayEffectHandle InHandle, int32 NewCount, int32 OldCount);

	UPROPERTY()
	class UAbilityTask_WaitGameplayEffectStackChange* StackChangeTask;
	public:
	
	UGA_Acceleration();
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float MoveSpeedMultiPerStack = 0.25f;

};
