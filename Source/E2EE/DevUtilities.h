#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DevUtilities.generated.h"

/**
 * 
 */
UCLASS()
class E2EE_API UDevUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION( BlueprintCallable )
	static void PrintError( const FString& ErrorMessage );

	UFUNCTION( BlueprintCallable )
	static void PrintWarning( const FString& WarningMessage );

	UFUNCTION( BlueprintCallable )
	static void PrintInfo( const FString& Info );
	
};
