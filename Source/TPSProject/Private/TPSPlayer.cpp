// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/TPSPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ATPSPlayer::ATPSPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Mesh data 할당
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("'/Game/Characters/Mannequins/Meshes/SKM_Manny_Simple.SKM_Manny_Simple'"));
	if (TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}
	
	// camera 관련 컴포넌트 추가 
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	
	// 월드에 Instance로 등록하면 자동으로 PlayerController가
	// Possess 한다.
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ATPSPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// 입력 액션과 함수 바인딩
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATPSPlayer::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ATPSPlayer::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ATPSPlayer::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ATPSPlayer::MoveForward);
}

void ATPSPlayer::Turn(float Value)
{
	// 마우스 좌우 입력값 받아서 회전시키기
	AddControllerYawInput(Value);
}

void ATPSPlayer::LookUp(float Value)
{
	// 상하 회전
	AddControllerPitchInput(Value);
}

void ATPSPlayer::MoveForward(float Value)
{
	FVector direction = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::X) * Value;
	AddMovementInput(direction);
}

void ATPSPlayer::MoveRight(float Value)
{
	FVector direction = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y) * Value;
	AddMovementInput(direction);
}
