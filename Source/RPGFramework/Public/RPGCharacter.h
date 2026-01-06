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

	UFUNCTION(BlueprintCallable, Category = "RPG Abilities")
	bool ActivateAbilitiesWithTags(FGameplayTagContainer AbilityTags, bool AllowRemoteActivation = true);

	/*Blueprint event when character dies*/
	UFUNCTION(BlueprintImplementableEvent)
	void OnDead();
	// RPGCharacter.h

	UFUNCTION(BlueprintImplementableEvent, Category = "RPG Attributes")
	void OnHealthChanged(float DeltaValue, AActor* Causer);

	UFUNCTION(BlueprintImplementableEvent, Category = "RPG Attributes")
	void OnStaminaChanged(float DeltaValue, AActor* Causer);

	UFUNCTION(BlueprintImplementableEvent, Category = "RPG Attributes")
	void OnAdrenalineChanged(float DeltaValue, AActor* Causer);

	UFUNCTION(BlueprintImplementableEvent, Category = "RPG Attributes")
	void OnXPChanged(float DeltaValue);

	//Character level getter
	UFUNCTION(BlueprintImplementableEvent)
	void OnCharacterLeveledUp();

	UFUNCTION(BlueprintCallable, Category = "RPG Abilities|Melee")
	bool ActivateMeleeAbility(bool AllowRemoteActivation = true);

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

	/*Set this to true if you want to add test abilities to character's ability component*/
	UPROPERTY(EditAnywhere, Category = "RPG Attributes|Debug")
	bool EnableTestAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RPG Attributes|Debug")
	TArray<TSubclassOf<class UGameplayAbility>> TestAbilities;

	virtual void SetTestAbilities();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RPG Abilities|Melee")
	TSubclassOf<class UGameplayAbility> MeleeAbility;

	UPROPERTY()
	FGameplayAbilitySpecHandle MeleeAbilitySpecHandle;

	virtual void SetMeleeAbility();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	//Inheredit via IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void HandleHealthChanged(float DeltaValue, AActor* Causer);
	virtual void HandleStaminaChanged(float DeltaValue, AActor* Causer);
	virtual void HandleAdrenalineChanged(float DeltaValue, AActor* Causer);
	virtual void HandleExperiencePointsChanged(float DeltaValue);

	virtual void HandleCharacterLeveledUp();

	virtual void ApplyDefaultAttributeEffects();

	virtual void RemoveDefaultAttributeEffects();
};
