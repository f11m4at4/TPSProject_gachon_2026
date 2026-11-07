// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"

#include "TPSPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	// 1. owner pawn
	auto pawn = TryGetPawnOwner();
	// 2. casting
	auto me = Cast<ATPSPlayer>(pawn);
	if (me)
	{
		// 3. set speed, direction, isinair
		Speed = me->GetVelocity().Dot(me->GetActorForwardVector());
		Direction = me->GetVelocity().Dot(me->GetActorRightVector());
		IsInAir = me->GetCharacterMovement()->IsFalling();
	}
}
