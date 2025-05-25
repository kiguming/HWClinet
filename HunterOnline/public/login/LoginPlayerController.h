// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LoginPlayerController.generated.h"

class ULoginWidget;

/**
 * 
 */
UCLASS()
class HUNTERONLINE_API ALoginPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	virtual void BeginPlay() override;

	ULoginWidget* GetLoginWidget(){return LoginWidgetInstance;}
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class ULoginWidget> LoginWidgetClass;

private:
	UPROPERTY()
	ULoginWidget* LoginWidgetInstance;
};
