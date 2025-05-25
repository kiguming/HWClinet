// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTERONLINE_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
		class UEditableText* IDInput;

	UPROPERTY(meta = (BindWidget))
		class UEditableText* IPInput;

	UPROPERTY(meta = (BindWidget))
		class UEditableText* PWInput;

	UPROPERTY(meta = (BindWidget))
 		class UButton* LoginButton;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ErrorTextBlcok;


	UFUNCTION()
	virtual void NativeConstruct() override;


	UFUNCTION()
	void LoginButtonClicked();
	
};
