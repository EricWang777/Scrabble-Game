 #include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

// Build function: if already have skyscraper, print error and return 
// BUILD x y c: currSkyscraper = sjyline[x]; y = height; c = color;
// totalHeight = buildingHeight[x];
void Build(string* &currSkyscraper, int height, int spot, 
		   string color, int &totalHeight, ofstream& outputfile){
	if (currSkyscraper != NULL) {
		outputfile << "Error - incorrect command" << endl; // using outputfile
		return;
	}
	else{
		currSkyscraper = new string[height];
		for (int i = 0; i < height; ++i){
			currSkyscraper[i] = color;
		}
		totalHeight = height;
	}
}

// Extend function: if no skyscrpaer, print error and return
// EXTEND x y c:
// currSk.. = skyline[x]; y = addHeight;
// c = color; currHeight = buildingHeight[x];
void Extend(string* &currSkyscraper, int addHeight, int spot,
			string color, int &currHeight, ofstream& outputfile){
	if (currSkyscraper == NULL){ // nothing built in this spot
		outputfile << "Error - incorrect command" << endl; // using outputfile
		return;
	}
	else{
		string* newArr = new string[addHeight + currHeight];// curr no change
		for (int i = 0; i < currHeight; ++i){
			newArr[i] = currSkyscraper[i]; // copy
		}
		delete[] currSkyscraper;
		currSkyscraper = newArr; // curr now points to larger array
		for (int i = currHeight; i < currHeight+addHeight; ++i){
			currSkyscraper[i] = color;
		}
		currHeight += addHeight; // build finish
	} 
}

// Demolish function: if no skyscraper, print error and return
// DEMOLISH x;
// currSk.. = skyline x; height = buildingheights[x]
void Demolish(string* &currSkyscraper, ofstream& outputfile, 
			  int spot, int &height){
	if (currSkyscraper == NULL){
		outputfile << "Error - incorrect command" << endl;
		return;
	}
	delete[] currSkyscraper;
	height = 0;
	currSkyscraper = NULL;

}

// Skyline function : if y < 1 print error and return
// our height(index) = user height - 1;
void Skyline(string** skyline, int height, int numBuilding,
			 int* buildingheights, ofstream& outputfile){
	if (height < 0){
		outputfile << "Error - incorrect command" << endl;
		return;
	}

	for (int i = 0; i < numBuilding; ++i){
		if (height < buildingheights[i]){
			outputfile << skyline[i][height] << " ";
		}
		else outputfile << "SKY ";
	}
	outputfile << endl;
}




int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }
  ifstream input(argv[1]);
  ofstream output(argv[2]);

  int constructionspots;
  int *buildingheights;
  string **skyline;
  string curr;
  string extra;

  input >> constructionspots;
  getline(input, curr); //consume the newline character for the first line.
  skyline = new string*[constructionspots];

  //you will need to keep track of the height of each building
  buildingheights = new int[constructionspots];

  for (int i = 0; i < constructionspots; i++) {
	  buildingheights[i] = 0;
	  skyline[i] = NULL;
  }
  while(getline(input, curr)) {
	  stringstream ss(curr);
	  ss >> curr;
	  if (curr == "BUILD") {
		  int x,y;
		  string c;
		  ss >> x;
		  ss >> y;
		  ss >> c;

		  if (ss.fail() || skyline[x] != NULL || x >= constructionspots
		  	  || ss >> extra || y <= 0) {
			  output << "Error - incorrect command" << endl;
		  }
		  else {
		  	  Build(skyline[x], y, x, c, buildingheights[x], output);
		  }
	  }
	  else if (curr == "EXTEND") {
	  	int x, y;
	  	string c;
	  	ss >> x;
	  	ss >> y;
	  	ss >> c;
	  	if (ss.fail() || skyline[x] == NULL || x >= constructionspots
	  		|| ss >> extra || y <= 0){
	  		output << "Error - incorrect command" << endl;
	  	}
	  	else{
	  		Extend(skyline[x], y, x, c, buildingheights[x], output);
	  	}

	  }
	  else if (curr == "DEMOLISH") {
	  	int x;
	  	ss >> x;
	  	if (ss.fail() || skyline[x] == NULL || ss >> extra){
	  		output << "Error - incorrect command" << endl;
	  	}
	  	else{
	  		Demolish(skyline[x], output, x, buildingheights[x]);
	  	}
	  }
	  else if (curr == "SKYLINE") {
	  	int y;
	  	ss >> y;
	  	if (ss.fail() || y < 1 || ss >> extra){
	  		output << "Error - incorrect command" << endl;
	  	}
	  	else{
	  		Skyline(skyline, y-1, constructionspots,
					buildingheights, output);
	  	}

	  }
	  else {
	  	output << "Error - incorrect command" << endl;
	  }
  }

// delete
  for (int i = 0; i < constructionspots; ++i){
  	delete[] skyline[i];
  	
  }
  delete[] skyline;
  delete[] buildingheights;

  return 0;
}
