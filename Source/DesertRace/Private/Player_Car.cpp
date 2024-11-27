#include "Player_Car.h"

APlayer_Car::APlayer_Car()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);//attach the camera to the end of the spring arm


	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComp"));
	SpriteComp->SetupAttachment(RootComponent);
}

void APlayer_Car::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
			(PlayerController->GetLocalPlayer());
		if (Subsystem) {
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void APlayer_Car::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayer_Car::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayer_Car::Move);
	}
}

void APlayer_Car::Move(const FInputActionValue& Value) {
	FVector2D MoveActionValue = Value.Get<FVector2D>();
	if (CanMove) {
		//move
		if ((abs(MoveActionValue.Y)) > 0.0f) {
			float DeltaTime = GetWorld()->GetDeltaSeconds();
			//rotate
			if ((abs(MoveActionValue.X)) > 0.0f) {
				float RotationAmount = -RotationSpeed * MoveActionValue.X * DeltaTime;//按A时,MoveActionValue = -1,表示与x轴夹角减小,即顺时针,因此要加负号
				AddActorWorldRotation(FRotator(RotationAmount, 0.0f, 0.0f));//改变与x,y,z轴所成角(轴逆时针转过来要多少角度),不是绕着x,y,z轴旋转
			}
			float FinalMovementSpeed = MovementSpeed;
			if (MoveActionValue.Y < 0.0f)
				FinalMovementSpeed *= 0.6;

			FVector CurrentLocation = GetActorLocation();
			FVector DistToMove = GetActorUpVector() * FinalMovementSpeed * MoveActionValue.Y * DeltaTime;

			FVector NewLocation = DistToMove + CurrentLocation;
			SetActorLocation(NewLocation);
		}
	}
}