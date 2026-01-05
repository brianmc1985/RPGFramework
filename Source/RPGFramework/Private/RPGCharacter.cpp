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
	return int32();
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

// Called when the game starts or when spawned
void ARPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
	
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffects, CharacterLevel, EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
	}
}
UAbilitySystemComponent* ARPGCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

