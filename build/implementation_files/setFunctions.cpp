#include "setFunctions.h"
#include "set.h"
#include "set.cpp"

using namespace std;
// Returns a set that is the Union of the two sets s1 and s2
Set<char> setUnion(const Set<char> &s1, const Set<char> &s2)
{
	Set<char> result;
	size_t len1 = s1.cardinality();
	size_t len2 = s2.cardinality();
	for (size_t i = 0; i < len1; i++)
	{
		result.insertElement(s1[i]);
	}
	for (size_t i = 0; i < len2; i++)
	{
		result.insertElement(s2[i]);
	}

	// Add your code here

	return result;
}

// Returns a set that is the intersection of the two sets s1 and s2
Set<char> setIntersection(const Set<char> &s1, const Set<char> &s2)
{
	Set<char> result;
	int inc = 0;
	size_t len1 = s1.cardinality();
	size_t len2 = s2.cardinality();

	//	Set<char> s1{ 's','f','g','h','h','i','a', 'b' }; //8
	//	Set<char> s2{ 'e','d','a','g','b','h','i','a','h' }; 10
	for (size_t i = 0; i < len1; i++) // i <= 8 loops through the smallest set
	{
		char s1_value = s1[i]; // s
		for (size_t t = 0; t < len2; t++)
		{
			if (s1_value == s2[t]) // s == e?
			{
				result.insertElement(s1_value);
			}
		}
	}

	// not done

	return result;
}

// Returns a set that is the s1 - s2
Set<char> setDiff(const Set<char> &s1, const Set<char> &s2)
{
	Set<char> result = s1;
	
	int size = s2.cardinality();
	
	for (int i = 0; i < size; i++) {
	    if (result.isElement(s2[i])) {
	        result.removeElement(s2[i]);
	    }
	}
	
	return result;
}

// Returns a set that is the symetric difference of the two sets s1 and s2
Set<char> setSymDiff(const Set<char> &s1, const Set<char> &s2)
{
	
	Set<char> result = setUnion(setDiff(s1, s2), setDiff(s2, s1));

	return result;
}

// Returns true if s1 is a subset of s2
bool isSubSet(const Set<char> &s1, const Set<char> &s2)
{
	// Add your code here and return the correct truth value
	// loop through each element in s1 and see if it's in s2
	bool wasFound;
	for (size_t i = 0; i <= s1.cardinality() - 1; i++)
	{
		char s1AtIndexI = s1[i]; // a
		for (size_t t = 0; t <= s2.cardinality() - 1; t++)
		{
			if (s1AtIndexI == s2[t]) // a ==
			{
				wasFound = true;
				break;
			}
			else
			{
				wasFound = false;
			}
		}
		if (wasFound == false)
		{
			break;
		}
	}
	return wasFound;
}

// Returns true if s1 is a proper subset of s2
bool isProperSubSet(const Set<char> &s1, const Set<char> &s2)
{
		// Copied directly from subset
		// this means we must make sure all elements 
		if(s1.cardinality() == s2.cardinality())
		{
			return false;
		}
		else
		{
			bool wasFound;
	for (size_t i = 0; i <= s1.cardinality() - 1; i++)
	{
		char s1AtIndexI = s1[i]; // a
		for (size_t t = 0; t <= s2.cardinality() - 1; t++)
		{
			if (s1AtIndexI == s2[t]) // a ==
			{
				wasFound = true;
				break;
			}
			else
			{
				wasFound = false;
			}
		}
		if (wasFound == false)
		{
			break;
		}
	}
	return wasFound;
		}
	
}

// This implementaion was done with the help of my classmate Jay.
// He uses recursion to pass over a set and index max, pretty cool huh!
void allSubsets(Set<char> &A, Set<Set<char>> &res, Set<char> &subset, int index)
{
	res.insertElement(subset);

	for (int i = index; i < A.cardinality(); i++)
	{
		subset.insertElement(A[i]);

		allSubsets(A, res, subset, i + 1);
		subset.removeElement(A[i]);
	}
	return;
}
// Returns the Power Set of set s as a set of sets
Set<Set<char>> PowerSet(const Set<char> &s)
{
	Set<Set<char>> result;

	// Add your code here
	Set<char> A = s;
	Set<char> subset = {};
	allSubsets(A, result, subset, 0);

	return result;
}

// Returns true if the sets in p make up a Partition of set s
bool isPartition(const Set<Set<char>> &p, const Set<char> &s)
{
	
	Set<char> tempUnion, tempIntersection;
	int partSize = p.cardinality();
	
	for (int i = 0; i < partSize; ++i)
	{
		if (!isSubSet(p[i], s)) {
			return false;
		}

		if (p[i].cardinality() == 0) {
			return false;
		}
		
		if (i + 1 < partSize) {
			tempIntersection = setIntersection(p[i], p[i + 1]);
			if (tempIntersection.cardinality() > 0) return false;
		}
		
		tempUnion = setUnion(p[i], tempUnion); 
	}
	
	if (tempUnion == s) {
	    return true;
	} else {
	    return false;
	}
}