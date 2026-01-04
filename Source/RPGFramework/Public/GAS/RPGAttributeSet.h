// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "RPGAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * RPG Character Attribute Set
 */
UCLASS()
class RPGFRAMEWORK_API URPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	URPGAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	//HEALTH
	UPROPERTY(BlueprintReadOnly, Category = "RPG Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "RPG Attributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxHealth);

	//STAMINA
	UPROPERTY(BlueprintReadOnly, Category = "RPG Attributes", ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, Category = "RPG Attributes", ReplicatedUsing = OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxStamina);

	//ADRENALINE
	UPROPERTY(BlueprintReadOnly, Category = "RPG Attributes", ReplicatedUsing = OnRep_Adrenaline)
	FGameplayAttributeData Adrenaline;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Adrenaline);

	UPROPERTY(BlueprintReadOnly, Category = "RPG Attributes", ReplicatedUsing = OnRep_MaxAdrenaline)
	FGameplayAttributeData MaxAdrenaline;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxAdrenaline);

	//EXPERIENCE POINTS
	UPROPERTY(BlueprintReadOnly, Category = "RPG Attributes", ReplicatedUsing = OnRep_ExperiencePoints)
	FGameplayAttributeData ExperiencePoints;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, ExperiencePoints);

	UPROPERTY(BlueprintReadOnly, Category = "RPG Attributes", ReplicatedUsing = OnRep_MaxExperiencePoints)
	FGameplayAttributeData MaxExperiencePoints;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxExperiencePoints);

protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_Adrenaline(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MaxAdrenaline(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_ExperiencePoints(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MaxExperiencePoints(const FGameplayAttributeData& OldValue);
};
