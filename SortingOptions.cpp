#include <iostream>
#include <fstream>
#include <vector>

void printVector(const std::vector<int> &v){
	for(const auto& i : v){
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

void selectionSort(std::vector<int> &v){
	std::cout << "Original Vector: ";
	printVector(v);
	std::cout << "Vector is now being sorted." << std::endl;
	int lowest, temp;

	for(size_t i=0; i<v.size()-1; i++){
		lowest = v[i];
		temp = i; 
		for(size_t j=i+1; j<v.size(); j++){
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
	for(int i=left; i<= right; i++){
		v[i] = temp[i];
	}
}//end of merge

void mergeSort(std::vector<int> &v, int left, int right){
	if(right > left){
		int middle = (left+right)/2;

		mergeSort(v, left, middle); //these two break down array into sub arrays
		mergeSort(v, middle+1, right);
		merge(v, left, middle, right); //this merges them back together
		
		printVector(v);
	}
}//end of mergeSort

/**returns median of the three indeces given for the given vector */
int median(const std::vector<int> &v, int left, int mid, int right){
	//cases for if left is the median
	if(((v[left] <= v[right]) && (v[left] >= v[mid])) 
		|| ((v[left] <= v[mid]) && (v[left] >= v[right]))){
			return left;
	}
	//cases for if mid is the median
	else if((v[mid] <= v[right] && v[mid] >= v[left]) 
		|| (v[mid] <= v[left] && v[mid] >= v[right])){
			return mid;
	}
	//only one left is right
	else{
		return right;
	}
}

int partition(std::vector<int> &v, int left, int right){
	int mid = (left+right)/2;
	int pivot = median(v, left, mid, right);

	//bring pivot to the front
	int temp = v[pivot];
	v[pivot] = v[left];
	v[left] = temp;
	
	int j=left;
	for(int i = left+1; i <= right; i++){
		if(v[i] < v[left]){
			j++;
			temp = v[i];
			v[i] = v[j];
			v[j] = temp;
		}
	}
	pivot=j;

	//put pivot back
	temp = v[pivot];
	v[pivot] = v[left];
	v[left] = temp;

	printVector(v);

	return pivot;
}//end of partition

void quickSort(std::vector<int> &v, int left, int right){
	if(left < right){
		int pivot = partition(v, left, right);
		quickSort(v, left, pivot-1);
		quickSort(v, pivot+1, right);
	}
}//end of quickSort

void insertionSort(std::vector<int> &v){
	std::cout << "Original Vector: ";
	printVector(v);
	std::cout << "Vector is now being sorted." << std::endl;

	int j;
	int current;
	for(size_t i=1; i<v.size(); i++){
		current = v[i];
		j = i-1;
		while(j >= 0 && current < v[j]){
			v[j+1] = v[j];
			j--;
		}
		v[j+1] = current;
		printVector(v);
	}

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
		std::cout << "the file you specifed for input is either not here or invalid"<< std::endl;
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
	// int counter = 0;

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

		switch (algorithm){
			case 1: selectionSort(numbers);
					break;
			case 2: std::cout << "Original Vector: ";
					printVector(numbers);
					std::cout << "Vector is now being sorted." << std::endl;
					mergeSort(numbers, 0, numbers.size()-1);
					std::cout << "Vector is now sorted!" << std::endl;
					break;
			case 3: std::cout << "Original Vector: ";
					printVector(numbers);
					std::cout << "Vector is now being sorted." << std::endl;
					quickSort(numbers, 0, numbers.size()-1);
					std::cout << "Vector is now sorted!" << std::endl;
					break;
			case 4:insertionSort(numbers);
					break;
		}

		for(const auto& i : numbers){
			outfile << i << " ";
		}
		outfile << std::endl;

		numbers.clear();
	}

	infile.close();
	outfile.close();
	return 0;
}
