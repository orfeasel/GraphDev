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
	TGraph<int32> Graph = TGraph<int32>(Edges);
	Graph.PrintAdjacencyList();
}