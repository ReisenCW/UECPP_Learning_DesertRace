#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameMode.h"


#include "Obstacle.generated.h"

UCLASS()
class DESERTRACE_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacle();

	AMyGameMode* MyGameMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* ObstacleSprite;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, 
		const FHitResult& SweepResult);
};
