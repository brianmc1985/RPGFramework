// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GAS/RPGAttributeSet.h"
#include "GameFramework/Character.h"
#include "RPGCharacter.generated.h"

UCLASS()
class RPGFRAMEWORK_API ARPGCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGCharacter();

	UFUNCTION(BlueprintCallable, Category = "RPG Attributes")
	virtual int32 GetCharacterLevel() const;

	//Health
	UFUNCTION(BlueprintCallable, Category = "RPG Attributes")
	virtual float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "RPG Attributes")
	virtual float GetMaxHealth() const;

	//Stamina
	UFUNCTION(BlueprintCallable, Category = "RPG Attributes")
	virtual float GetStamina() const;

	UFUNCTION(BlueprintCallable, Category = "RPG Attributes")
	virtual float GetMaxStamina() const;

	//Adrenaline
	UFUNCTION(BlueprintCallable, Category = "RPG Attributes")
	virtual float GetAdrenaline() const;

	UFUNCTION(BlueprintCallable, Category = "RPG Attributes")
	virtual float GetMaxAdrenaline() const;

	//Experience Points
	UFUNCTION(BlueprintCallable, Category = "RPG Attributes")
	virtual float GetExperiencePoints() const;

	UFUNCTION(BlueprintCallable, Category = "RPG Attributes")
	virtual float GetMaxExperiencePoints() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	class URPGAttributeSet* AttributeSet;

	/*The level of character. It should not be changed directly once character is spawned!*/
	UPROPERTY(EditAnywhere, Category = "RPG Attributes")
	int32 CharacterLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RPG Attributes")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffects;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	//Inheredit via IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

};
