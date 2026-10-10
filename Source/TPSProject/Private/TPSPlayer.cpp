// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/TPSPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


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
	
	SniperGunComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SniperGunComp"));
	SniperGunComp->SetupAttachment(GetMesh());
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempGun(TEXT("/Script/Engine.StaticMesh'/Game/SniperGun/sniper11.sniper11'"));
	if (TempGun.Succeeded())
	{
		SniperGunComp->SetStaticMesh(TempGun.Object);
		// 배치
		SniperGunComp->SetRelativeLocation(FVector(-10.852490,50.000000,120.000000));
		SniperGunComp->SetRelativeRotation(FRotator(0.000000,0.000001,0.000000));
		SniperGunComp->SetRelativeScale3D(FVector(0.187500,0.187500,0.187500));
	}
	
	
	// 월드에 Instance로 등록하면 자동으로 PlayerController가
	// Possess 한다.
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	// 몇단 점프까지 할지 지정
	JumpMaxCount = 2;
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
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ATPSPlayer::PlayerJump);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATPSPlayer::Fire);
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

void ATPSPlayer::PlayerJump()
{
	Jump();
}

// 사용자가 발사버튼을 누르면 총을 쏜다.
void ATPSPlayer::Fire()
{
	FHitResult HitInfo;
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation + Camera->GetForwardVector() * 50000;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	// 총을 쏜다.
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitInfo, StartLocation, EndLocation, ECC_Visibility, Params);

	// 충돌했을 때
	if (bHit)
	{
		// 파편 재생
		if (BulletEffect)
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletEffect, HitInfo.Location);
		
		// 물체 날려 버리기
		// -> 부딪힌 물체가 Simulate Physics 활성화 돼있다면
		if (HitInfo.GetComponent()->IsSimulatingPhysics())
		{
			HitInfo.GetComponent()->AddImpulseAtLocation(Camera->GetForwardVector() * 1000000, HitInfo.Location);
		}
	}
}
