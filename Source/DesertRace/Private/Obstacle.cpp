#include "Obstacle.h"

#include "Player_Car.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	ObstacleSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ObstacleSprite"));
	ObstacleSprite->SetupAttachment(RootComponent);
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnOverlap);
	MyGameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacle::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep,
	const FHitResult& SweepResult) {
	APlayer_Car* Player = Cast<APlayer_Car>(OtherActor);
	if (Player) {
		if (Player->CanMove) {
			Player->CanMove = false;

			UGameplayStatics::PlaySound2D(GetWorld(), HitSound);

			MyGameMode->ResetLevel(IsFinishLine);
		}
	}
}