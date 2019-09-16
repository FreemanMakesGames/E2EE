#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StoryDisplay.generated.h"

class UTextBlock;
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnPresentationFinished );

/**
 * 
 */
UCLASS()
class E2EE_API UStoryDisplay : public UUserWidget
{
	GENERATED_BODY()

public:

	UStoryDisplay( const FObjectInitializer& ObjectInitializer );

protected:

	virtual void NativeOnInitialized() override;

public:

	UPROPERTY( BlueprintAssignable )
	FOnPresentationFinished OnPresentationFinished;

protected:

	UPROPERTY( meta = ( BindWidget ), BlueprintReadOnly )
	UTextBlock* TextBlock_StoryText;

	UPROPERTY( meta = ( BindWidget ), BlueprintReadOnly )
	UButton* Button_Next;

	UPROPERTY( meta = ( BindWidget ), BlueprintReadOnly )
	UButton* Button_Previous;

	UPROPERTY( meta = ( BindWidget ), BlueprintReadOnly )
	UButton* Button_Proceed;

public:

	UFUNCTION( BlueprintCallable )
	void PresentStoryFromFile( FString FileName );

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void FadeToBlack();

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
	void HandleOnButtonPreviousClicked();

	UFUNCTION()
	void HandleOnButtonProceedClicked();

protected:

	UFUNCTION( BlueprintImplementableEvent )
	void ShowText( int IndexInSequence );
	
};
