// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/RPGAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

URPGAttributeSet::URPGAttributeSet()
{

}

void URPGAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(URPGAttributeSet, Health);
	DOREPLIFETIME(URPGAttributeSet, MaxHealth);
	DOREPLIFETIME(URPGAttributeSet, Stamina);
	DOREPLIFETIME(URPGAttributeSet, MaxStamina);
	DOREPLIFETIME(URPGAttributeSet, Adrenaline);
	DOREPLIFETIME(URPGAttributeSet, MaxAdrenaline);
	DOREPLIFETIME(URPGAttributeSet, ExperiencePoints);
	DOREPLIFETIME(URPGAttributeSet, MaxExperiencePoints);

}

void URPGAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		//Clamp Health between 0 and MaxHealth
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	if(Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		//Clamp Stamina between 0 and MaxStamina
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
	}
	if(Data.EvaluatedData.Attribute == GetAdrenalineAttribute())
	{
		//Clamp Adrenaline between 0 and MaxAdrenaline
		SetAdrenaline(FMath::Clamp(GetAdrenaline(), 0.f, GetMaxAdrenaline()));
	}
	if(Data.EvaluatedData.Attribute == GetExperiencePointsAttribute())
	{
		//Clamp Experience Points between 0 and MaxExperiencePoints
		SetExperiencePoints(FMath::Clamp(GetExperiencePoints(), 0.f, GetMaxExperiencePoints()));
	}
}

void URPGAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
	if(Attribute == GetMaxStaminaAttribute())
	{
		AdjustAttributeForMaxChange(Stamina, MaxStamina, NewValue, GetStaminaAttribute());
	}
	if(Attribute == GetMaxAdrenalineAttribute())
	{
		AdjustAttributeForMaxChange(Adrenaline, MaxAdrenaline, NewValue, GetAdrenalineAttribute());
	}
	if(Attribute == GetMaxExperiencePointsAttribute())
	{
		AdjustAttributeForMaxChange(ExperiencePoints, MaxExperiencePoints, NewValue, GetExperiencePointsAttribute());
	}
}

void URPGAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilitySystemComponent = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilitySystemComponent)
	{
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = CurrentMaxValue > 0.f ? (CurrentValue*NewMaxValue/CurrentMaxValue)-CurrentValue : NewMaxValue;
		AbilitySystemComponent->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

void URPGAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Health, OldValue);
}

void URPGAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MaxHealth, OldValue);
}

void URPGAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Stamina, OldValue);
}

void URPGAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MaxStamina, OldValue);
}

void URPGAttributeSet::OnRep_Adrenaline(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Adrenaline, OldValue);
}

void URPGAttributeSet::OnRep_MaxAdrenaline(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MaxAdrenaline, OldValue);
}

void URPGAttributeSet::OnRep_ExperiencePoints(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, ExperiencePoints, OldValue);
}

void URPGAttributeSet::OnRep_MaxExperiencePoints(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MaxExperiencePoints, OldValue);
}
