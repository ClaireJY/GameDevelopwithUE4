// Fill out your copyright notice in the Description page of Project Settings.


#include "MasteringWeaponPickup.h"
#include "MasteringInventory.h"
#include "MyProjectCharacter.h"

// Sets default values
AMasteringWeaponPickup::AMasteringWeaponPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMasteringWeaponPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMasteringWeaponPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator rotationAmount(0.0f, DeltaTime * RotationSpeed, 0.0f);
	AddActorLocalRotation(rotationAmount);

}

void AMasteringWeaponPickup::NofityActorBeginOverlap(AActor* OtherActor)
{
	AMyProjectCharacter* player = Cast< AMyProjectCharacter>(OtherActor);
	if (player == nullptr)
	{
		return;
	}

	UMasteringInventory* Inventory = player->Inventory;
	Inventory->AddWeapon(WeaponClass, Ammunition, WeaponPower);
	Inventory->SelectBestWeapon(player);

	Destroy();
}

