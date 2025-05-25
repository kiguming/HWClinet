// Fill out your copyright notice in the Description page of Project Settings.


#include "login/LoginWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "login/NetworkGameInstance.h"

void ULoginWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (LoginButton)
	{
		LoginButton->OnClicked.AddDynamic(this, &ULoginWidget::LoginButtonClicked);
	}
	
}

void ULoginWidget::LoginButtonClicked()
{
	UNetworkGameInstance* NetInstance = Cast<UNetworkGameInstance>(GetGameInstance());

	const FString IPAddress = IPInput->GetText().ToString().TrimStartAndEnd();
	const FString ID = IDInput->GetText().ToString().TrimStartAndEnd();
	const FString PW = PWInput->GetText().ToString().TrimStartAndEnd();
	FString ErrorMessage;
	if (NetInstance)
	{
		if (IPInput->GetText().IsEmpty())
		{
			UE_LOG(LogTemp, Warning, TEXT("IP 주소를 입력해주세요."));
			ErrorMessage += TEXT("IP 주소가 비어있습니다.\n");
			
		}
		if (IDInput->GetText().IsEmpty())
		{
			UE_LOG(LogTemp, Warning, TEXT("ID를 입력해주세요."));
			ErrorMessage += TEXT("ID칸이 비어있습니다.\n");
			
		}
		if (PWInput->GetText().IsEmpty())
		{
			UE_LOG(LogTemp, Warning, TEXT("패스워드를 입력해주세요."));
			ErrorMessage += TEXT("패스워드 칸이 비어있습니다.\n");
			
		}
		
		if (!ErrorMessage.IsEmpty())
		{
			if (ErrorTextBlcok)
			{
				ErrorTextBlcok->SetText(FText::FromString(ErrorMessage));
			}
			return;
		}
		
		NetInstance->ConnectToServer(IPAddress, 1234);
		NetInstance->SendLoginPacket(ID, PW);

	}else
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance가 UNetworkGameInstance로 캐스팅되지 않았습니다."));
	}
}
