#include "BotGameMode.h"

#include "StoryDisplay.h"

#include "Kismet/GameplayStatics.h"

void ABotGameMode::BeginPlay()
{
	StoryDisplay = CreateWidget<UStoryDisplay>( GetWorld(), StoryDisplayClass );
}

void ABotGameMode::EndGame( bool PlayerWins )
{
	StoryDisplay->FadeToBlack();

	StoryDisplay->OnPresentationFinished.AddDynamic( this, &ABotGameMode::GoBackToHomeMenu );

	if ( PlayerWins )
	{
		StoryDisplay->PresentStoryFromFile( "PlayerWins.txt" );
	}
	else
	{
		StoryDisplay->PresentStoryFromFile( "PlayerLoses.txt" );
	}
}

void ABotGameMode::GoBackToHomeMenu()
{
	UGameplayStatics::OpenLevel( GetWorld(), "HomeMenu" );
}
