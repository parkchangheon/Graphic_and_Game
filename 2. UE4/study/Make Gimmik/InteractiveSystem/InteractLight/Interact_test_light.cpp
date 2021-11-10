// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact_test_light.h"


AInteract_test_light::AInteract_test_light()
{
	State = true;
	Intensity = 10000.f;
	Light = CreateDefaultSubobject<USpotLightComponent>(TEXT("Light"));
	Light->SetupAttachment(GetRootComponent());
	Light->SetIntensity(Intensity);

}

void AInteract_test_light::Interact() 
{
	if (State)
	{
		Light->SetIntensity(0);
	}
	else
	{
		Light->SetIntensity(Intensity);
	}

	State = !State;
}