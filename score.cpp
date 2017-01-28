#include <iostream>
#include <string>
#include <cassert>
using namespace std;

std::string normalize(std::string words)
{
	std::string normal = "";
	for (int i = 0; i < words.size(); i++)
	{

		if ((words[i] >= 'A') && (words[i] <= 'Z'))
		{
			normal += (words[i] + 32);
		}

		if ((words[i] >= 'a') && (words[i] <= 'z'))
		{
			normal += (words[i]);
		}

	}
	return normal;
}

bool stopChecker(char subject)
{
	if ((subject == ' ') || (subject == '\t') || (subject == ',') || (subject == '.') || (subject == ';') || (subject == ':') || (subject == '\'') || (subject == '\"') || (subject == '?'))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool matchChecker(std::string a, std::string b)
{
	for (int i = 0; i < a.size(); i++){
		if (a[i] != b[i]){
			return false;
		}
		else{
			return true;
		}
	}
}

int transformCriteria(unsigned int distances[], std::string words1[], std::string words2[], unsigned int nCriteria)
{
	int counter = 0;
	for (int i = 0; i < nCriteria; i++)
	{
		if (words1[i] != (normalize(words1[i])))
		{
			counter++;
		}
		if (words2[i] != (normalize(words2[i])))
		{
			counter++;
		}
		
		words1[i] = normalize(words1[i]);
		words2[i] = normalize(words2[i]);
	}
	return counter;
}

std::string* DocumentLexAndNorm(std::string& document, unsigned int& numberOfWords) 
{
	unsigned int numWordsOutput = 0;
	int start = 0;
	int end = 0;

	for (int i = start; i < document.size(); i++) {
		if( i == 0 || stopChecker(document[i-1]) == true ) {
			if( stopChecker(document[i]) == false) {
				for (int j = start; j < document.size(); j++) {
					if( j == document.size() - 1 || stopChecker(document[j+1]) == true ) {
						start = j+1;
						j = document.size();
						numWordsOutput++;
					}
				}
			}
		}
	}   

	numberOfWords = numWordsOutput;
	if(numWordsOutput == 0) {
		std::string* retVal = new std::string[1];
		retVal[0] = "";
		return retVal;
	}

	std::string* retVal = new std::string[numWordsOutput];

	
	start = 0;
	end = 0;

	for (int i = 0, q = 0; i < document.size(); i++) {
		if( i == 0 || stopChecker(document[i-1]) == true ) {
			if( stopChecker(document[i]) == false) {
				for (int j = i; j < document.size(); j++) {
					char cc = document[j];
					if( j == document.size() - 1 || stopChecker(document[j]) == true ) {						
						end = j;
						j = document.size();
					}
				}
			}
		} 

		std::string temp = "";

		for(int k = i; k < end+1; k++){
			temp += document[k];
		}
		
		
		std::string normal = normalize(temp);
		if(normal.size() > 0) {
			retVal[q] = normal;
			q++;
		}
		if(end > i)
			i = end;
	}   

	return retVal;
}

bool matchCriterion(std::string* doclex, unsigned int numNormWords, unsigned int distance, std::string& word1, std::string& word2)
{
	signed int distanceClone = distance;

	for (int i = 0; i < numNormWords; i++){
		std::string match;
		signed int matchPos = 0;

		//PART ONE
		if (word1.size() == doclex[i].size()){
			if (matchChecker(word1, doclex[i])){
				match = doclex[i];
				matchPos = i;

				if (matchPos + distanceClone < numNormWords){
					for (int k = matchPos; k < (matchPos + distanceClone + 1); k++){
						if (word2.size() == doclex[k].size()){
							if (matchChecker(word2, doclex[k])){
								return true;
							}
						}
					}
				}
				if (matchPos - distanceClone > 0){
					for (int n = matchPos; n > (matchPos - distanceClone - 1); n--){
						if (word2.size() == doclex[n].size()){
							if (matchChecker(word2, doclex[n])){
								return true;
							}
						}
					}
				}
				if (matchPos + distanceClone > numNormWords){
					for (int k = matchPos; k < numNormWords; k++){
						if (word2.size() == doclex[k].size()){
							if (matchChecker(word2, doclex[k])){
								return true;
							}
						}
					}
				}
				if (matchPos - distanceClone < 0){
					for (int n = matchPos; n > 0; n--){
						if (word2.size() == doclex[n].size()){
							if (matchChecker(word2, doclex[n])){
								return true;
							}
						}
					}
				}
			}
		}
	

		//PART TWO
		if (word2.size() == doclex[i].size()){
			if (matchChecker(word2, doclex[i])){
				match = doclex[i];
				matchPos = i;

				if (matchPos + distanceClone < numNormWords){
					for (int k = matchPos; k < (matchPos + distanceClone + 1); k++){
						if (word1.size() == doclex[k].size()){
							if (matchChecker(word1, doclex[k])){
								return true;
							}
						}
					}
				}
				if (matchPos - distanceClone > 0){
					for (int n = matchPos; n > (matchPos - distanceClone - 1); n--){
						if (word1.size() == doclex[n].size()){
							if (matchChecker(word1, doclex[n])){
								return true;
							}
						}
					}
				}
				if (matchPos + distanceClone > numNormWords){
					for (int k = matchPos; k < numNormWords; k++){
						if (word1.size() == doclex[k].size()){
							if (matchChecker(word1, doclex[k])){
								return true;
							}
						}
					}
				}
				if (matchPos - distanceClone < 0){
					for (int n = matchPos; n > 0; n--){
						if (word1.size() == doclex[n].size()){
							if (matchChecker(word1, doclex[n])){
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

int DocumentScore(std::string& document, unsigned int nCriteria, unsigned int distances[], std::string words1[], std::string words2[])
{
	int counter = 0;
	unsigned int numberofWords = 0;
	transformCriteria(distances, words1, words2, nCriteria);
	std::string* doclex = DocumentLexAndNorm(document, numberofWords);
	for (int i = 0; i < nCriteria; i++){
		if (matchCriterion (doclex, numberofWords, distances[i], words1[i], words2[i])){
			counter++;
		}
	}
	return counter;
}


int main ()
{
	 const unsigned int TEST1_NCRITERIA = 4;
            unsigned int test1dist[TEST1_NCRITERIA] = { 2, 4, 1, 13 };
            std::string test1w1[TEST1_NCRITERIA] = { "Mad", "deranged123", "plot", "have" };
            std::string test1w2[TEST1_NCRITERIA] = { "14scientist", "robot", "nefarious12", "MAD!" };
            std::string doc1 = "The mad UCLA scientist unleashed a deranged evil giant robot.";
            assert(DocumentScore(doc1, TEST1_NCRITERIA, test1dist, test1w1, test1w2) == 2);
            std::string doc2 = "The mad UCLA scientist unleashed    a deranged robot.";
            assert(DocumentScore(doc2, TEST1_NCRITERIA, test1dist, test1w1, test1w2) == 2);
            std::string doc3 = "**** 2012 ****";
            assert(DocumentScore(doc3, TEST1_NCRITERIA, test1dist, test1w1, test1w2) == 0);
            std::string doc4 = "  What a NEFARIOUS plot!";
           assert(DocumentScore(doc4, TEST1_NCRITERIA, test1dist, test1w1, test1w2) == 1);
            std::string doc5 = "Two mad scientists have deranged-robot fever.";
            assert(DocumentScore(doc5, TEST1_NCRITERIA, test1dist, test1w1, test1w2) == 1);
            cout << "All tests succeeded" << endl;

			unsigned int numberofWords = 0;
			//DocumentLexAndNorm(doc4, numberofWords);
			//cout << numberofWords << endl;
			//DocumentScore(doc4, TEST1_NCRITERIA, test1dist, test1w1, test1w2);



	/*std::string document = "This is NOT an exciting document...";
	unsigned int nb_words = 0;
	std::string * doc = DocumentLexAndNorm(document, nb_words);
	for (unsigned int i = 0; i < nb_words; ++i) {
		cout << "word #" << i << ": " << doc[i];
		cout << std::endl;
	}*/


	/*std::string document = "this is not an exciting document...";
	unsigned int nb_words = 0;
	documentlexandnorm(document, nb_words);*/
	/*for (unsigned int i = 0; i < nb_words; ++i) {
		cout << "word #" << i << ": " << doc[i];
		cout << std::endl;
	}*/
// Free the array created at the end of the program.
//delete[]doc;

}