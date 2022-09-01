// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BLASTER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponenet;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* Tracer;
	
	class UParticleSystemComponent* TracerComponent;
	
	UPROPERTY(EditAnywhere)
	UParticleSystem* MetalImpactParticles;
	UPROPERTY(EditAnywhere)
	class USoundCue* MetalImpactSound;
	UPROPERTY()
	bool bIsCharacterHit;

public:	

	

};
