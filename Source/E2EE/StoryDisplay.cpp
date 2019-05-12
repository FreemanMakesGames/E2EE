#include "StoryDisplay.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"


UStoryDisplay::UStoryDisplay( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{

}

void UStoryDisplay::NativeOnInitialized()
{
	Button_Next->OnClicked.AddDynamic( this, &UStoryDisplay::HandleOnButtonNextClicked );
	Button_Proceed->OnClicked.AddDynamic( this, &UStoryDisplay::HandleOnButtonProceedClicked );

	Button_Proceed->SetVisibility( ESlateVisibility::Hidden );
}

void UStoryDisplay::PresentStoryFromFile( FString FileName )
{
	FString FilePath = FPaths::ProjectContentDir() + TEXT( "Story/" ) + FileName;

	FFileHelper::LoadFileToStringArray( TextSequence, *FilePath );

	if ( TextSequence.Num() > 0 )
	{
		ShowText( 0 );

		NextTextToShow = 1;
	}
	else
	{
		UE_LOG( LogTemp, Error, TEXT( "UStoryDisplay: TextSequence is empty upon PresentStoryFromFile!" ) );
		return;
	}

	AddToViewport();
}

void UStoryDisplay::HandleOnButtonNextClicked()
{
	if ( NextTextToShow <= TextSequence.Num() - 1 )
	{
		ShowText( NextTextToShow );
	}

	NextTextToShow++;
}

void UStoryDisplay::HandleOnButtonProceedClicked()
{
	RemoveFromParent();
}
