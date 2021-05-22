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

	TArray<InElementType> GetAdjacentVertices(const InElementType& Vertex) const;

	TArray<InElementType> BFS(const InElementType& Start) const;

	TArray<InElementType> DFS(const InElementType& Start) const;


	int32 Order() const;
	int32 Size() const;

};

template<typename InElementType>
TArray<InElementType> TGraph<InElementType>::DFS(const InElementType& Start) const
{
	TArray<InElementType> DFS_Path;

	TSet<InElementType> VisitedVertices;
	VisitedVertices.Add(Start);

	TArray<InElementType> Stack;
	Stack.Push(Start);

	while (Stack.Num() > 0)
	{
		InElementType Top = Stack.Pop();
		DFS_Path.Add(Top);
		TArray<InElementType> AdjacentVertices = GetAdjacentVertices(Top);
		for (int32 i = 0; i < AdjacentVertices.Num(); i++)
		{
			if (!VisitedVertices.Contains(AdjacentVertices[i]))
			{
				VisitedVertices.Add(AdjacentVertices[i]);
				Stack.Push(AdjacentVertices[i]);
			}
		}
	}

	return DFS_Path;
}

template<typename InElementType>
TArray<InElementType> TGraph<InElementType>::BFS(const InElementType& Start) const
{
	TArray<InElementType> BFS_Path;

	//Keeping track of visited elements
	TSet<InElementType> VisitedVertices;
	VisitedVertices.Add(Start);

	//Keeping track of the elements we have in a queue in case we want to backtrack later on
	TQueue<InElementType> Queue;
	Queue.Enqueue(Start);
	
	while (!Queue.IsEmpty())
	{
		InElementType Front;
		Queue.Dequeue(Front);
		BFS_Path.Add(Front);

		//Get adjacent vertices and add them in the queue if we haven't visited them yet
		TArray<InElementType> AdjacentVertices = GetAdjacentVertices(Front);	
		for (int32 i = 0; i < AdjacentVertices.Num(); i++)
		{
			if (!VisitedVertices.Contains(AdjacentVertices[i]))
			{
				VisitedVertices.Add(AdjacentVertices[i]);
				Queue.Enqueue(AdjacentVertices[i]);
			}
		}
	}

	return BFS_Path;
}

template<typename InElementType>
TArray<InElementType> TGraph<InElementType>::GetAdjacentVertices(const InElementType& Vertex) const
{
	TArray<InElementType> AdjacentVertices;

	for (int32 i = 0; i < AdjacencyList.Num(); i++)
	{
		if (AdjacencyList[i].Key == Vertex)
		{
			AdjacentVertices.Add(AdjacencyList[i].Value);
		}
		else if (AdjacencyList[i].Value == Vertex) //for undirected graphs TODO: fix this
		{
			AdjacentVertices.Add(AdjacencyList[i].Key);
		}
	}

	return AdjacentVertices;
}

template<typename InElementType>
int32 TGraph<InElementType>::Size() const
{
	return AdjacencyList.Num();
}

template<typename InElementType>
int32 TGraph<InElementType>::Order() const
{
	TSet<InElementType> Vertices;
	for (int32 i = 0; i < AdjacencyList.Num(); i++)
	{
		Vertices.Add(AdjacencyList[i].Value);
		Vertices.Add(AdjacencyList[i].Key);
	}

	return Vertices.Num();
}

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
		int32 A = static_cast<int32>(AdjacencyList[i].Key);
		int32 B = static_cast<int32>(AdjacencyList[i].Value);
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
