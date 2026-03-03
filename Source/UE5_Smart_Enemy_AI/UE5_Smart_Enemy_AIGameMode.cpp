// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5_Smart_Enemy_AIGameMode.h"
#include "UE5_Smart_Enemy_AICharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE5_Smart_Enemy_AIGameMode::AUE5_Smart_Enemy_AIGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
