#pragma once

#include "ItemUsage.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemMenu.generated.h"

class UVerticalBox;
class UButton;
class AItem;

/**
 * 
 */
UCLASS()
class E2EE_API UItemMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	UItemMenu( const FObjectInitializer& ObjectInitializer );

	virtual void NativeOnInitialized() override;

protected:

	UPROPERTY( meta = ( BindWidget ) )
	UVerticalBox* VerticalBox_Buttons;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_Destroy;

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_Drop;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	TMap<EItemUsage, UButton*> ItemUsageToButton;

public:

	UFUNCTION()
	void ShowButtons( AItem* Item );
	
};
