#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StoryDisplay.generated.h"

class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS()
class E2EE_API UStoryDisplay : public UUserWidget
{
	GENERATED_BODY()

public:

	UStoryDisplay( const FObjectInitializer& ObjectInitializer );

	virtual void NativeOnInitialized() override;

protected:

	UPROPERTY( meta = ( BindWidget ), BlueprintReadOnly )
	UTextBlock* TextBlock_StoryText;

	UPROPERTY( meta = ( BindWidget ), BlueprintReadOnly )
	UButton* Button_Next;

	UPROPERTY( meta = ( BindWidget ), BlueprintReadOnly )
	UButton* Button_Proceed;

public:

	UFUNCTION( BlueprintCallable )
	void PresentStoryFromFile( FString FileName );

protected:

	/**
	 * The sequence of texts to display.
	 * Clicking Button_Next will attempt to display the next FString in the array.
	 */
	UPROPERTY( BlueprintReadOnly )
	TArray<FString> TextSequence;

	int NextTextToShow;

protected:

	UFUNCTION()
	void HandleOnButtonNextClicked();

	UFUNCTION()
	void HandleOnButtonProceedClicked();

	UFUNCTION( BlueprintImplementableEvent )
	void ShowText( int IndexInSequence );
	
};
