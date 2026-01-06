// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/RPGAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "RPGCharacter.h"

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

	float DeltaValue = 0.f;

	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Additive)
	{
		DeltaValue = Data.EvaluatedData.Magnitude;
	}
	
	AActor* TargetActor = nullptr;
	ARPGCharacter* RPGCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		RPGCharacter = Cast<ARPGCharacter>(TargetActor);
	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		//Clamp Health between 0 and MaxHealth
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		if(RPGCharacter)
		{
			RPGCharacter->HandleHealthChanged(DeltaValue, Data.EffectSpec.GetContext().GetInstigator());
		}
	}
	if(Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		//Clamp Stamina between 0 and MaxStamina
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
		if (RPGCharacter)
		{
			RPGCharacter->HandleStaminaChanged(DeltaValue, Data.EffectSpec.GetContext().GetInstigator());
		}
	}
	if(Data.EvaluatedData.Attribute == GetAdrenalineAttribute())
	{
		//Clamp Adrenaline between 0 and MaxAdrenaline
		SetAdrenaline(FMath::Clamp(GetAdrenaline(), 0.f, GetMaxAdrenaline()));
		if (RPGCharacter)
		{
			RPGCharacter->HandleAdrenalineChanged(DeltaValue, Data.EffectSpec.GetContext().GetInstigator());
		}
	}
	if(Data.EvaluatedData.Attribute == GetExperiencePointsAttribute())
	{
		float Difference = GetExperiencePoints() - GetMaxExperiencePoints();
		if (RPGCharacter)
		{
			RPGCharacter->HandleExperiencePointsChanged(DeltaValue);
			if (Difference >= 0.f)
			{
				RPGCharacter->HandleCharacterLeveledUp();
			}

		}
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
	if (Attribute == GetMaxExperiencePointsAttribute())
	{
		SetExperiencePoints(0.f);
	}
}

void URPGAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilitySystemComponent = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilitySystemComponent)
	{
		AbilitySystemComponent->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Override, NewMaxValue);
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
