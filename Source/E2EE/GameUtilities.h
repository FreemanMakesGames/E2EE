#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameUtilities.generated.h"

class AActor;

/**
 * 
 */
UCLASS( Blueprintable )
class E2EE_API UGameUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
# pragma region Actor Disabling/Enabling
	UFUNCTION( BlueprintCallable )
	static void DisableActor( AActor* TargetActor );

	UFUNCTION( BlueprintCallable )
	static void EnableActor( AActor* TargetActor );

	UFUNCTION( BlueprintCallable )
	static void ToggleActor( AActor* TargetActor, bool IsActive );
# pragma endregion
	
};
