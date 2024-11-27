#include "MyGameMode.h"
#include "Kismet/GameplayStatics.h"

void AMyGameMode::ResetLevel(bool IsWin) 
{
	float WaitTime = LoseTime;
	if (IsWin) {
		WaitTime = WinTime;
	}
	GetWorldTimerManager().SetTimer(ResetGameTimerHandle, this, &AMyGameMode::OnResetTimeout, 1.0f, false, WaitTime);
}

void AMyGameMode::OnResetTimeout() {
	UGameplayStatics::OpenLevel(this, FName("Desert_Level"));
}