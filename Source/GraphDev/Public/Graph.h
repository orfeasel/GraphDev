// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

template<typename InElementType>
class TGraph
{
public:
	typedef TTuple<InElementType, InElementType> Edge;

private:

	TArray<Edge> AdjacencyList;

public:

	TGraph();

	TGraph(const TArray<Edge>& InEdges);

	void PrintAdjacencyList();
	void PrintMatrix();

};

template<typename InElementType>
void TGraph<InElementType>::PrintMatrix()
{
	//TODO
}

template<typename InElementType>
void TGraph<InElementType>::PrintAdjacencyList()
{
	GLog->Log("Printing adjacency list...");
	for (int32 i = 0; i < AdjacencyList.Num(); i++)
	{
		int32 A = static_cast<int32>AdjacencyList[i].Key;
		int32 B = static_cast<int32>AdjacencyList[i].Value;
		FString OutputStr = FString("(") + FString::FromInt(A) +" - "+FString::FromInt(B) +FString(")");
		GLog->Log(OutputStr);
	}
}

template<typename InElementType>
TGraph<InElementType>::TGraph(const TArray<Edge>& InEdges)
{
	for (int32 i = 0; i < InEdges.Num(); i++)
	{
		AdjacencyList.Add(InEdges[i]);
	}
}

template<typename InElementType>
TGraph<InElementType>::TGraph()
{
	AdjacencyList.Empty();
}
