#include "../headers/utilCLUSTER.h"

/* Distance calculator function is implemented in order to be easily extendable in vector 
spaced with other metrics. */
double dist(int distance,item x,item y){

	if(x.getVector()->size() != y.getVector()->size()){

		cerr << "Cannot compute Euclidean Distance between vertexes from different dimensions." << endl;
		return 0;
	}

	unsigned long int d = x.getVector()->size();
	double result = 0.0;

	for(unsigned long int i = 0;i<d;i++)
		result += pow((*x.getVector()).at(i)-(*y.getVector()).at(i),distance);
	
	return pow(result,1.0/distance);
}

void readConf(string fileName,int *K,int *L,int *kLSH,int *M,int *kCUBE,int *probes){

	ifstream fp;
	fp.open(fileName);

	string line, word;
	int target =0;

	while( getline(fp,line) ){

		stringstream linestream(line);
		int counter =0;

		while(linestream >> word){

			if(!counter++)
				continue;

			switch(target++){

				case(0):{

					*K = stoi(word);
					break;
				}case(1):{

					*L = stoi(word);
					break;
				}case(2):{

					*kLSH = stoi(word);
					break;
				}case(3):{

					*M = stoi(word);
					break;
				}case(4):{

					*kCUBE = stoi(word);
					break;
				}case(5):{

					*probes = stoi(word);
					break;
				}
			}
		}
	}
}

void readDatasetCLUSTER(string fileName,Clustering* cluster,vector<item*> *dataset){

	ifstream fp;
	fp.open(fileName);

	string line,id,word;
	int counter =0;

	while( getline(fp,line) ){

		vector<double> words;
		stringstream linestream(line);

		while(linestream >> word){

			if(++counter == 1){

				id = word;
				continue;
			}

			words.push_back(stod(word));

		}

		counter =0;

		item* newItem = new item(id,words);
		dataset->push_back(newItem);

		cluster->insert(newItem);
		// item temp(id,words);
		// temp.print();
	}
}

void fillDatasetCLUSTER(vector<item*> dataset,Clustering* cluster){

	for(vector<item*>::iterator it = dataset.begin(); it != dataset.end(); it++)
		cluster->insert(*it);
}

item* getRandomItem(vector<item*> i){

	/* We use uniform distribution in order to generate a random t in range [0,w). */
	random_device rd;
	mt19937 generator(rd());
	uniform_real_distribution<> distance(0,i.size());

	return i.at(distance(generator));
}

// void deleteByValue(item* i,vector<item*> *items){

// 	for(unsigned long int j=0;j<items->size();j++)
// 		if(items->at(j)->getID() == i->getID())
// 	    	items->erase(items->at(j));
// 	else
// 		cout << "GOt here\n";
// }

double prob(vector<pair<item*,double>> D){

	double add = 0;

	for(vector<pair<item*,double>>::iterator it = D.begin(); it != D.end(); it++)
		add += pow((*it).second,2);

	return add;
}

int32_t H(item *p,int w,vector<double> * v,double t){

	// p->print();

	// /* We use uniform distribution in order to generate a random t in range [0,w). */
	// random_device rd;
	// mt19937 generator(rd());
	// uniform_real_distribution<> distance(0,w);

	// double t = distance(generator);
	// cout << "t is " << t << endl;

	/* We use normal distribution in order to generate a random vector v. */
	// vector<double> *v = produceNdistVector(p->getDimension(),0.0,1.0);

	// cout << "v ";
	// for(unsigned long int i=0;i<v->size();i++)
	// 	cout << (*v)[i] << " "; 
	// cout << endl;

	/* We calculate the scaler product between vectors p and (randomly generated) v. */
	double scalerProduct = inner_product(p->getVector()->begin(),p->getVector()->end(),v->begin(),0.0);

	// double scalerProduct = 0.0;

	// cout << "Scaler product is " << scalerProduct << endl;

	return (int32_t)floor( (scalerProduct + t) / (double)w );

}

int32_t G(item* p,int w,int k,vector<int32_t> rVector,int tableSize){

	/* We use uniform distribution in order to generate a random t in range [0,w). */
	random_device rd;
	mt19937 generator(rd());
	uniform_real_distribution<> distance(0,w);

	double t = distance(generator);

	/* We use normal distribution in order to generate a random vector v. */
	vector<double> *v = produceNdistVector(p->getDimension(),0.0,1.0);

    long int M = pow(2,32/k);
    // cout << "M : " << M << endl;

	// vector<uint32_t> hashFunctions;
	int result =0;
	//int32_t temp;
	for(int i=0;i<k;i++){

		// int32_t r = rand();

		// cout << "Before addition is: " << (result) << endl;
		//temp = H(p,w);
		//temp = module(temp,M);
		// cout << "temp is : " << temp << endl;
		int temp = module(H(p,w,v,t)*rVector.at(i),M);
		// cout << "Result is " << temp << endl;
		result += temp;
		// cout << "After addition is: " << (result) << endl;
	}

	// cout << "It came out as: " << result << endl;
	//cout << "Result is : " << result;
	result = module(result,M);
	// cout << "After modM is " << result << endl;
	p->setTrick(result);
	// cout << endl << "NOw IT IS " << result << endl;

	// result2 = module(result,M);
	result = module(result,tableSize);
	// cout << "After mod" << tableSize << " is " << result << endl;
	// result2 = module(result,tableSize);
	
	//cout << "Result is: " << result << endl;

	return result;

}

int module(int a, int b){
    return (a%b + b) % b;
}

vector<double>* produceNdistVector(int dimension,int mean,int stddev){

	default_random_engine generator(random_device{}());
	normal_distribution<double> distribution(/*mean=*/mean, /*standard deviation=*/stddev);

	vector<double> *temp = new vector<double>;

	for(int i=0;i<dimension;i++)
		temp->push_back(distribution(generator));

	return temp;

}

int getDimension(string fileName){

	ifstream fp;
	fp.open(fileName);

	string line,id,word;
	int counter =0;

	getline(fp,line);

	vector<double> words;
	stringstream linestream(line);

	while(linestream >> word){

		if(++counter == 1){

			id = word;
			continue;
		}

		words.push_back(stod(word));

	}

	counter =0;

	item newItem(id,words);
	return newItem.getDimension();
	
}

void writeToFile(string fileName,string content){

	ofstream file;

	file.open(fileName,fstream::app);
	file << content;
	file.close();
}

int calculateW(string fileName,int flag){

	ifstream fp;
	fp.open(fileName);

	string line,id,word;
	int counter =0;

	int totalDist =0;
	int totalW = 0;

	item *firstItem;

	int count =0;

	while(getline(fp,line)){

		if(++count == 1){

			vector<double> words;
			stringstream linestream(line);

			while(linestream >> word){

				if(++counter == 1){

					id = word;
					continue;
				}

				words.push_back(stod(word));

			}

			counter =0;

			firstItem = new item(id,words);
		}

		vector<double> words;
		stringstream linestream(line);

		while(linestream >> word){

			if(++counter == 1){

				id = word;
				continue;
			}

			words.push_back(stod(word));

		}

		counter =0;

		item newItem(id,words);

		totalDist += dist(2,newItem,*firstItem);
		totalW++;
		
		if(count == flag){

			delete firstItem;
			return totalDist/totalW;
		}
	}

	delete firstItem;
	return 0;
}

void functionality(string inputFile,string outputFile,int K, int L, int kLSH, int M, int kCUBE, int probes, int w, bool complete, int totalItems){

/*******************LLOYD*****************************/

	Clustering clustering1(K,L,kLSH,M,kCUBE,probes,w,totalItems);

	vector<item*> dataset;

	readDatasetCLUSTER(inputFile,&clustering1,&dataset);

	auto startClustering = high_resolution_clock::now();

	clustering1.kMeansPP();
	clustering1.Assign("Classic");

	auto endClustering = high_resolution_clock::now();

	// clustering1.print();

	writeToFile(outputFile,"Algorithm: Lloyds\n");
	// cout << "Algorithm: Lloyds" << endl;

	for(int i=0;i<K;i++){

		writeToFile(outputFile,"CLUSTER-" + to_string(i) + " {");

		pair<int,item*> stats = clustering1.getClusterat(i);

		writeToFile(outputFile,"size: " + to_string(stats.first) + ",");
		writeToFile(outputFile,"centroid: ");

		vector<double> *coordinates = stats.second->getVector();

		for(unsigned long int j=0;j<coordinates->size();j++)
			writeToFile(outputFile,to_string(coordinates->at(j)) + " ");
		
		writeToFile(outputFile,"}\n");
	}

	writeToFile(outputFile,"clustering_time: " + to_string((double)duration_cast<seconds>(endClustering - startClustering).count()) + "\n");

	pair<vector<double>,double> test1;
	// clustering1.Silhouette();

	writeToFile(outputFile,"Silhouette: [");
	// cout << "Silhouette: [";

	vector<double> result = test1.first;

	for(vector<double>::iterator it = result.begin(); it != result.end(); it++)
		writeToFile(outputFile,to_string(*it) + ",");
		// cout << (*it) << ",";

	writeToFile(outputFile,to_string(test1.second) + "]\n");
	// cout << test.second << "]" << endl;

	if(complete){

		for(int i=0;i<K;i++){

			writeToFile(outputFile,"CLUSTER-" + to_string(i) + " {");

			pair<string,vector<string>> result = clustering1.getCompleteClusterat(i);

			writeToFile(outputFile, result.first + ", " );

			for(vector<string>::iterator it = result.second.begin(); it != result.second.end(); it++)
				writeToFile(outputFile,(*it) + ",");

			writeToFile(outputFile,"}\n");

		}
	}

	writeToFile(outputFile,"\n");

/*************************LSH************************/

	Clustering clustering2(K,L,kLSH,M,kCUBE,probes,w,totalItems);

	readDatasetCLUSTER(inputFile,&clustering2,&dataset);

	startClustering = high_resolution_clock::now();

	clustering2.kMeansPP();
	clustering2.Assign("LSH");

	endClustering = high_resolution_clock::now();

	writeToFile(outputFile,"Algorithm: LSH\n");

	for(int i=0;i<K;i++){

		writeToFile(outputFile,"CLUSTER-" + to_string(i) + " {");

		pair<int,item*> stats = clustering2.getClusterat(i);

		writeToFile(outputFile,"size: " + to_string(stats.first) + ",");
		writeToFile(outputFile,"centroid: ");

		vector<double> *coordinates = stats.second->getVector();

		for(unsigned long int j=0;j<coordinates->size();j++)
			writeToFile(outputFile,to_string(coordinates->at(j)) + " ");
		
		writeToFile(outputFile,"}\n");
	}

	writeToFile(outputFile,"clustering_time: " + to_string((double)duration_cast<seconds>(endClustering - startClustering).count()) + "\n");

	// test1 = clustering2.Silhouette();

	writeToFile(outputFile,"Silhouette: [");
	// cout << "Silhouette: [";

	result = test1.first;

	for(vector<double>::iterator it = result.begin(); it != result.end(); it++)
		writeToFile(outputFile,to_string(*it) + ",");
		// cout << (*it) << ",";

	writeToFile(outputFile,to_string(test1.second) + "]\n");
	// cout << test.second << "]" << endl;

	if(complete){

		for(int i=0;i<K;i++){

			writeToFile(outputFile,"CLUSTER-" + to_string(i) + " {");

			pair<string,vector<string>> result = clustering2.getCompleteClusterat(i);

			writeToFile(outputFile, result.first + ", " );

			for(vector<string>::iterator it = result.second.begin(); it != result.second.end(); it++)
				writeToFile(outputFile,(*it) + ",");

			writeToFile(outputFile,"}\n");

		}
	}

	writeToFile(outputFile,"\n");

/********************HYPERCUBE***************/

	Clustering clustering3(K,L,kLSH,M,kCUBE,probes,w,totalItems);

	readDatasetCLUSTER(inputFile,&clustering3,&dataset);

	startClustering = high_resolution_clock::now();

	clustering3.kMeansPP();
	clustering3.Assign("Hypercube");

	endClustering = high_resolution_clock::now();

	writeToFile(outputFile,"Algorithm: Hypercube\n");

	for(int i=0;i<K;i++){

		writeToFile(outputFile,"CLUSTER-" + to_string(i) + " {");

		pair<int,item*> stats = clustering3.getClusterat(i);

		writeToFile(outputFile,"size: " + to_string(stats.first) + ",");
		writeToFile(outputFile,"centroid: ");

		vector<double> *coordinates = stats.second->getVector();

		for(unsigned long int j=0;j<coordinates->size();j++)
			writeToFile(outputFile,to_string(coordinates->at(j)) + " ");
		
		writeToFile(outputFile,"}\n");
	}

	writeToFile(outputFile,"clustering_time: " + to_string((double)duration_cast<seconds>(endClustering - startClustering).count()) + "\n");

	// test1 = clustering3.Silhouette();

	writeToFile(outputFile,"Silhouette: [");

	result = test1.first;

	for(vector<double>::iterator it = result.begin(); it != result.end(); it++)
		writeToFile(outputFile,to_string(*it) + ",");

	writeToFile(outputFile,to_string(test1.second) + "]\n");

	if(complete){

		for(int i=0;i<K;i++){

			writeToFile(outputFile,"CLUSTER-" + to_string(i) + " {");

			pair<string,vector<string>> result = clustering3.getCompleteClusterat(i);

			writeToFile(outputFile, result.first + ", " );

			for(vector<string>::iterator it = result.second.begin(); it != result.second.end(); it++)
				writeToFile(outputFile,(*it) + ",");

			writeToFile(outputFile,"}\n");

		}
	}

	writeToFile(outputFile,"\n");
}

int countItems(string fileName){

	ifstream fp;
	fp.open(fileName);

	string line;
	int n =0;

	while( getline(fp,line) )
		n++;

	return n;

}