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
	//Create a reader pointer to read the json data
	FString JsonStr;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonStr);
	//Write the data
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	Request->SetContentAsString(JsonStr);
	Request->ProcessRequest();

}


/*Http call for DELETE*/
void AHttpActor::MyHttpCallPut(FString username)
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	//Request->OnProcessRequestComplete().BindUObject(this, &AHttpActor::OnResponseReceivedGetPassword);
	//This is the url on which to process the request
	Request->SetURL("http://gameplayprogrammingjp.getsandbox.com/users/" + username);
	Request->SetVerb("PUT");
	Request->SetHeader("Content-Type", TEXT("application/json"));
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





