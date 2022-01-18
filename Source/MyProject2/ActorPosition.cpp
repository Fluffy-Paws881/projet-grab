// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorPosition.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UActorPosition::UActorPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


FString UActorPosition::GetName() const
{
	return GetOwner()->GetName();
}

FVector UActorPosition::GetLocation() const
{
	return GetOwner()->GetActorLocation();
}

// Called when the game starts
void UActorPosition::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActorPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GEngine != nullptr) {
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, *GetName());
		GEngine->AddOnScreenDebugMessage(1, 2, FColor::Green, *GetLocation().ToString());
	}

	UE_LOG(LogTemp, Warning, TEXT("Name : %s, Position : %s"), *GetName(), *GetLocation().ToString());

	if (GetOwner()->FindComponentByClass<UPhysicsHandleComponent>()->GrabbedComponent)
	{
		GetOwner()->FindComponentByClass<UPhysicsHandleComponent>()->SetTargetLocation((GetOwner()->GetActorForwardVector() * 500.f) + (GetOwner()->GetActorForwardVector() + GetOwner()->GetActorLocation()));
	}
}

void UActorPosition::startGrab()
{
	FHitResult OutHit;
	FCollisionQueryParams CollisionParams(FName(TEXT("")), false, GetOwner());
	FVector StartTrace = GetOwner()->GetActorForwardVector() + GetOwner()->GetActorLocation();
	FVector EndTrace = ((GetOwner()->GetActorForwardVector() * 1000.f) + StartTrace);

	FString StringExample = TEXT("String example");

	 GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	

	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 1, 0, 1);

	if (GetWorld()->LineTraceSingleByChannel(OutHit, StartTrace, EndTrace, ECollisionChannel::ECC_PhysicsBody, CollisionParams))
	{
		if (OutHit.bBlockingHit)
		{
			if (GEngine) {

				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetComponent()->GetName()));

			}
			if (GetOwner()->FindComponentByClass<UPhysicsHandleComponent>()) 
			{
				GetOwner()->FindComponentByClass<UPhysicsHandleComponent>()->GrabComponentAtLocation
				(
					OutHit.GetComponent(),
					NAME_None,
					EndTrace 
				);
			}
		}
			
	}

}

void UActorPosition::releaseGrab()
{
	if (GetOwner()->FindComponentByClass<UPhysicsHandleComponent>()->GrabbedComponent)
	{
		GetOwner()->FindComponentByClass<UPhysicsHandleComponent>()->ReleaseComponent();
	}
}



