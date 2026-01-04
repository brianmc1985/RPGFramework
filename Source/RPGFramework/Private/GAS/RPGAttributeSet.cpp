// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/RPGAttributeSet.h"
#include "Net/UnrealNetwork.h"

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
}

void URPGAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
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
