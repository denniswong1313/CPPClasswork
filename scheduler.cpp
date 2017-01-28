#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


class Scheduler{
	public:
		std::vector<string> taskList;
		std::vector<int> taskNumber;
	
	std::string createTaskString(std::string base, unsigned int val){
		std::string ret;
		std::stringstream s;
		s << base;
		s << val;
		ret = s.str();

		return ret;
	}

	std::string createStringFromInt(int val){
		std::string ret;
		std::stringstream s;
		s << val;
		ret = s.str();

		return ret;
	}

	void setNumberOfTasks(unsigned int n){
		
		taskList.clear();
		taskNumber.clear();
		for (int i = 0; i < n; i++){
			taskList.push_back(createTaskString("T", i));
			taskNumber.push_back(0);
		}
	}

	std::string printSchedule(){
		string schedule = "Schedule: (";
		for (int i = 0; i < taskList.size(); i++){
			schedule += taskList[i] + "=" + createStringFromInt(taskNumber[i]) + " ";
		}
		schedule += ")";
		return schedule;
	}

	std::vector<int> getSchedule(){
		return taskNumber;
	}

	unsigned int getTaskId(std::string name){
	   int sz = name.size() + 1;
	   char *buffer = new char[sz];
	   char* b = buffer;
	   strcpy (buffer, name.c_str());
	   b++; // skip the first character 'T'
	   int ret = atoi (b);
	   delete [] buffer;

	   return ret; 
	}

	std::string getTaskNameAtPos(std::string depgraph, unsigned int pos){
		string taskName="T";
		if (pos > depgraph.size()){
			return "";
		}

		if (depgraph[pos] != 'T'){
			return "";
		}

		if (depgraph[pos] == 'T'){
			for (int i = pos+1; i < depgraph.size(); i++){
				if (depgraph[i] != 'T'){
					taskName += depgraph[i];
				}
				else{
					break;
				}
			}
		}
		return taskName;
	}

	bool isStringValid(std::string depgraph, unsigned int numTasks){
		int taskCounter = 0;
		for (int i = 0; i < depgraph.size(); i++){
			if (!((depgraph[i] == 'T') || ((depgraph[i] >= '0') && (depgraph[i] <= '9')))){
				return false;
			}

			if ((depgraph[i] == 'T') && (depgraph[i+1] == 'T')){
				return false;
			}

			if (depgraph[0] != 'T'){
				return false;
			}

			if (depgraph[depgraph.size()-1] == 'T'){
				return false;
			}

			if (getTaskNameAtPos(depgraph,i) != ""){
				taskCounter++;
				if (getTaskId(getTaskNameAtPos(depgraph, i)) >= (numTasks)){
					return false;
				}
			}
		}
		if (taskCounter % 2 != 0){
				return false;
		}
		return true;
	}

	void set_task_time(string taskId, unsigned int val){
		taskNumber[getTaskId(taskId)] = val;
	}

	int get_time(string taskId){
		return taskNumber[getTaskId(taskId)];
	}

	void computeFreeSchedule(std::string depgraph){
		if (isStringValid(depgraph, taskList.size()) == false){
			return;
		}

		for (int i = 0; i < taskNumber.size(); i++){
			taskNumber[i] = 0;
		}

		std::vector<string> depvector;
		for (int i = 0; i < depgraph.size(); i++){
			if (getTaskNameAtPos(depgraph, i) != ""){
				depvector.push_back(getTaskNameAtPos(depgraph, i));
			}
		}

		int i;
		bool has_converged;
		do{
			has_converged = true;
			for (i = 0; i < depvector.size(); i += 2){
				int val1 = get_time(depvector[i]);
				int val2 = get_time(depvector[i+1]);
 				if (val1 >= val2)
 					has_converged = false;
					int max = val1 + 1;
				if (max < val2)
					max = val2;
					set_task_time (depvector[i+1], max);
			}
		}
		while (! has_converged);
	}

	bool checkSchedule(std::string depgraph, std::vector<int> schedule){
		std::vector<string> depvector;
		if (depgraph == ""){
			return true;
		}

		if (isStringValid(depgraph, schedule.size()) == false){
			return false;
		}

		for (int i = 0; i < depgraph.size(); i++){
			if (getTaskNameAtPos(depgraph, i) != ""){
				depvector.push_back(getTaskNameAtPos(depgraph, i));
			}
		}

		for (int j=0; j < depvector.size() - 1; j+=2){
			int id1 = getTaskId(depvector[j]);
			int id2 = getTaskId(depvector[j+1]);
			int a = schedule[id1];
			int b = schedule[id2];
			if (a >= b){
				return false;
			}
		}
		return true;
	}

	bool isSchedulable(std::string depgraph){
		std::vector<string> depvector;
		if (depgraph == ""){
			return true;
		}

		for (int j = 0; j < depgraph.size(); j++){
			if (getTaskNameAtPos(depgraph, j) != ""){
				depvector.push_back(getTaskNameAtPos(depgraph, j));
			}
		}

		if (isStringValid(depgraph, taskList.size()) == false){
			return false;
		}

		int** adjmat = new int*[taskList.size()];
		int i;
		for(i = 0; i < taskList.size(); ++i)
			adjmat[i] = new int[taskList.size()];

		for(int k = 0; k < taskList.size(); k++){
			for (int l = 0; l < taskList.size(); l++){
				adjmat[k][l] = 0;
			}
		}

		for (int x = 0; x < depvector.size() - 1; x+=2){
			int id1 = getTaskId(depvector[x]);
			int id2 = getTaskId(depvector[x+1]);
			adjmat[id1][id2] = 1;
		}

  // Algorithm to compute paths.
  {
		   int k, i, j;
			for (k = 0; k < taskList.size(); k++){
				for(i = 0; i < taskList.size(); i++){
     				for (j = 0; j < taskList.size(); j++){
						if (adjmat[i][k] && adjmat[k][j]){
							if (adjmat[i][j]){
         						adjmat[i][j] = adjmat[i][j] < adjmat[i][k] + adjmat[k][j] ?
									   adjmat[i][j] : adjmat[i][k] + adjmat[k][j];
							}
    					else{
	        				adjmat[i][j] = adjmat[i][k] + adjmat[k][j];
						}
					}
				}
			}
		}
	}
  
  for (int z = 0; z < taskList.size(); z++){
	  if (adjmat[z][z] != 0){
		return false;
	  }
  }
  for(i = 0; i < taskList.size(); ++i){
    delete [] adjmat[i];
  }
	delete [] adjmat;
 

  return true;

}
};

int main(){
	std::cout << "THE START" << std::endl;
Scheduler s;
s.setNumberOfTasks(4);
std::cout << s.isSchedulable("") << std::endl;
std::cout << s.isSchedulable("T0T0") << std::endl;
std::cout << s.isSchedulable("T0T1T0T2T1T2") << std::endl;
std::cout << s.isSchedulable("T0T1T1T2T2T0") << std::endl;
std::cout << "THE END" << std::endl;
	return 0;
}

	

