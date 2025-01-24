// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpyUI.h"

#define LOCTEXT_NAMESPACE "mynamespace"

void UJumpyUI::SetHeight(int32 Height)
{
	FText HeightFText = FText::Format(LOCTEXT("ShowHeight", "{0}"), Height / 100);
	HeightText->SetText(HeightFText);

	float temp = static_cast<float>(Height) / MaxHeight;
	//UE_LOG(LogTemp, Warning, TEXT("Value: %f"), temp);
	MaxHeightProgressBar->SetPercent((static_cast<float>(Height)/100) / MaxHeight);

	if ((Height/100) > (MaxHeight))
	{		
		/*UE_LOG(LogTemp, Warning, TEXT("height: % d"), Height/100);
		UE_LOG(LogTemp, Warning, TEXT("Maxheight: % d"), MaxHeight);*/
		//IncreaseCoin(1);

		MaxHeight = Height/100;

		FText MaxHeightFText = FText::Format(LOCTEXT("ShowMaxHeight", "{0}"), MaxHeight);
		MaxHeightTextBlock->SetText(MaxHeightFText);
	}
}

void UJumpyUI::SetCoin(int32 Amount)
{
	FText cointAmountFText = FText::AsCurrency(Amount, "$");
	CoinText->SetText(cointAmountFText);
}

void UJumpyUI::IncreaseCoin(int32 Amount)
{
	CoinAmount += Amount;
	UE_LOG(LogTemp, Warning, TEXT("Coin: %d"), CoinAmount);
	SetCoin(CoinAmount);
}
 