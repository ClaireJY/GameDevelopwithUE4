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

	MyOwner = Cast<AMyProjectCharacter>(GetOwner());
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
	for (auto WeaponIt = WeaponArray.CreateIterator(); WeaponIt; WeaponIt++)
	{
		{
			FWeaponProperties weapon = *WeaponIt;
			SelectWeapon(weapon.WeaponClass);
			break;
		}
	}
}

void UMasteringInventory::AddWeapon(TSubclassOf<class AMasteringWeapon> Weapon, int AmmoCount, uint8 WeaponPower)
{

	for (auto WeaponIt = WeaponArray.CreateIterator(); WeaponIt; ++WeaponIt)
	{
		FWeaponProperties& currentProps = *WeaponIt;
		if (currentProps.WeaponClass == Weapon)
		{
			checkSlow(AmmoCount > 0);
			currentProps.Ammo += AmmoCount;
			return;
		}

		FWeaponProperties weaponProps;
		weaponProps.WeaponClass = Weapon;
		weaponProps.WeaponPower = WeaponPower;
		weaponProps.Ammo = AmmoCount;

		WeaponArray.Add(weaponProps);
	}

}

void UMasteringInventory::ChangeAmmo(TSubclassOf<class AMasteringWeapon> Weapon, const int ChangeAmount)
{
	for (auto WeaponIt = WeaponArray.CreateIterator(); WeaponIt; ++WeaponIt)
	{
		FWeaponProperties& currentProps = *WeaponIt;
		if (currentProps.WeaponClass == Weapon)
		{
			if (currentProps.Ammo == UNLIMITED_AMMO)
				return;
			currentProps.Ammo = FMath::Clamp(currentProps.Ammo + ChangeAmount, 0, 999);
			if (currentProps.Ammo == 0)
			{
				CurrentWeaponPower = -1;
				SelectBestWeapon();
			}
			return;
		}
	}
}

void UMasteringInventory::SelectWeapon(TSubclassOf<class AMasteringWeapon> Weapon)
{
	MyOwner->EquipWeapon(Weapon);
	CurrentWeapon = Weapon; 
}

int UMasteringInventory::FindCurrentWeaponIndex() const 
{
	int currentIndex = 0;
	for (auto WeaponIt = WeaponArray.CreateConstIterator(); WeaponIt; ++WeaponIt, ++currentIndex)
	{
		const FWeaponProperties& currentProps = *WeaponIt;
		if (currentProps.WeaponClass == CurrentWeapon)
		{
			break;
		}

		checkSlow(currentIndex < weaponArray.Num());
		
	}
	return currentIndex;
}

void UMasteringInventory::SelectNextWeapon()
{
	int currentIndex = FindCurrentWeaponIndex();
	if (currentIndex == WeaponArray.Num() - 1)
	{
		SelectWeapon(WeaponArray[0].WeaponClass);
	}
	else
	{
		SelectWeapon(WeaponArray[currentIndex + 1].WeaponClass);
	}
}

void UMasteringInventory::SelectPreviousWeapon()
{
	int currentIndex = FindCurrentWeaponIndex();
	if (currentIndex > 0) {
		SelectWeapon(WeaponArray[currentIndex - 1].WeaponClass);
	}
	else
	{
		SelectWeapon(WeaponArray[WeaponArray.Num() - 1].WeaponClass);
	}
}




