// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Item/Test_SubItem.h"

ATest_SubItem::ATest_SubItem()
{
	//StaticMesh ��� ����
	StaticMesh = LoadObject<UStaticMesh>(nullptr, TEXT(""));
	StaticMeshComponent->SetStaticMesh(StaticMesh);
}
