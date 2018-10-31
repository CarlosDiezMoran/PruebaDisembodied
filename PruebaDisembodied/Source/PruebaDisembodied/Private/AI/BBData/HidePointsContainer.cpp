// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BBData/HidePointsContainer.h"
#include "AI/Points/HidePoint.h"
#include "DebugLibrary.h"

UHidePointsContainer::UHidePointsContainer() : Super() 
{
	DISEMLOG();

	HidePoints.Empty();
}