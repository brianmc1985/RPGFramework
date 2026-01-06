// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGCharacter.h"
#include "GAS/RPGAbilitySystemComponent.h"

// Sets default values
ARPGCharacter::ARPGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialize Ability System Component
	AbilitySystemComponent = CreateDefaultSubobject<URPGAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	//Initialize Attribute Set
	AttributeSet = CreateDefaultSubobject<URPGAttributeSet>("AttributeSet");

	//Set default character level to 1
	CharacterLevel = 1;
}

int32 ARPGCharacter::GetCharacterLevel() const
{
	return CharacterLevel;
}

float ARPGCharacter::GetHealth() const
{
	if(!AttributeSet)
	{
		return 0.f;
	}
	return AttributeSet->GetHealth();
}

float ARPGCharacter::GetMaxHealth() const
{
	if(!AttributeSet)
	{
		return 0.f;
	}
	return AttributeSet->GetMaxHealth();
}

float ARPGCharacter::GetStamina() const
{
	if (!AttributeSet)
	{
		return 0.f;
	}
	return AttributeSet->GetStamina();
}

float ARPGCharacter::GetMaxStamina() const
{
	if(!AttributeSet)
	{
		return 0.f;
	}
	return AttributeSet->GetMaxStamina();
}

float ARPGCharacter::GetAdrenaline() const
{
	if(!AttributeSet)
	{
		return 0.f;
	}	
	return AttributeSet->GetAdrenaline();
}

float ARPGCharacter::GetMaxAdrenaline() const
{
	if (!AttributeSet)
	{
		return 0.f;
	}
	return AttributeSet->GetMaxAdrenaline();
}

float ARPGCharacter::GetExperiencePoints() const
{
	if (!AttributeSet)
	{
		return 0.f;
	}
	return AttributeSet->GetExperiencePoints();
}

float ARPGCharacter::GetMaxExperiencePoints() const
{
	if (!AttributeSet)
	{
		return 0.f;
	}
	return AttributeSet->GetMaxExperiencePoints();
}

bool ARPGCharacter::ActivateAbilitiesWithTags(FGameplayTagContainer AbilityTags, bool AllowRemoteActivation)
{
	if (!AbilitySystemComponent) 
	{
		return false;
	}
	return AbilitySystemComponent->TryActivateAbilitiesByTag(AbilityTags, AllowRemoteActivation);
}

bool ARPGCharacter::ActivateMeleeAbility(bool AllowRemoteActivation)
{
	if (!AbilitySystemComponent || !MeleeAbilitySpecHandle.IsValid())
	{
		return false;
	}
	return AbilitySystemComponent->TryActivateAbility(MeleeAbilitySpecHandle, AllowRemoteActivation);
}

// Called when the game starts or when spawned
void ARPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARPGCharacter::SetTestAbilities()
{
	if (!AbilitySystemComponent)
	{
		return;
	}
	if (GetLocalRole() == ROLE_Authority)
	{
		for (TSubclassOf<UGameplayAbility> TestAbility : TestAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(TestAbility, GetCharacterLevel(),INDEX_NONE,this ));
		}
	}
}

void ARPGCharacter::SetMeleeAbility()
{
	if (!AbilitySystemComponent)
	{
		return;
	}
	MeleeAbilitySpecHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(MeleeAbility, GetCharacterLevel(), INDEX_NONE, this));
}

// Called every frame
void ARPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void ARPGCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!AbilitySystemComponent)
	{
		return;
	}
	if (EnableTestAbilities) 
	{
		SetTestAbilities();
	}
	ApplyDefaultAttributeEffects();
	SetMeleeAbility();
}
UAbilitySystemComponent* ARPGCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ARPGCharacter::HandleHealthChanged(float DeltaValue, AActor* Causer)
{
	// Llama al evento de Blueprint (el nuevo nombre)
	OnHealthChanged(DeltaValue, Causer);

	if (GetHealth() <= 0.f) { OnDead(); }
}

void ARPGCharacter::HandleStaminaChanged(float DeltaValue, AActor* Causer)
{
	OnStaminaChanged(DeltaValue, Causer);
}

void ARPGCharacter::HandleAdrenalineChanged(float DeltaValue, AActor* Causer)
{
	OnAdrenalineChanged(DeltaValue, Causer);
}

void ARPGCharacter::HandleExperiencePointsChanged(float DeltaValue)
{
	OnXPChanged(DeltaValue);
}

void ARPGCharacter::HandleCharacterLeveledUp()
{
	CharacterLevel += 1;
	RemoveDefaultAttributeEffects();
	ApplyDefaultAttributeEffects();
	OnCharacterLeveledUp();
}

void ARPGCharacter::ApplyDefaultAttributeEffects()
{
	//Apply Default Attribute Effect
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	for (TSubclassOf<class UGameplayEffect>& DefaultEffect : DefaultAttributeEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultEffect, CharacterLevel, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
		}
	}
	
}

void ARPGCharacter::RemoveDefaultAttributeEffects()
{
	FGameplayEffectQuery Query;
	Query.EffectSource = this;
	AbilitySystemComponent->RemoveActiveEffects(Query);
}

