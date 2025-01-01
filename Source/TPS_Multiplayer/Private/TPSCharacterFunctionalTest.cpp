// (C) ToasterCat Studios 2024

//#include "TPSCharacterFunctionalTest.h"

#include "CoreTypes.h"
#include "Containers/UnrealString.h"
#include "Misc/AutomationTest.h"

#include "Character/TPSCharacter.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTPSCharacterTest, "TPSCharacter.TestDoAThing", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FTPSCharacterTest::RunTest(FString const& Parameters) {
	return true;
}

/*bool FTPSCharacterTest::RunAnotherTest(FString const& Parameters) {
	const auto BoolToTest = false;
	TestTrue("bool to test", BoolToTest);

	const auto FloatToTest = 0.F;
	const auto Expected = 10.F;
	const auto Tolerance = KINDA_SMALL_NUMBER;
	TestEqual("float to test", FloatToTest, Expected, Tolerance);

	return true;
}*/

BEGIN_DEFINE_SPEC(FDifferentCharacterTest, "TPSCharacter", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
int UsefulInteger = 0;
void UtilityMethodForTest();
END_DEFINE_SPEC(FDifferentCharacterTest)

void FDifferentCharacterTest::Define() {
	BeforeEach([this]() {
		UE_LOG(LogTemp, Display, TEXT("b1"));
		//ATPSCharacter* character = new ATPSCharacter();
		});

	Describe("Initialization", [this]() {
		BeforeEach([this]() {
			UE_LOG(LogTemp, Display, TEXT("b2"));
			});

		It("DoAnotherThingTest", [this]() {
			UE_LOG(LogTemp, Display, TEXT("t1"));
			});

		Describe("SubInitialization", [this]() {
			BeforeEach([this]() {
				UE_LOG(LogTemp, Display, TEXT("b3"));
				});

			It("Huh", [this]() {
				UE_LOG(LogTemp, Display, TEXT("t23"));
				});

			It("Whut", [this]() {
				UE_LOG(LogTemp, Display, TEXT("t23"));
				});

			AfterEach([this]() {
				UE_LOG(LogTemp, Display, TEXT("a1"));
				});
			});

		AfterEach([this]() {
			UE_LOG(LogTemp, Display, TEXT("a2"));
			});

		AfterEach([this]() {
			UE_LOG(LogTemp, Display, TEXT("a3"));
			});
		});

	AfterEach([this]() {
		UE_LOG(LogTemp, Display, TEXT("a4"));
		});
}


#if WITH_DEV_AUTOMATION_TESTS

BEGIN_DEFINE_SPEC(TPSCharacterAutoTest, "TPSCharacter", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
END_DEFINE_SPEC(TPSCharacterAutoTest)

void TPSCharacterAutoTest::Define() {
	Describe("Initializes", [this]() {
		It("Should have the correct default values", [this]() {
			ATPSCharacter character();

			TestTrue(TEXT("FireRound succeeds when non-empty magazine"), character.IsAlive());
			TestEqual(TEXT("Current magazine decrements by one"), character.CurrentHealth, 100);
			TestEqual(TEXT("total ammo decrements by one"), character.CurrentArmor, 100);
			});
	});
}


#endif