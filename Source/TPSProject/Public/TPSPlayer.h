// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSPlayer.generated.h"

UCLASS()
class TPSPROJECT_API ATPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	// SringArm 컴포넌트 추가
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* Camera;
	
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* SniperGunComp;	
public:
	// mouse 회전
	void Turn(float Value);
	void LookUp(float Value);
	
	// 이동
	void MoveForward(float Value);
	void MoveRight(float Value);
	
	// 점프
	void PlayerJump();
	
	
	// 총쏘기
	UPROPERTY(EditDefaultsOnly, Category=Effect)
	class UParticleSystem* BulletEffect;
	
	void Fire();
	
	// crosshair UI
	UPROPERTY(EditDefaultsOnly, Category=UI)
	TSubclassOf<class UUserWidget> CrosshairUIWidget;
	// crosshair instance
	UPROPERTY()
	class UUserWidget* CrosshairUI;
	
	// sniper aim 입력처리 함수
	void Aim();
	// aim 중인지 여부
	bool bAiming = false;
	
	
	// ---------- sniper ui --------------
	// crosshair UI
	UPROPERTY(EditDefaultsOnly, Category=UI)
	TSubclassOf<class UUserWidget> SniperUIWidget;
	// crosshair instance
	UPROPERTY()
	class UUserWidget* SniperUI;
};
