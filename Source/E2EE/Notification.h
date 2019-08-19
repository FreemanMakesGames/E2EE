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
	void DisplayNotification( const FString& NotificationString );
	
};
