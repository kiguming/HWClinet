// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HunterController.generated.h"

/**
 * 
 */
UCLASS()
class HUNTERONLINE_API AHunterController : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UPlayerMainWidget> PlayerWidgetClass;

private:
	UPROPERTY()
	UPlayerMainWidget* PlayerWidgetInstance;
};
