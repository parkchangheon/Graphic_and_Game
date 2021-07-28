READ_ME 

this code is to make character sprint.

In function, void Atutorial_of_cCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)

we can see InputComponent->BindAction......


than go last part of code, make the function of it...



set Max walk Speed 1200 and 

add the code 


if (bIsSprinting)
	Value *= 2;

on
void Atutorial_of_cCharacter::MoveForward(float Value)
void Atutorial_of_cCharacter::MoveRight(float Value)


and this will make Sprinting effect!