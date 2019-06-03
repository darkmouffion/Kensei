// Fill out your copyright notice in the Description page of Project Settings.


#include "ShinkenMotion.h"

FString UShinkenMotion::decodeTechnique(TArray<FString> sequence, float longN, float longE, float longS, float longW)
{
	TArray<FString> ordreMin;
	ordreMin.Add(TEXT("S"));
	ordreMin.Add(TEXT("SW"));
	ordreMin.Add(TEXT("W"));
	ordreMin.Add(TEXT("NW"));
	ordreMin.Add(TEXT("N"));
	ordreMin.Add(TEXT("NE"));
	ordreMin.Add(TEXT("E"));
	ordreMin.Add(TEXT("SE"));

	if (sequence.Num() < 4) return TEXT("");		// technique incomplete (en train de faire l'enten ou on a rate)

	int32 lastIndex = 0;
	int32 nbSuccIndex = 0;
	int32 seqi = 0;

	// est-ce qu'on fait un beau enten ?
	for (const FString &text : sequence) {
		int32 index = ordreMin.Find(text);

		if (index == 7 || (index == 0 && lastIndex > 4)) break;		// SE ou S apres avoir ete au nord

		if (index >= lastIndex) ++nbSuccIndex;
		lastIndex = index;
		++seqi;
	}

	if (nbSuccIndex < 4) return TEXT("");		// technique ratee, enten pas assez bien!!

	if (seqi >= sequence.Num()) {
		if (fabs(longN) < 1.5*fabs(longS))
			return TEXT("TSUKI");		// TSUKI simple
		return TEXT("MEN");			// MEN simple : la pointe va directement vers la tete
	}
	if (sequence[seqi][0] != TCHAR('S')) return TEXT("");		// technique inconnue!4
	if (seqi == sequence.Num() - 1) return TEXT("MENTACHI");			// MEN TACHI : la pointe descend vers le ventre

	while (seqi < sequence.Num() && sequence[seqi][0] == TCHAR('S')) ++seqi;
	if (seqi >= sequence.Num()) return TEXT("MENTACHI");

	if (sequence[seqi].Contains(TEXT("N"))) {
		// Kurai tachi		... + NE|N				= contient au moins un S puis contient un N
		// Kiri wari		... + NE|N et SE|S		= contient au moins un S puis un N puis un S

		while (seqi < sequence.Num() && sequence[seqi][0] == TCHAR('N')) ++seqi;
		if (seqi >= sequence.Num()) return TEXT("KURAITACHI");

		while (seqi < sequence.Num() && sequence[seqi][0] == TCHAR('S')) ++seqi;
		if (seqi >= sequence.Num()) return TEXT("KIRIWARI");

		return TEXT("KURAITACHI");

	}
	else if (sequence[seqi].Contains(TEXT("W"))) {
		// Tsuki kaeshi		... + SW|W|NW et N|NE et NE|E	= contient au moins un S puis W puis N puis E
		// Enbi ken			... + SW|W|NW et N|NE et NE|E	= contient au moins un S puis W puis N puis E
		while (seqi < sequence.Num() && sequence[seqi].Contains(TEXT("W"))) ++seqi;
		if (seqi >= sequence.Num()) return TEXT("MENTACHI");

		while (seqi < sequence.Num() && sequence[seqi].Contains(TEXT("N"))) ++seqi;
		if (seqi >= sequence.Num()) return TEXT("MENTACHI");

		while (seqi < sequence.Num() && sequence[seqi].Contains(TEXT("E"))) ++seqi;
		if (seqi < sequence.Num()) return TEXT("MENTACHI");

		if (fabs(longN) < 1.5*fabs(longS)) return TEXT("TSUKIKAESHI");
		return TEXT("ENBIKEN");

	}
	else return TEXT("");

	return TEXT("ENTEN");
}