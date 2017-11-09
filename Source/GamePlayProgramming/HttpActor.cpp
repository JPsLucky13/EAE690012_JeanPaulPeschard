// Fill out your copyright notice in the Description page of Project Settings.

#include "HttpActor.h"


// Sets default values
AHttpActor::AHttpActor(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	//When the object is constructed, Get the HTTP Module
	Http = &FHttpModule::Get();

}

// Called when the game starts or when spawned
void AHttpActor::BeginPlay()
{
	Super::BeginPlay();
	
}

/*Http call for GET*/
void AHttpActor::MyHttpCallGet(FString username)
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpActor::OnResponseReceivedGetPassword);
	//This is the url on which to process the request
	Request->SetURL("http://gameplayprogrammingjp.getsandbox.com/users/" + username);
	Request->SetVerb("GET");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();

}

/*Http call for POST*/
void AHttpActor::MyHttpCallPost(FString username, FString password)
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	//Request->OnProcessRequestComplete().BindUObject(this, &AHttpActor::OnResponseReceived);
	//This is the url on which to process the request
	Request->SetURL("http://gameplayprogrammingjp.getsandbox.com/users");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetStringField("username", username);
	JsonObject->SetStringField("password", password);
	JsonObject->SetStringField("currentLevel", "Level1");
	JsonObject->SetStringField("saveDateTime", "NoTime");
	JsonObject->SetStringField("playerPosition", "0.0f,0.0f,260.0f");
	JsonObject->SetNumberField("machineGunBullets", 50);
	JsonObject->SetBoolField("mission1Active", true);
	JsonObject->SetBoolField("mission1Complete", false);
	JsonObject->SetBoolField("mission2Active", false);
	JsonObject->SetBoolField("mission2Complete", false);
	//Create a reader pointer to read the json data
	FString JsonStr;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonStr);
	//Write the data
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	Request->SetContentAsString(JsonStr);
	Request->ProcessRequest();

}


/*Http call for Put*/
void AHttpActor::MyHttpCallPut(FString username,FString currentLevel, FString saveDateTime, FVector playerPosition, int machineGunBullets, bool mission1Active, bool mission1Complete, bool mission2Active, bool mission2Complete)
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	//Request->OnProcessRequestComplete().BindUObject(this, &AHttpActor::OnResponseReceivedGetPassword);
	//This is the url on which to process the request
	Request->SetURL("http://gameplayprogrammingjp.getsandbox.com/users/" + username);
	Request->SetVerb("PUT");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetStringField("currentLevel", currentLevel);
	JsonObject->SetStringField("saveDateTime", saveDateTime);
	JsonObject->SetStringField("playerPosition", FString::SanitizeFloat(playerPosition.X) + "," + FString::SanitizeFloat(playerPosition.Y) + "," + FString::SanitizeFloat(playerPosition.Z));
	JsonObject->SetNumberField("machineGunBullets", machineGunBullets);
	JsonObject->SetBoolField("mission1Active", mission1Active);
	JsonObject->SetBoolField("mission1Complete", mission1Complete);
	JsonObject->SetBoolField("mission2Active", mission2Active);
	JsonObject->SetBoolField("mission2Complete", mission2Complete);
	//Create a reader pointer to read the json data
	FString JsonStr;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonStr);
	//Write the data
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	Request->SetContentAsString(JsonStr);
	Request->ProcessRequest();

}


/*Http call for DELETE*/
void AHttpActor::MyHttpCallDelete(FString username)
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	//Request->OnProcessRequestComplete().BindUObject(this, &AHttpActor::OnResponseReceivedGetPassword);
	//This is the url on which to process the request
	Request->SetURL("http://gameplayprogrammingjp.getsandbox.com/users/" + username);
	Request->SetVerb("DELETE");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();

}

/*Assigned fucntion on successfull http call*/
void AHttpActor::OnResponseReceivedGetPassword(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{

	ResponseReceived = true;

	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject;

	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		//Get the value of the json object by field name
		password  = JsonObject->GetStringField("password");
		saveGameValues.currentLevel = JsonObject->GetStringField("currentLevel");
		saveGameValues.saveDateTime = JsonObject->GetStringField("saveDateTime");
		TArray<FString> playerPostionStringValues;
		FString playerPosition = JsonObject->GetStringField("playerPosition");
		const TCHAR delim[] = { ',' };
		playerPosition.ParseIntoArray(playerPostionStringValues, delim,true);
		saveGameValues.playerPosition = FVector(FCString::Atof(*playerPostionStringValues[0]), FCString::Atof(*playerPostionStringValues[1]), FCString::Atof(*playerPostionStringValues[2]));
		saveGameValues.machineGunBullets = JsonObject->GetIntegerField("machineGunBullets");
		saveGameValues.mission1Active = JsonObject->GetBoolField("mission1Active");
		saveGameValues.mission1Complete = JsonObject->GetBoolField("mission1Complete");
		saveGameValues.mission2Active = JsonObject->GetBoolField("mission2Active");
		saveGameValues.mission2Complete = JsonObject->GetBoolField("mission2Complete");
	}

}

bool AHttpActor::ValidatePassword(FString p_password)
{
	if (p_password.Equals(password))
	{
		return true;
	}
	else
	{
		return false;
	}
}





