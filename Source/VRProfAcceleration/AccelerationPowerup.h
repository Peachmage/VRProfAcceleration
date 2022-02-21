// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "AccelerationPowerup.generated.h"

class UGameplayEffect;
UCLASS()
class VRPROFACCELERATION_API AAccelerationPowerup : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* Representation;
	UFUNCTION()
    void BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
                      AActor* OtherActor, 
                      UPrimitiveComponent* OtherComp, 
                      int32 OtherBodyIndex, 
                      bool bFromSweep, 
                      const FHitResult &SweepResult );
	UFUNCTION()
	void StartRespawnTimer();
	
	void ChangePowerupState(bool bReady);
public:
	// Sets default values for this actor's properties
	AAccelerationPowerup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float EffectDuration = 3.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float RespawnTime = 5.f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<class UGE_AccelerationStacker> EffectClass;
};