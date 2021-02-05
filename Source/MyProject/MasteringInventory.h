// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyProjectCharacter.h"
#include "MasteringInventory.generated.h"

USTRUCT()
struct FWeaponProperties
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
	TSubclassOf<class AMasteringWeapon> WeaponClass;

	UPROPERTY()
	int WeaponPower;

	UPROPERTY()
	int Ammo;

};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UMasteringInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMasteringInventory();

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AMasteringWeapon> DefaultWeapon;
	void SelectBestWeapon();
	void SelectWeapon(TSubclassOf <class AMasteringWeapon> Weapon);
	void SelectNextWeapon();
	void SelectPreviousWeapon();
	void AddWeapon(TSubclassOf<class AMasteringWeapon> weapon, int AmmoCount, uint8 WeaponPower);
	int FindCurrentWeaponIndex() const;

	FORCEINLINE TSubclassOf<class AMasteringWeapon> GetCurrentWeapon() const { return CurrentWeapon; }

	void ChangeAmmo(TSubclassOf<class AMasteringWeapon> Weapon, const int ChangeAmount);

	protected:
		TArray<FWeaponProperties> WeaponArray;
		TSubclassOf<class AMasteringWeapon> CurrentWeapon;
		
		int CurrentWeaponPower = -1;
		class AMyProjectCharacter* MyOwner;
		
};
