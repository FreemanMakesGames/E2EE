#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemMenu.generated.h"

class UVerticalBox;

/**
 * 
 */
UCLASS()
class E2EE_API UItemMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY( meta = ( BindWidget ) )
	UVerticalBox* VerticalBox_Buttons;
	
};
