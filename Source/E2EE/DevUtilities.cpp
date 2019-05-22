#include "DevUtilities.h"

#include "Engine/Engine.h"

void UDevUtilities::PrintError( const FString& ErrorMessage )
{
	if ( GEngine )
	{
		GEngine->AddOnScreenDebugMessage( -1, 100.0f, FColor::Red, ErrorMessage );
	}
	else
	{
		UE_LOG( LogTemp, Error, TEXT( "Somehow GEngine isn't valid when logging this error message." ) );
	}
}

void UDevUtilities::PrintWarning( const FString& WarningMessage )
{
	if ( GEngine )
	{
		GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Yellow, WarningMessage );
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "Somehow GEngine isn't valid when logging this warning message." ) );
	}
}

void UDevUtilities::PrintInfo( const FString& Info )
{
	if ( GEngine )
	{
		GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Blue, Info );
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "Somehow GEngine isn't valid when logging this info." ) );
	}
}
