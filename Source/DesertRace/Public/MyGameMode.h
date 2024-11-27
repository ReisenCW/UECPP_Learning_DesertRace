#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Engine/TimerHandle.h"

#include "MyGameMode.generated.h"


UCLASS()
class DESERTRACE_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LoseTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WinTime = 3.0f;

	FTimerHandle ResetGameTimerHandle;

	void ResetLevel(bool IsWin);
	void OnResetTimeout();
};
