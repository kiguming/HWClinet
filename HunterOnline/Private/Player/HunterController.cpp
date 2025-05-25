// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HunterController.h"
#include "Player/PlayerMainWidget.h"

void AHunterController::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerWidgetClass)
	{
		PlayerWidgetInstance = CreateWidget<UPlayerMainWidget>(this, PlayerWidgetClass);
		if (PlayerWidgetInstance)
		{
			PlayerWidgetInstance->AddToViewport();
			
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("LoginWidgetClass Error"));
	}
}
