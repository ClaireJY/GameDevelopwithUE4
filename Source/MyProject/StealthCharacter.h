// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProjectCharacter.h"
#include "StealthCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AStealthCharacter : public AMyProjectCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float StealthPitchYawScale = 0.5f;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void AddControllerPitchInput(float Val) override;
	virtual void AddControllerYawInput(float Val) override;

	void Stealth();
	void UnStealth();
protected:
	bool bIsStealthed = false;
	
};
