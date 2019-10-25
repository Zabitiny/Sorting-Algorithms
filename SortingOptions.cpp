#include <iostream>
#include <fstream>
#include <vector>

void printVector(const std::vector<int> &v){
	for(int i=0; i<v.size(); i++){
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
}

void selectionSort(std::vector<int> &v){
	std::cout << "Original Vector: ";
	printVector(v);
	std::cout << "Vector is now being sorted." << std::endl;
	int lowest, temp;

	for(int i=0; i<v.size()-1; i++){
		lowest = v[i];
		temp = i; 
		for(int j=i+1; j<v.size(); j++){
			if(v[j] < v[i] && v[j] < lowest){
				lowest = v[j];
				temp = j;
			}
		}
		v[temp] = v[i];
		v[i] = lowest;

		printVector(v);
	}

	std::cout << "Vector is now sorted!" << std::endl;

}//end of selection sort

void merge(std::vector<int> &v, int left, int middle, int right){
	std::vector<int> temp(v.size());

	//need indeces for left & right halves of array, and for temp array
	int i=left, j=middle+1, k=left;

	std::cout << "VECTOR BEFORE: " << std::endl;
	printVector(v);
	
	/**compare left half to right half
	 * once either half is done assume the rest are in order */
	while(i <= middle && j <= right){
		if(v[i] < v[j]){
			temp[k] = v[i];
			i++;
		}
		else{
			temp[k] = v[j];
			j++;
		}
		k++;
	}

	//move remaining values into temp array
	while(i <= middle){
		temp[k] = v[i];
		i++, k++;
	}
	while(j <= right){
		temp[k] = v[j];
		j++, k++;
	}
	//copy values to original
	for(int i=0; i<v.size(); i++){
		v[i] = temp[i];
	}
	std::cout << "VECTOR AFTER: " << std::endl;
	printVector(v);

}//end of merge

void mergeSort(std::vector<int> v, int left, int right){
	if(right > left){
		int middle = (left+right)/2;

		mergeSort(v, left, middle); //these two break down array into sub arrays
		mergeSort(v, middle+1, right);

		merge(v, left, middle, right); //this merges them back together
	}
}//end of mergeSort

void quickSort(std::vector<int> &v){
	std::cout << "Original Vector: ";
	printVector(v);
	std::cout << "Vector is now being sorted." << std::endl;


	std::cout << "Vector is now sorted!" << std::endl;
}//end of quickSort

void insertionSort(std::vector<int> &v){
	std::cout << "Original Vector: ";
	printVector(v);
	std::cout << "Vector is now being sorted." << std::endl;



	std::cout << "Vector is now sorted!" << std::endl;
}//end of insertion sort

int main(){
	std::ifstream infile;
	std::string user;
	
	//get user input for read file and write file
	std::cout << "Sorting Options: \n"
			<< "---------------------------------\n"
			<< "Enter a file for input: " << std::flush;
	std::cin >> user;
	infile.open(user);
	
	//check to make sure user defined infile works
	if(!infile){
		std::cout << "your file for input is invalid"<< std::endl;
		exit(1);
	}

	std::cout << "\nEnter a file for output: ";
	std::cin >> user;
	std::ofstream outfile(user);
	
	//prompt user for which algorithm they want to use
	//put result in algorithm
	int algorithm;
	std::cout << "What sorting algorithm would you like to use?\n"
		<< "1. Selection Sort\n"
		<< "2. Merge Sort\n"
		<< "3. Quick Sort\n"
		<< "4. Insertion Sort" << std::endl;
	std::cout << "(Enter an integer value for your selection): ";
	std::cin >> algorithm;
	
	
	std::vector<int> numbers;
	std::string line;
	std::string clean;
	int counter = 0;

	/*first loop is for the number of lines in the file
	* second loop is for the number of values in each line */
	while(getline(infile, line)){
	
		for(char ch: line){
			if(isdigit(ch))
				clean += ch;
			else if(isspace(ch)){
				continue;
			}
			else{
				numbers.push_back(stoi(clean));
				clean.clear();
			}
		}
		if(!clean.empty()){
			numbers.push_back(stoi(clean));
			clean.clear();
		}
		//TODO: add sorting call
		switch (algorithm){
			case 1: selectionSort(numbers);
					break;
			case 2: std::cout << "Original Vector: ";
					printVector(numbers);
					std::cout << "Vector is now being sorted." << std::endl;
					mergeSort(numbers, 0, numbers.size()-1);
					std::cout << "Vector is now sorted!" << std::endl;
					printVector(numbers);
					break;
			case 3: quickSort(numbers);
					break;
			case 4:insertionSort(numbers);
					break;
		}

		for(int i=0; i<numbers.size(); i++){
			outfile << numbers[i] << std::endl;
		}

		numbers.clear();
	}

	infile.close();
	outfile.close();
	return 0;
}
