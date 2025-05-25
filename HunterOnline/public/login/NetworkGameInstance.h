// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NetworkGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HUNTERONLINE_API UNetworkGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	FString ServerIP;
	int32 ServerPort;
	FSocket* ClientSocket;
	FTimerHandle ReceiveTimerHandle;
	
	void ConnectToServer(const FString& IP, const int32 Port);
	void SendLoginPacket(const FString& ID, const FString& PW);
	void ReceiveData();
};
