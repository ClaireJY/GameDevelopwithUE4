// Fill out your copyright notice in the Description page of Project Settings.


#include "MasteringInventory.h"
#include "MyProjectCharacter.h"
#include "MasteringWeapon.h"

#define UNLIMITED_AMMO -1

// Sets default values for this component's properties
UMasteringInventory::UMasteringInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MyOwner = Cast<AMasteringCharacter>(GetOwner());
	check(GetOwner() == nullptr || MyOwner != nullptr);
}


// Called when the game starts
void UMasteringInventory::BeginPlay()
{
	Super::BeginPlay();

	if (DefaultWeapon != nullptr)
	{
		AddWeapon(DefaultWeapon, UNLIMITED_AMMO, 0);
	}
	
}

void UMasteringInventory::SelectBestWeapon()
{
	for (auto WeaponIt = weaponArray.CreateIterator(); WeaponIt; WeaponIt++)
	{
		{
			SelectWeapon(*WeaponIt);
			break;
		}
	}
}

void UMasteringInventory::AddWeapon(TSubclassOf<class AMasteringWeapon> weapon, int AmmoCount, uint8 WeaponPower)
{
	weaponArray.AddUnique(weapon);

}

void UMasteringInventory::AddDefaultWeapon()
{

}

void UMasteringInventory::SelectWeapon(class AMyProjectCharacter* Player, TSubclassOf<class AMasteringWeapon> Weapon)
{
	Player->EquipWeapon(Weapon);
}



