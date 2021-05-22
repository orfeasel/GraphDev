// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphTester.h"
#include "Graph.h"

// Sets default values
AGraphTester::AGraphTester()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGraphTester::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGraphTester::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGraphTester::Test()
{
	typedef TGraph<int32>::Edge Edge;
	TArray<Edge> Edges;
	Edges.Add(Edge(1,5));
	Edges.Add(Edge(5,2));
	Edges.Add(Edge(7,2));
	Edges.Add(Edge(1,3));
	Edges.Add(Edge(2,6));
	Edges.Add(Edge(2,7));
	Edges.Add(Edge(7,3));

	TGraph<int32> Graph = TGraph<int32>(Edges);
	Graph.PrintAdjacencyList();
	GLog->Log("Order:"+FString::FromInt(Graph.Order()));
	GLog->Log("Size:"+FString::FromInt(Graph.Size()));

	int32 BFS_Start_Vertex = 1;
	TArray<int32> BFSPath = Graph.BFS(BFS_Start_Vertex);
	GLog->Log("--- BFS for " + FString::FromInt(BFS_Start_Vertex) + " ----");
	for (int32 i = 0; i < BFSPath.Num(); i++)
	{
		GLog->Log(FString::FromInt(BFSPath[i]));
	}


}