// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

#define Trace_Length 80000.f

class AWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLASTER_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();
	friend class ABlasterCharacter;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void EquipWeapon(AWeapon* WeaponToEquip);
	void FireButtonPressed(bool bPressed);
protected:
	virtual void BeginPlay() override;

	void SetIsAiming(bool bAiming); //Server and client side
	
	UFUNCTION(Server, Reliable)
	void ServerSetIsAiming(bool bAiming); //Server will replicate to all clients
	
	UFUNCTION()
	void OnRep_EquippedWeapon();

	UFUNCTION(Server, Reliable)
	void ServerFire(); //Server RPC
	UFUNCTION(NetMulticast, Reliable)
	void MulticastFire(); //Multicast RPC

	void TraceUnderCrosshairs(FHitResult& TraceHitResult);

private:
	class ABlasterCharacter* Character;
	UPROPERTY(ReplicatedUsing = OnRep_EquippedWeapon)
	AWeapon* EquippedWeapon;
	UPROPERTY(Replicated) //Replicated is used only when the value changes form one state to another state (true to false and vice versa) otherwise it is useless for continuous use incase of automatic weapon
	bool bIsAiming;

	UPROPERTY(EditAnywhere)
	float BaseWalkSpeed;
	UPROPERTY(EditAnywhere)
	float AimWalkSpeed;

	bool bFireButtonPressed;
public:	
	

		
};
