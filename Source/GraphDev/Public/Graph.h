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

	TArray<Edge> Edges;

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

	void PrintAdjacencyLists();
	void PrintAdjacencyMatrix();

	TArray<InElementType> GetAdjacentVertices(const InElementType& Vertex) const;

	TArray<InElementType> BFS(const InElementType& Start) const;

	TArray<InElementType> DFS(const InElementType& Start) const;

	TArray<InElementType> GetVertices() const;
	TArray<Edge> GetEdges() const;

	int32 Order() const;
	int32 Size() const;

	FString (*ToStr)(InElementType);

};

template<typename InElementType>
TArray<TGraph::Edge> TGraph<InElementType>::GetEdges() const
{
	return Edges;
}

template<typename InElementType>
bool TGraph<InElementType>::VerticesConnected(const InElementType& A, const InElementType& B) const
{
	bool result = false;
	for (int32 i = 0; i < Edges.Num(); i++)
	{
		//TODO: Directional / undirectional
		Edge TestEdge = Edges[i];
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
	for (int32 i = 0; i < Edges.Num(); i++)
	{
		Vertices.Add(Edges[i].Key);
		Vertices.Add(Edges[i].Value);
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

	for (int32 i = 0; i < Edges.Num(); i++)
	{
		if (Edges[i].Key == Vertex)
		{
			AdjacentVertices.Add(Edges[i].Value);
		}
		else if (Edges[i].Value == Vertex) //for undirected graphs TODO: fix this
		{
			AdjacentVertices.Add(Edges[i].Key);
		}
	}

	return AdjacentVertices;
}

template<typename InElementType>
int32 TGraph<InElementType>::Size() const
{
	return Edges.Num();
}

template<typename InElementType>
int32 TGraph<InElementType>::Order() const
{
	TSet<InElementType> Vertices;
	for (int32 i = 0; i < Edges.Num(); i++)
	{
		Vertices.Add(Edges[i].Value);
		Vertices.Add(Edges[i].Key);
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
		InElementType Vertex = Vertices[i];
		FString ElementStr = ToStr(Vertex); //Make sure to bind ToStr callback
		VerticesNamesStr.Append(ElementStr + FString(" "));
	}
	GLog->Log(VerticesNamesStr);

	for (int32 i = 0; i < Vertices.Num(); i++)
	{
		InElementType Vertex = Vertices[i];
		FString ElementStr = ToStr(Vertex);
		FString RowStr = ElementStr + FString(" ");
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
void TGraph<InElementType>::PrintAdjacencyLists()
{
	GLog->Log("Printing adjacency list...");
	for (int32 i = 0; i < Edges.Num(); i++)
	{
		//Make sure to bind ToStr callback
		FString A = ToStr(Edges[i].Key);
		FString B = ToStr(Edges[i].Value);
		FString OutputStr = FString("(") + A + " - " + B + FString(")");
		GLog->Log(OutputStr);
	}
}

template<typename InElementType>
TGraph<InElementType>::TGraph(const TArray<Edge>& InEdges)
{
	for (int32 i = 0; i < InEdges.Num(); i++)
	{
		Edges.Add(InEdges[i]);
	}
}

template<typename InElementType>
TGraph<InElementType>::TGraph()
{
	Edges.Empty();
}
