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
	Super::NativeOnInitialized();

	Button_Next->OnClicked.AddDynamic( this, &UStoryDisplay::HandleOnButtonNextClicked );
	Button_Previous->OnClicked.AddDynamic( this, &UStoryDisplay::HandleOnButtonPreviousClicked );
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
		ensureMsgf( false, TEXT( "UStoryDisplay: TextSequence is empty upon PresentStoryFromFile!" ) );
	}

	AddToViewport();
}

void UStoryDisplay::HandleOnButtonNextClicked()
{
	if ( NextTextToShow <= TextSequence.Num() - 1 )
	{
		ShowText( NextTextToShow );

		NextTextToShow++;
	}
}

void UStoryDisplay::HandleOnButtonPreviousClicked()
{
	int PreviousTextToShow = NextTextToShow - 2;

	if ( PreviousTextToShow >= 0 )
	{
		ShowText( PreviousTextToShow );

		NextTextToShow--;
	}
}

void UStoryDisplay::HandleOnButtonProceedClicked()
{
	RemoveFromParent();

	OnPresentationFinished.Broadcast();
}
