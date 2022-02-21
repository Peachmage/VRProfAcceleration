// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Acceleration.h"

#include "AbilitySystemComponent.h"
#include "VRProfAccelerationCharacter.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEffectStackChange.h"
#include "GameFramework/CharacterMovementComponent.h"

UGA_Acceleration::UGA_Acceleration()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_Acceleration::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
	//adds a commit call (not relevant for us) and boilerplate for blueprint extension if needed
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AVRProfAccelerationCharacter* Char = Cast<AVRProfAccelerationCharacter>(GetOwningActorFromActorInfo());
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (!Char || !ASC)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, true);
		return;
	}

	StackChangeTask = UAbilityTask_WaitGameplayEffectStackChange::WaitForGameplayEffectStackChange(this, ASC->FindActiveGameplayEffectHandle(Handle));
	StackChangeTask->OnChange.AddDynamic(this, &UGA_Acceleration::OnStackChange);
	StackChangeTask->ReadyForActivation();
	UpdateMoveSpeed();
	
}

void UGA_Acceleration::UpdateMoveSpeed(int32 Stacks)
{
	//this isn't really scalable but it was explicitly stated implementation of this bit doesn't count

	AVRProfAccelerationCharacter* Char = Cast<AVRProfAccelerationCharacter>(GetOwningActorFromActorInfo());
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	// we can either get stacks ourselves or pass them explicitly
	int32 CurrentStacks = Stacks == -1 ? ASC->GetCurrentStackCount(CurrentSpecHandle) : Stacks;
	//getting default speed out of CDO
	float DefaultSpeed = Cast<AVRProfAccelerationCharacter>(
		AVRProfAccelerationCharacter::StaticClass()->GetDefaultObject())->GetCharacterMovement()->MaxWalkSpeed;
	Char->GetCharacterMovement()->MaxWalkSpeed = (1.f + 0.25f * CurrentStacks) * DefaultSpeed;
}

void UGA_Acceleration::OnStackChange(FActiveGameplayEffectHandle InHandle, int32 NewCount, int32 OldCount)
{
	UpdateMoveSpeed(NewCount);
}


void UGA_Acceleration::OnAvatarSet(const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilitySpec & Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);

}

void UGA_Acceleration::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	UpdateMoveSpeed(0);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

