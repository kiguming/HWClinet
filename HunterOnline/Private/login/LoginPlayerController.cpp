// Fill out your copyright notice in the Description page of Project Settings.


#include "login/LoginPlayerController.h"
#include "login/LoginWidget.h"

void ALoginPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (LoginWidgetClass)
	{
		LoginWidgetInstance = CreateWidget<ULoginWidget>(this, LoginWidgetClass);
		if (LoginWidgetInstance)
		{
			LoginWidgetInstance->AddToViewport();
			SetInputMode(FInputModeUIOnly());
			bShowMouseCursor = true;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("LoginWidgetClass Error"));
	}
	
}
