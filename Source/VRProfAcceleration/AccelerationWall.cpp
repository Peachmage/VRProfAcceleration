// Fill out your copyright notice in the Description page of Project Settings.


#include "AccelerationWall.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


void AAccelerationWall::OnWallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//Only characters can destroy this wall. Could cast to our character class too.
	if (!Cast<ACharacter>(OtherActor)) return;
	//technically you can destroy the wall just by touching it with enough powerups
	float OtherSpeed = Cast<ACharacter>(OtherActor)->GetCharacterMovement()->MaxWalkSpeed;
	if (OtherSpeed >= SpeedToDestroy) Destroy();
}

// Sets default values
AAccelerationWall::AAccelerationWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Representation = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Representation"));
	RootComponent = Representation;

	Representation->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Representation->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	
}

// Called when the game starts or when spawned
void AAccelerationWall::BeginPlay()
{
	Super::BeginPlay();
	Representation->OnComponentHit.AddDynamic(this, &AAccelerationWall::OnWallHit);
}

// Called every frame
void AAccelerationWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

