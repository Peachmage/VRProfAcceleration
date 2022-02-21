// Fill out your copyright notice in the Description page of Project Settings.


#include "AccelerationPowerup.h"


#include "AbilitySystemComponent.h"
#include "GE_AccelerationStacker.h"
#include "VRProfAccelerationCharacter.h"


// Sets default values
AAccelerationPowerup::AAccelerationPowerup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Representation = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Representation"));
	RootComponent = Representation;

	Representation->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Representation->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Representation->SetGenerateOverlapEvents(true);
	EffectClass = UGE_AccelerationStacker::StaticClass();
}

// Called when the game starts or when spawned
void AAccelerationPowerup::BeginPlay()
{
	Super::BeginPlay();
	Representation->OnComponentBeginOverlap.AddDynamic(this, &AAccelerationPowerup::BeginOverlap);
}

// Called every frame
void AAccelerationPowerup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAccelerationPowerup::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	AVRProfAccelerationCharacter* Char = Cast<AVRProfAccelerationCharacter>(OtherActor);
	//only characters get to pick powerups
	if (!Char) return;
	
	UAbilitySystemComponent* ASC = Char->GetAbilitySystemComponent();
	//ASC isn't valid? abort.
	if (!ASC) return;

	FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(EffectClass, 1.0f, ASC->MakeEffectContext());
	SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Ability.Duration")), EffectDuration);
	ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data, ASC->GetPredictionKeyForNewAction());
	ChangePowerupState(false);
	StartRespawnTimer();
}

void AAccelerationPowerup::StartRespawnTimer()
{
	FTimerHandle Handle;
	FTimerDelegate Del;
	Del.BindUObject(this, &AAccelerationPowerup::ChangePowerupState, true);
	GetWorldTimerManager().SetTimer(Handle, Del, RespawnTime, false);
}

void AAccelerationPowerup::ChangePowerupState(bool bReady)
{
	if (bReady)
	{
		Representation->SetVisibility(true);
		Representation->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		Representation->SetVisibility(false);
		Representation->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

	
	
