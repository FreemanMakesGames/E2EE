#pragma once

#include "Runtime/Engine/Classes/Engine/Texture2D.h"

//#include "CoreMinimal.h"
#include "Item.generated.h"

USTRUCT()
struct FItem
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere )
	FString Name;

	UPROPERTY( EditAnywhere )
	UTexture2D* Icon;

};
