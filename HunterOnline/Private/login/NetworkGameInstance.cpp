// Fill out your copyright notice in the Description page of Project Settings.


#include "login/NetworkGameInstance.h"
#include "SocketSubsystem.h"
#include "Sockets.h"
#include "Common/TcpSocketBuilder.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "login/LoginPlayerController.h"
#include "login/LoginWidget.h"


void UNetworkGameInstance::ConnectToServer(const FString& IP, const int32 Port)
{
	ServerIP = IP;
	ServerPort = Port;
	
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	TSharedRef<FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr();

	bool bIsValid;
	Addr->SetIp(*ServerIP, bIsValid);
	Addr->SetPort(ServerPort);

	
	ClientSocket = FTcpSocketBuilder(TEXT("MyClientSocket")).AsBlocking().AsReusable().Build();
	
	ClientSocket->Connect(*Addr);

	GetWorld()->GetTimerManager().SetTimer(ReceiveTimerHandle, this, &UNetworkGameInstance::ReceiveData, 0.1f, true);
}

void UNetworkGameInstance::SendLoginPacket(const FString& ID, const FString& PW)
{
	FString Msg = FString::Printf(TEXT("LOGIN %s %s"), *ID, *PW);
	FTCHARToUTF8 Convert(*Msg);
	int32 BytesSent = 0;
	ClientSocket->Send((uint8*)Convert.Get(), Convert.Length(), BytesSent);
}

void UNetworkGameInstance::ReceiveData()
{
	uint32 PendingDataSize = 0;
	if (ClientSocket->HasPendingData(PendingDataSize))
	{
		TArray<uint8> ReceivedData;
		ReceivedData.SetNumUninitialized(PendingDataSize);
		int32 Read = 0;

		ClientSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);

		FString Response = FString(UTF8_TO_TCHAR(reinterpret_cast<const char*>(ReceivedData.GetData())));
		UE_LOG(LogTemp, Log, TEXT("서버 응답: %s"), *Response);

		if (Response.Contains(TEXT("LOGIN_SUCCESS")))
		{
			UE_LOG(LogTemp, Log, TEXT("로그인 성공!"));
			ALoginPlayerController* LController = Cast<ALoginPlayerController>(GetWorld()->GetFirstPlayerController());
			if (LController)
			{
				LController->GetLoginWidget()->ErrorTextBlcok->SetText(FText::FromString(TEXT("로그인 성공")));
			}
			UGameplayStatics::OpenLevel(this, "StartMap");
		}
		else if (Response.Contains(TEXT("LOGIN_FAIL")))
		{
			UE_LOG(LogTemp, Warning, TEXT("로그인 실패!"));
			// 예: UI에서 경고 띄우기
			
			ALoginPlayerController* LController = Cast<ALoginPlayerController>(GetWorld()->GetFirstPlayerController());
			if (LController)
			{
				
				LController->GetLoginWidget()->ErrorTextBlcok->SetText(FText::FromString(TEXT("아이디나 비밀번호가 틀렸습니다.")));
			}
			
		}
	}
}
