// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "HttpActor.generated.h"

UCLASS()
class GAMEPLAYPROGRAMMING_API AHttpActor : public AActor
{
	GENERATED_BODY()
	
public:	

	FHttpModule* Http;

	FString password;
	bool ResponseReceived = false;

	/* The actual HTTP call for GET*/
	UFUNCTION(BlueprintCallable, Category = "RestAPI")
	void MyHttpCallGet(FString username);

	/* The actual HTTP call for POST*/
	UFUNCTION(BlueprintCallable, Category = "RestAPI")
	void MyHttpCallPost(FString username, FString password);

	/* The actual HTTP call for PUT*/
	UFUNCTION(BlueprintCallable, Category = "RestAPI")
	void MyHttpCallPut(FString username);

	/* The actual HTTP call for DELETE*/
	UFUNCTION(BlueprintCallable, Category = "RestAPI")
	void MyHttpCallDelete(FString username);

	/*Assign this function to call when the GET request processes successfully*/
	void OnResponseReceivedGetPassword(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	/*Validate on the client side the password of the user*/
	UFUNCTION(BlueprintCallable, Category = "RestAPI")
	bool ValidatePassword(FString p_password);

	// Sets default values for this actor's properties
	AHttpActor(const class FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;

	
	
};
