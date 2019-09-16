#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Notification.generated.h"

/**
 * 
 */
UCLASS()
class E2EE_API UNotification : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void DisplayNotification( const FText& NotificationString, bool StayInView = false );

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void HideNotification( bool SuddenHide = false );
	
};
