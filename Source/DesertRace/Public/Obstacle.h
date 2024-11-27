#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"

#include "Obstacle.generated.h"

UCLASS()
class DESERTRACE_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacle();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComp;
	UPaperSpriteComponent* ObstacleSprite;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
