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

	TArray<Edge> AdjacencyLists;

	/**
	 * Checks if there's a direct edge connecting A and B
	 * @param A - vertex A
	 * @param B - vertex B
	 * @return true if an edge is connecting A and B
	 */
	bool VerticesConnected(const InElementType& A, const InElementType& B) const;

public:

	TGraph();

	TGraph(const TArray<Edge>& InEdges);

	void PrintAdjacencyList();
	void PrintAdjacencyMatrix();

	TArray<InElementType> GetAdjacentVertices(const InElementType& Vertex) const;

	TArray<InElementType> BFS(const InElementType& Start) const;

	TArray<InElementType> DFS(const InElementType& Start) const;

	TArray<InElementType> GetVertices() const;

	int32 Order() const;
	int32 Size() const;

	FString (*/*const*/ ToStr)(InElementType);

};

template<typename InElementType>
bool TGraph<InElementType>::VerticesConnected(const InElementType& A, const InElementType& B) const
{
	bool result = false;
	for (int32 i = 0; i < AdjacencyLists.Num(); i++)
	{
		//TODO: Directional / undirectional
		Edge TestEdge = AdjacencyLists[i];
		if (TestEdge.Key == A && TestEdge.Value == B)
		{
			return true;
		}
		else if (TestEdge.Key == B && TestEdge.Value == A)
		{
			return true;
		}
	}
	return result;
}

template<typename InElementType>
TArray<InElementType> TGraph<InElementType>::GetVertices() const
{
	//TODO: Extend this for directed/undirected graphs
	TSet<InElementType> Vertices;
	for (int32 i = 0; i < AdjacencyLists.Num(); i++)
	{
		Vertices.Add(AdjacencyLists[i].Key);
		Vertices.Add(AdjacencyLists[i].Value);
	}
	return Vertices.Array();
}

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

	for (int32 i = 0; i < AdjacencyLists.Num(); i++)
	{
		if (AdjacencyLists[i].Key == Vertex)
		{
			AdjacentVertices.Add(AdjacencyLists[i].Value);
		}
		else if (AdjacencyLists[i].Value == Vertex) //for undirected graphs TODO: fix this
		{
			AdjacentVertices.Add(AdjacencyLists[i].Key);
		}
	}

	return AdjacentVertices;
}

template<typename InElementType>
int32 TGraph<InElementType>::Size() const
{
	return AdjacencyLists.Num();
}

template<typename InElementType>
int32 TGraph<InElementType>::Order() const
{
	TSet<InElementType> Vertices;
	for (int32 i = 0; i < AdjacencyLists.Num(); i++)
	{
		Vertices.Add(AdjacencyLists[i].Value);
		Vertices.Add(AdjacencyLists[i].Key);
	}

	return Vertices.Num();
}

template<typename InElementType>
void TGraph<InElementType>::PrintAdjacencyMatrix()
{
	//TODO
	FString VerticesNamesStr = FString("# ");
	GLog->Log("Printing adjacency matrix");

	//Building top guide
	TArray<InElementType> Vertices = GetVertices();
	for (int32 i = 0; i < Vertices.Num(); i++)
	{
		int32 Vertex = static_cast<int32>(Vertices[i]);
		VerticesNamesStr.Append(FString::FromInt(Vertex) + FString(" "));
	}
	GLog->Log(VerticesNamesStr);

	for (int32 i = 0; i < Vertices.Num(); i++)
	{
		int32 Vertex = static_cast<int32>(Vertices[i]);
		FString RowStr = FString::FromInt(Vertex) + FString(" ");
		for (int32 j = 0; j < Vertices.Num(); j++)
		{
			bool bResult = VerticesConnected(Vertices[i],Vertices[j]);
			FString ResultStr = (bResult) ? FString("1") : FString("0");
			ResultStr+=FString(" ");
			RowStr+=ResultStr;
		}
		GLog->Log(RowStr);
	}


	
	

}

template<typename InElementType>
void TGraph<InElementType>::PrintAdjacencyList()
{
	GLog->Log("Printing adjacency list...");
	for (int32 i = 0; i < AdjacencyLists.Num(); i++)
	{
		/*int32 A = static_cast<int32>(AdjacencyLists[i].Key);
		int32 B = static_cast<int32>(AdjacencyLists[i].Value);
		FString OutputStr = FString("(") + FString::FromInt(A) +" - "+FString::FromInt(B) +FString(")");
		GLog->Log(OutputStr);*/

		FString A = ToStr(AdjacencyLists[i].Key);
		FString B = ToStr(AdjacencyLists[i].Value);
		FString OutputStr = FString("(") + A + " - "+ B +FString(")");
		GLog->Log(OutputStr);
	}
}

template<typename InElementType>
TGraph<InElementType>::TGraph(const TArray<Edge>& InEdges)
{
	for (int32 i = 0; i < InEdges.Num(); i++)
	{
		AdjacencyLists.Add(InEdges[i]);
	}
}

template<typename InElementType>
TGraph<InElementType>::TGraph()
{
	AdjacencyLists.Empty();
}
